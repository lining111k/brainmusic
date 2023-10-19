#include "myserialport.h"

mySerialPort::mySerialPort(QString port,int bara)
{
    COM = port;
    BauaRate = bara;
    isConnectFlag = true;
    myPort = new QSerialPort();
    thread = new QThread();
    this->moveToThread(thread);
    myPort->moveToThread(thread);
    connect(thread,SIGNAL(started()),this,SLOT(Slot_OpenComPort()));
    qDebug()<<"创建对象初始化线程为:"<<QThread::currentThread();
}
void mySerialPort::SLot_StartThread()
{
    if(!thread->isRunning()){
        thread->start();
        qDebug()<<"线程开始了,线程号："<<QThread::currentThread();
    }
    else{
        qDebug()<<"线程正在运行："<<QThread::currentThread();
    }
}
void mySerialPort::Slot_OpenComPort()
{
    myPort->setPortName(COM);
    myPort->setBaudRate(BauaRate);
    myPort->setDataBits(QSerialPort::Data8);
    myPort->setStopBits(QSerialPort::OneStop);
    myPort->setParity(QSerialPort::NoParity);
    myPort->setFlowControl(QSerialPort::NoFlowControl);
    if(myPort->open(QIODevice::ReadWrite))
    {
        qDebug()<<"串口打开成功，子线程号"<<QThread::currentThread();
        if(isConnectFlag)
        {
            connect(myPort,SIGNAL(readyRead()),this,SLOT(Slot_ReadSerialPortData()));
            isConnectFlag = false;
        }
    }
    else
    {
        qDebug()<<"串口打开失败";
    }
}
void mySerialPort::Slot_ReadSerialPortData()
{
    qDebug()<<"读数据，子线程号"<<QThread::currentThread();
    QByteArray buf = myPort->readAll();
    if(!buf.isEmpty()){
        QString str = buf;
        qDebug()<<str;
        emit Sig_SendSerialPortData(str);
    }
    buf.clear();
}
void mySerialPort::SLot_CloseThread()
{
    qDebug()<<"析构函数执行线程："<<QThread::currentThread();
    //关闭串口
    myPort->clear();
    myPort->close();
    //myPort->deleteLater();

    //杀死线程
    if(thread->isRunning())
    {
        thread->quit();
        thread->wait();
        //thread->deleteLater();
    }
}
