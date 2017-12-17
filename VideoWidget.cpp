#include "VideoWidget.h"

#include <QPainter>

#include <QMutexLocker>

#include <QDebug>
#include <QThread>
VideoWidget::VideoWidget(QWidget *parent)
    : QWidget(parent)
{
}


void VideoWidget::paintEvent(QPaintEvent *event)
{
    QMutexLocker mlocker(&mutex);
    QPainter p(this);
    if (drawingImage.isNull())
    {
        return;
    }

    QImage image(drawingImage.bits(), drawingImage.width(), drawingImage.height(), drawingImage.format());
    bits = image.bits();
    p.drawImage(0, 0, image.copy());
}

void VideoWidget::emitPushImage(const QImage &image)
{
    mutex.lock();
    drawingImage = image;
    mutex.unlock();
    repaint();
}

uchar *VideoWidget::getBits() const
{
    return bits;
}
