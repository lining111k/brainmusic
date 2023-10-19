#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtCharts>
#include "SerialThread.h"
#include<myserialport.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void handleData(const QByteArray &data);
    void Slot_OpenCom();
    void updateChart();

signals:
    void Sig_StartThread();
    void Sig_CloseThread();
private:
    mySerialPort *GpsSerialPort;
    int  pointIndex=0;
    QList<QPointF> newCh1;
    QList<QPointF> newCh2;
    QList<QPointF> newCh3;
    SerialThread *serialThread;
    Ui::MainWindow *ui;
    QLineSeries* series_ch1;
    QLineSeries* series_ch2;
    QLineSeries* series_ch3;
    QChart *chart_ch1;
    int EEGi=0;
    QChart *chart_ch2;
    QChart *chart_ch3;
};

#endif // MAINWINDOW_H
