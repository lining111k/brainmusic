// SerialThread.cpp
#include "SerialThread.h"
#include <QSerialPortInfo>
#include <QDebug>
SerialThread::SerialThread(QObject *parent)
    : QThread(parent)
{
    // 初始化串口，例如设置串口名、波特率等
    serial = new QSerialPort();
    connect(serial,SIGNAL(readyRead()),this,SLOT(readData()));

}

SerialThread::~SerialThread()
{
    QByteArray arr;
    arr += static_cast<char>(0x43);
    arr += static_cast<char>(0x54);
    arr += static_cast<char>(0x52);
    arr += static_cast<char>(0x4C);
    arr += static_cast<char>(0x00);
    arr += static_cast<char>(0x03);
    arr += static_cast<char>(0x00);
    arr += static_cast<char>(0x04);
    arr += static_cast<char>(0x0D);
    arr += static_cast<char>(0x0A);
    serial->write(arr);
    serial->close();
    delete serial;
}

void SerialThread::serialLink()
{
    if(serial->open(QIODevice::ReadWrite)) {
        // 设置波特率、数据位、停止位和奇偶校验
        serial->setBaudRate(QSerialPort::Baud460800);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
    } else {
        qDebug() << "Failed to open port!";
    }
}
void SerialThread::run()
{

}
void SerialThread::readData()
{
    // 设置缓冲区用于接收数据
    buffer += serial->readAll();

    while (!buffer.isEmpty()) {
        // 首先检查是否有足够的数据
        if (buffer.size() < 174) {
            break;  // 缓冲区中的数据不足174字节，退出循环
        }

        // 检查包头
        if (buffer.startsWith(PACKET_HEADER)) {
            QByteArray packet = buffer.left(174);
            buffer.remove(0, 174);
            emit dataReceived(packet);
        } else {
            // 查找包头
            //qDebug() << "丢包一次";
            int headerIndex = buffer.indexOf(PACKET_HEADER);

            // 如果没有找到包头，清空缓冲区并退出
            if (headerIndex == -1) {
                buffer.clear();
                break;
            }

            // 如果包头不在缓冲区的开始，移除前面的数据

            buffer.remove(0, headerIndex);
        }
    }
}
