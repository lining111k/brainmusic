#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serialThread = new SerialThread(this);
    connect(serialThread, &SerialThread::dataReceived, this, &MainWindow::handleData);
    /*
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateChart);
    timer->start(1000);  // 更新频率为200ms
*/
    chart_ch1 = new QChart;
    ui->widget_ch1->setChart(chart_ch1);

    chart_ch2 = new QChart;
    ui->widget_ch2->setChart(chart_ch2);

    chart_ch3 = new QChart;
    ui->widget_ch3->setChart(chart_ch3);

    series_ch1 = new QLineSeries;
    series_ch2 = new QLineSeries;
    series_ch3 = new QLineSeries;
    series_ch1->setName("CH1");
    series_ch2->setName("CH2");
    series_ch3->setName("CH3");

    chart_ch1->addSeries(series_ch1);
    chart_ch2->addSeries(series_ch2);
    chart_ch3->addSeries(series_ch3);
     //添加数据绘制
        //创建坐标轴
    QValueAxis* axisX_ch1 = new QValueAxis;
    axisX_ch1->setRange(0,100);
    chart_ch1->setAxisX(axisX_ch1,series_ch1);
    QValueAxis* axisY_ch1 = new QValueAxis;
    axisY_ch1->setRange(0, 10);
    chart_ch1->setAxisY(axisY_ch1,series_ch1);
    QValueAxis* axisX_ch2 = new QValueAxis;
    axisX_ch2->setRange(0,100);
    chart_ch2->setAxisX(axisX_ch2,series_ch2);
    QValueAxis* axisY_ch2 = new QValueAxis;
    axisY_ch2->setRange(0, 10);
    chart_ch2->setAxisY(axisY_ch2,series_ch2);
    QValueAxis* axisX_ch3 = new QValueAxis;
    axisX_ch3->setRange(0,100);
    chart_ch3->setAxisX(axisX_ch3,series_ch3);
    QValueAxis* axisY_ch3 = new QValueAxis;
    axisY_ch3->setRange(0, 10);
    chart_ch3->setAxisY(axisY_ch3,series_ch3);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->pushButton->text()=="采集"){
        ui->pushButton->setText("关闭");
        serialThread->start();

    }
    else{
        ui->pushButton->setText("采集");

    }
}
void MainWindow::updateChart()
{
    series_ch1->append(newCh1);
    newCh1.clear();
}
void MainWindow::handleData(const QByteArray &data)
{
    // 在这里处理从串口读取的数据
    QString hexStr = data.toHex(' ').toUpper();
    ui->textEdit->append(hexStr);

    QByteArray EEGData = data.mid(12, 152);
    QByteArray batteryData = data.mid(164, 2);
           // 转换为浮点数
    float batteryPercentage = static_cast<unsigned char>(batteryData[1]) + static_cast<unsigned char>(batteryData[0]) / 100.0;

          // 显示电量百分比
    ui->lineEdit->setText(QString("%1%").arg(batteryPercentage, 0, 'f', 2));

    for (int i = 0; i < 152; i += 19, pointIndex++) {
           // 为每个通道解析一个数据点
           int value1 = static_cast<unsigned char>(data[i]) + (static_cast<unsigned char>(data[i + 1]) << 8) + (static_cast<unsigned char>(data[i + 2]) << 16);
           int value2 = static_cast<unsigned char>(data[i + 3]) + (static_cast<unsigned char>(data[i + 4]) << 8) + (static_cast<unsigned char>(data[i + 5]) << 16);
           int value3 = static_cast<unsigned char>(data[i + 6]) + (static_cast<unsigned char>(data[i + 7]) << 8) + (static_cast<unsigned char>(data[i + 8]) << 16);

           newCh1.append(QPointF(pointIndex, value1%10));
           newCh1.append(QPointF(pointIndex, value1));
           newCh1.append(QPointF(pointIndex, value1));
           /*series_ch1->append(newCh1);
           newCh1.clear();*/
       }
}
