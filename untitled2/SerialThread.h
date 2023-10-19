// SerialThread.h
#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>
class SerialThread : public QThread
{
    Q_OBJECT

public:
    SerialThread(QObject *parent = nullptr);
    ~SerialThread();

    void run() override;

signals:
    void dataReceived(const QByteArray &data);
public slots:

    void readData();
private:
    const QByteArray PACKET_HEADER = QByteArray::fromHex("4441544100020003");
    QByteArray packet;
    QSerialPort *serial;
    QByteArray buffer;
};
