#include "VideoWidget.h"

#include <QPainter>

#include <QMutexLocker>

#include <QDebug>
#include <QThread>
VideoWidget::VideoWidget(QWidget *parent)
    : QWidget(parent)
{
    connect(this, &VideoWidget::pushImage,
            this, &VideoWidget::onPushImage, Qt::QueuedConnection);
}


void VideoWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    if (drawingImage.isNull())
    {
        return;
    }

    auto scaledImage = drawingImage.scaled(size(), Qt::KeepAspectRatio);
    QRect imageRect(QPoint(0, 0), scaledImage.size());
    imageRect.moveCenter(rect().center());
    p.drawImage(imageRect.x(), imageRect.y(), scaledImage);
}

void VideoWidget::onPushImage(const QImage &image)
{
    drawingImage = image;
    update();
}
