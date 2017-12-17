#include "Singleton.h"

Singleton &Singleton::instance()
{
    static Singleton self;
    return self;
}

void Singleton::appendImage(const QImage &image)
{
    emit instance().pVideoWidget->pushImage(image.copy());
}

Singleton::Singleton(QObject *parent)
    : QObject(parent),
      pVideoWidget(new VideoWidget)
{
    pVideoWidget->show();
}
