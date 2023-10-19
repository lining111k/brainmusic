#include "music.h"
#include "mainwindow.h"
#include<QProcess>
#include <QLabel>
#include <QDebug>
#include <QSound>
MusicThread::MusicThread(QObject *parent):
    QThread(parent),
    m_paused(false),
    m_stopFlag(false)

{
    player = new  QMediaPlayer;
    player->setVolume(50);
    musicFilePath = "F:/techFair/myproject/bwm1.wav";

}

MusicThread::~MusicThread()
{
}
void MusicThread::setFilePath(const QString &filePath)
{
    musicFilePath = filePath;
}

void MusicThread::run()
{

    if (!QFileInfo::exists(musicFilePath)) {
            qWarning() << "The music file doesn't exist: " << musicFilePath;
            return ;
        }

        // 设置要播放的内容
    player->setMedia(QUrl::fromLocalFile(musicFilePath));
    qDebug()<<"s";
    player->play(); // 开始播放
exec();
    // 在需要时暂停

    //QProcess p;
      //  p.start("aplay " + m_filePath);
       // p.waitForFinished();

}
void MusicThread::pause()
{
    player->pause();
}

