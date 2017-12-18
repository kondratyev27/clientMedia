#include "VideoWidget.h"

#include <QPainter>

#include <QCloseEvent>
#include <Singleton.h>

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
    if (originalImage.isNull())
    {
        return;
    }

    p.drawImage(drawingPoint, scaledImage);
}

void VideoWidget::resizeEvent(QResizeEvent *pEvent)
{
    updateScaledImage();
}

void VideoWidget::clear()
{
   originalImage = QImage();
   updateScaledImage();
}

void VideoWidget::closeEvent(QCloseEvent *event)
{
    event->ignore();
    hide();
    Singleton::stop();
}

void VideoWidget::onPushImage(const QImage &image)
{
    originalImage = image;
    updateScaledImage();
    update();
}

void VideoWidget::updateScaledImage()
{
    if (originalImage.isNull())
    {
        scaledImage = QImage();
        return;
    }

    scaledImage = originalImage.scaled(size(), Qt::KeepAspectRatio, Qt::FastTransformation);
    QRect imageRect(QPoint(0, 0), scaledImage.size());
    imageRect.moveCenter(rect().center());
    drawingPoint = imageRect.topLeft();
}
