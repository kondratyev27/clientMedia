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

    static void start(QString &fileName, const QString &username = QString(), const QString &password = QString());
    static void stop();

signals:

public slots:

private:

    explicit Singleton(QObject *parent = nullptr);

    bool isStarted = false;
    VideoWidget *pVideoWidget;
};

#endif // SINGLETON_H
