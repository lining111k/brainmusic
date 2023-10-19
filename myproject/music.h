#ifndef MUSIC_H
#define MUSIC_H
#include <QAudioFormat>
#include <QAudioOutput>
#include <QFile>
#include <QThread>
#include <QMutex>
#include <QDebug>
#include <QMediaPlayer>
#include <QBuffer>
#include <QWaitCondition>
class MainWindow;
class QLabel;


struct music
{
    QString name;
};

//声明元类型
Q_DECLARE_METATYPE(music)

class MusicThread : public QThread {
    Q_OBJECT

public:
    explicit MusicThread(QObject *parent = 0);
    virtual ~MusicThread();

    void setFilePath(const QString &filePath);
    virtual void run();
    void pause();

protected:

private slots:


private:
    QString musicFilePath;
    bool m_paused;
    bool m_stopFlag;
    QMediaPlayer *player;
};

#endif // MUSIC_H
