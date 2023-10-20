#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtCharts>
#include <QRandomGenerator>

#include "SerialThread.h"
#include "music.h"
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
    void updateChart();


    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_minButton_clicked();

    void on_closeButton_clicked();

private:
    void closeEvent(QCloseEvent *event) override;
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    int  pointIndex=0;
    int value1;
    int value2;
    int value3;
    QTimer *timer;
    QByteArray openarr  = QByteArray::fromHex("4354524C000300030D0A");
    QByteArray closearr = QByteArray::fromHex("4354524C000300040D0A");
    QVector<double> ch1EEG{0.0,0.0,0.0};
    QVector<double> ch2EEG{0.0,0.0,0.0};
    QVector<double> ch3EEG{0.0,0.0,0.0};
    QPointF newCh1;
    QPointF newCh2;
    QPointF newCh3;
    SerialThread *serialThread= nullptr;
    MusicThread *music_thread = nullptr;
    QMediaPlayer *player;
    Ui::MainWindow *ui;
    QLineSeries* series_ch1;
    QLineSeries* series_ch2;
    QLineSeries* series_ch3;
    QValueAxis* axisX_ch1;
    QValueAxis* axisX_ch2;
    QValueAxis* axisX_ch3;
    QChart *chart_ch1;
    int EEGi=0;
    QChart *chart_ch2;
    QChart *chart_ch3;
    bool  m_leftMousePressed;
    QPoint m_StartPoint;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // MAINWINDOW_H
