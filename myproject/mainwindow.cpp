#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//隐藏最大最小化等按键
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()){
        //查询出有哪些串口设备，并将其打印出来
        QSerialPort serival;
        serival.setPort(info);
        if(serival.open(QIODevice::ReadWrite)){
             ui->textEdit->append(serival.portName());//控制台输出的信息
            //在图形中的下拉框中显示串口的名字信息
            ui->portBox->addItem(serival.portName());
            serival.close();
        }
    }
    QVector<QString> music{"bwm1.wav","tmedium"};
    QRandomGenerator generator;
    generator.seed(QDateTime::currentMSecsSinceEpoch());
    int randValue = QRandomGenerator::global()->bounded(0, 2);
    qDebug()<<randValue;
    QString musicName = music[randValue];
    player = new QMediaPlayer(this);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::onMediaStatusChanged);
    QString musicFilePath = QDir::currentPath() +"/music/"+ musicName;
    ui->textEdit->append(musicFilePath);
    player->setMedia(QUrl::fromLocalFile(musicFilePath));
    serialThread = new SerialThread(this);
    connect(serialThread, &SerialThread::dataReceived, this, &MainWindow::handleData);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateChart);
      // 更新频率为200ms

    chart_ch1 = new QChart;
    ui->widget_ch1->setChart(chart_ch1);

    chart_ch2 = new QChart;
    ui->widget_ch2->setChart(chart_ch2);

    chart_ch3 = new QChart;
    ui->widget_ch3->setChart(chart_ch3);
    chart_ch1->legend()->hide();
    chart_ch2->legend()->hide();
    chart_ch3->legend()->hide();
    series_ch1 = new QLineSeries;
    series_ch2 = new QLineSeries;
    series_ch3 = new QLineSeries;
    series_ch1->setPointsVisible(false);
   /* series_ch1->setName("CH1");
    series_ch2->setName("CH2");
    series_ch3->setName("CH3");
*/
    chart_ch1->addSeries(series_ch1);
    chart_ch2->addSeries(series_ch2);
    chart_ch3->addSeries(series_ch3);
     //添加数据绘制
        //创建坐标轴
    axisX_ch1 = new QValueAxis;
    axisX_ch1->setRange(0,500);
    chart_ch1->setAxisX(axisX_ch1,series_ch1);
    QValueAxis* axisY_ch1 = new QValueAxis;
    axisY_ch1->setRange(0, 100);
    chart_ch1->setAxisY(axisY_ch1,series_ch1);
    axisX_ch2 = new QValueAxis;
    axisX_ch2->setRange(0,500);
    chart_ch2->setAxisX(axisX_ch2,series_ch2);
    QValueAxis* axisY_ch2 = new QValueAxis;
    axisY_ch2->setRange(0, 100);
    chart_ch2->setAxisY(axisY_ch2,series_ch2);
    axisX_ch3 = new QValueAxis;
    axisX_ch3->setRange(0,500);
    chart_ch3->setAxisX(axisX_ch3,series_ch3);
    QValueAxis* axisY_ch3 = new QValueAxis;
    axisY_ch3->setRange(0, 100);
    chart_ch3->setAxisY(axisY_ch3,series_ch3);


}
void MainWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{

       if (status == QMediaPlayer::EndOfMedia) {
           qDebug()<<"a";
           ui->pushButton_2->setText("音乐");
       }
}
void MainWindow::closeEvent(QCloseEvent *event) {
    // 发送停止信号到串口
    serialThread->serial->write(closearr);
    // 其他清理工作...

    event->accept(); // 接受关闭事件，继续窗口关闭过程
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->pushButton->text()=="采集"){
        ui->pushButton->setText("暂停");
        serialThread->serial->write(openarr);
        timer->start(20);
    }
    else{
        ui->pushButton->setText("采集");

        serialThread->serial->write(closearr);
        timer->stop();
    }

}
void MainWindow::updateChart()
{
    newCh1.setY(ch1EEG.last());
    newCh2.setY(ch2EEG.last());
    newCh3.setY(ch3EEG.last());
    if(pointIndex>500){
        axisX_ch1->setRange(pointIndex-499,pointIndex);
        axisX_ch2->setRange(pointIndex-499,pointIndex);
        axisX_ch3->setRange(pointIndex-499,pointIndex);
        newCh1.setX(pointIndex);
        newCh2.setX(pointIndex);
        newCh3.setX(pointIndex);
        series_ch1->append(newCh1);
        series_ch2->append(newCh2);
        series_ch3->append(newCh3);
        pointIndex++;
    }
    else{
        newCh1.setX(pointIndex);
        newCh2.setX(pointIndex);
        newCh3.setX(pointIndex);
        series_ch1->append(newCh1);
        series_ch2->append(newCh2);
        series_ch3->append(newCh3);
        pointIndex++;
    }
}
void MainWindow::handleData(const QByteArray &data)
{
    // 在这里处理从串口读取的数据
   // QString hexStr = data.toHex(' ').toUpper();
   // ui->textEdit->append(hexStr);

    QByteArray EEGData = data.mid(12, 152);
    QByteArray batteryData = data.mid(164, 2);
           // 转换为浮点数
    float batteryPercentage = static_cast<unsigned char>(batteryData[1]) + static_cast<unsigned char>(batteryData[0]) / 100.0;
          // 显示电量百分比
    ui->lineEdit->setText(QString("%1%").arg(batteryPercentage, 0, 'f', 2));

    for (int i = 0; i < 152; i += 19) {

           // 为每个通道解析一个数据点
        value1 = static_cast<unsigned char>(EEGData[i+0]) + (static_cast<unsigned char>(EEGData[i +1 ]) << 8) + (static_cast<unsigned char>(EEGData[i + 2]) << 16);
        value2 = static_cast<unsigned char>(EEGData[i + 3]) + (static_cast<unsigned char>(EEGData[i + 4]) << 8) + (static_cast<unsigned char>(EEGData[i + 5]) << 16);
        value3 = static_cast<unsigned char>(EEGData[i + 6]) + (static_cast<unsigned char>(EEGData[i + 7]) << 8) + (static_cast<unsigned char>(EEGData[i + 8]) << 16);
        if (value1 & 0x800000) { // 如果符号位为1，表示这是一个负数
               // 转换为原码
            value1 = ~value1 + 1;
            value1 = value1 & 0xFFFFFF; // 保留24位
            value1 = -value1; // 保留符号
        }

        if (value2 & 0x800000) { // 如果符号位为1，表示这是一个负数
               // 转换为原码
            value2 = ~value2 + 1;
            value2 = value2 & 0xFFFFFF; // 保留24位
            value2 = -value2; // 保留符号
        }
        if (value3 & 0x800000) { // 如果符号位为1，表示这是一个负数
               // 转换为原码
            value3 = ~value3 + 1;
            value3 = value3 & 0xFFFFFF; // 保留24位
            value3 = -value3; // 保留符号
        }// 计算真实电压值
/*
        QByteArray a =EEGData.mid(3,3);
        QString hexStr = a.toHex(' ').toUpper();
        //qDebug()<<hexStr;
*/
        double real_value1 = value1 * 4.5 * 1000 / 8388608 / 12; // 计算公式
        double real_value2 = value2 * 4.5 * 1000 / 8388608 / 12; // 计算公式
        double real_value3 = value3 * 4.5 * 1000 / 8388608 / 12; // 计算公式
        ch1EEG.push_back(real_value1);
        ch2EEG.push_back(real_value2);
        ch3EEG.push_back(real_value3);
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    if(ui->pushButton_2->text()=="音乐"){
        ui->pushButton_2->setText("暂停");
        player->play();

    }
    else{
        ui->pushButton_2->setText("音乐");
        player->pause();
    }

}
//打开串口
void MainWindow::on_pushButton_3_clicked()
{
    if(ui->pushButton_3->text()=="打开串口"){
        ui->pushButton_3->setText("关闭串口");
        serialThread->serial->setPortName(ui->portBox->currentText());
        if(serialThread->serial->open(QIODevice::ReadWrite)) {
            // 设置波特率、数据位、停止位和奇偶校验
            serialThread->serial->setBaudRate(QSerialPort::Baud460800);
            serialThread->serial->setDataBits(QSerialPort::Data8);
            serialThread->serial->setParity(QSerialPort::NoParity);
            serialThread->serial->setStopBits(QSerialPort::OneStop);
            serialThread->serial->setFlowControl(QSerialPort::NoFlowControl);
            ui->textEdit->append(ui->portBox->currentText()+"已连接");
    }
        else {
            QSerialPort::SerialPortError serialError = serialThread->serial->error();
               QString errorString = serialThread->serial->errorString();
               ui->textEdit->append("Failed to open port! Error:"+errorString);
               //qDebug() <<  << serialError << "Error string:" << ;
           }
    }
    else{
        ui->pushButton_3->setText("打开串口");
        ui->textEdit->append(ui->portBox->currentText()+"已关闭");
        serialThread->serial->clear();//针对的缓存清空
        serialThread->serial->close();//针对于设备接口关闭
    }

}
//重新搜索串口并打印在ui上
void MainWindow::on_pushButton_4_clicked()
{
    ui->portBox->clear();
    foreach(const QSerialPortInfo &info,
            QSerialPortInfo::availablePorts()){
        //查询出有哪些串口设备，并将其打印出来
        QSerialPort serival;
        serival.setPort(info);
        if(serival.open(QIODevice::ReadWrite)){
            ui->textEdit->append(serival.portName());//控制台输出的信息
            //在图形中的下拉框中显示串口的名字信息
            ui->portBox->addItem(serival.portName());
            serival.close();
        }
    }
}

void MainWindow::on_minButton_clicked()
{
    this->showMinimized();
}

void MainWindow::on_closeButton_clicked()
{
    this->close();
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x=ui->widget->x();
    int y=ui->widget->y();
    int w=ui->widget->width();
    int h=ui->widget->height();
    //只能是鼠标左键移动和改变大小
    if((event->button() == Qt::LeftButton) //处于左键状态
        &&(event->x()>x&&event->x()<x+w)  //x坐标位置判定
        &&(event->y()>y&&event->y()<y+h)) //y坐标位置判定
    {
    m_leftMousePressed = true;  //标志位置为真
    //按下时鼠标左键时，窗口在屏幕中的坐标
    m_StartPoint = event->globalPos();
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //移动窗口,由于取消了标题栏，因此需要自己实现拖动窗口功能
    if (m_leftMousePressed)
    {
        QPoint curPoint = event->globalPos();   //按住移动时的位置
        QPoint movePoint = curPoint - m_StartPoint; //与初始坐标做差，得位移
        //普通窗口
        QPoint mainWinPos = this->pos();
        //设置窗口的全局坐标
        this->move(mainWinPos.x() + movePoint.x(), mainWinPos.y() + movePoint.y());
        m_StartPoint = curPoint;
     }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_leftMousePressed = false;//释放鼠标，标志位置为假
}
