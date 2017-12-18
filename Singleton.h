#ifndef SINGLETON_H
#define SINGLETON_H

#include <QObject>

#include <VideoWidget.h>
#include <MCU/Core/Container.hpp>



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

public slots:

private:

    explicit Singleton(QObject *parent = nullptr);

    bool isStarted = false;
    VideoWidget *pVideoWidget;

    QString userName = "loh";
    QString password = "loh";
};

#endif // SINGLETON_H
