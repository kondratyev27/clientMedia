#ifndef SINGLETON_H
#define SINGLETON_H

#include <QObject>

#include <VideoWidget.h>

class Singleton : public QObject
{
    Q_OBJECT
public:

    static Singleton &instance();

    static void appendImage(const QImage &image);

signals:

public slots:

private:

    explicit Singleton(QObject *parent = nullptr);

    VideoWidget *pVideoWidget;
};

#endif // SINGLETON_H
