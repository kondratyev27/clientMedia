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

    static void setUserParams(const QString &userName, const QString &password);
    static void start(QString &fileName);
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

    QString userName = "loh";
    QString password = "loh";
};

#endif // SINGLETON_H
