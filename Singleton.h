#ifndef SINGLETON_H
#define SINGLETON_H

#include <QObject>

#include <VideoWidget.h>
#include <MCU/Core/Container.hpp>

#include <QTimer>



class Singleton : public QObject
{
    Q_OBJECT
public:

    static Singleton &instance();

    static void appendImage(const QImage &image);

    static void start(QString &fileName, const QString &userName, const QString &password);
    static void stop();

signals:
    void streamingError();

public slots:

private slots:
    void onTimerTimeout();

private:

    explicit Singleton(QObject *parent = nullptr);

    bool isStarted = false;
    VideoWidget *pVideoWidget;
    QTimer timer;
};

#endif // SINGLETON_H
