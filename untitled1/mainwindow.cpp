#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //识别串口设备 测试代码段，用于检测该电脑设备有多少具体的串口设备
    foreach(const QSerialPortInfo &info,
            QSerialPortInfo::availablePorts()){
        //查询出有哪些串口设备，并将其打印出来
        QSerialPort serival;
        serival.setPort(info);
        if(serival.open(QIODevice::ReadWrite)){
            qDebug() << serival.portName();//控制台输出的信息
            //在图形中的下拉框中显示串口的名字信息
            ui->portBox->addItem(serival.portName());
            serival.close();
        }
    }
}
void MainWindow::on_openButton_clicked()
{
    //text()可以获取控件上的文字信息
    if(ui->openButton->text() == tr("打开串口")){
        //用串口对象设置基本信息，用于打开串口使用
        serial = new QSerialPort();//为串口对象申请内存空间
        //设置串口名称
        serial->setPortName(ui->portBox->currentText());
        //打开串口
        serial->open(QIODevice::ReadWrite);
        //设置波特率
        serial->setBaudRate(ui->baundBox->currentText().toInt());
        //设置数据位
        switch(ui->dataBox->currentIndex()){
        case 8:
            serial->setDataBits(QSerialPort::Data8);
            break;
        case 7:
            serial->setDataBits(QSerialPort::Data7);
            break;
        default:
            break;
        }
        //设置校验位  无校验位
        switch(ui->checkBox->currentIndex()){
        case 0:
            serial->setParity(QSerialPort::NoParity);
            break;
        default:
            break;
        }
        //设置停止位
        switch(ui->stopBox->currentIndex()){
        case 1:
            serial->setStopBits(QSerialPort::OneStop);
            break;
        case 2:
            serial->setStopBits(QSerialPort::TwoStop);
            break;
        default:
            break;
        }
        //设置控制流  大多数的串口工具都是默认无控制流的
        serial->setFlowControl(QSerialPort::NoFlowControl);
        //在空白区显示数据（建立独立封装为函数），调用其他的函数
        //以代码方式建立信号与槽函数的关联
        connect(serial,SIGNAL(readyRead()),this,SLOT(readData()));
        //禁止使用下拉框的选项
        //setEnabled() 控制控件的可用性  true可用 false不可用
        ui->portBox->setEnabled(false);
        //setText()为控件设置文字信息
        ui->openButton->setText(tr("关闭串口"));
    }else {
        //关闭串口
        serial->clear();//针对的缓存清空
        serial->close();//针对于设备接口关闭
        serial->deleteLater();//释放资源
        //可用性开启
        ui->portBox->setEnabled(true);
        ui->openButton->setText(tr("打开串口"));
    }
}

void MainWindow::readData()
{
    //设置缓冲区用于接收数据
    QByteArray buf;
    buf = serial->readAll();

    if(!buf.isEmpty()){
        QString str = ui->textEdit->toPlainText();
        str += tr(buf);
        ui->textEdit->clear();
        ui->textEdit->append(str + '\n');

    }
    buf.clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    serial->write(ui->lineEdit->text().toUtf8());
    ui->lineEdit->setText("");
}
