#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H
#include <QThread>
#include <QString>
#include <qdebug>
#include<QtSerialPort/QSerialPort>
#include<QtSerialPort/QSerialPortInfo>
class mySerialPort : public QObject
{
    Q_OBJECT
public:
    mySerialPort(QString port,int bara);
private:
    QString COM;
    int BauaRate;

    QSerialPort *myPort;
    QThread *thread;
    bool isConnectFlag;
signals:
    void Sig_SendSerialPortData(QString);
public slots:
    void SLot_StartThread();//槽函数1
    void Slot_OpenComPort();//槽函数2
    void Slot_ReadSerialPortData();//槽函数3

    void SLot_CloseThread();
};

#endif // MYSERIALPORT_H
