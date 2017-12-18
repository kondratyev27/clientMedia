#include "VideoWidget.h"

#include <QPainter>

#include <QCloseEvent>
#include <Singleton.h>

#include <QDebug>
#include <QThread>
VideoWidget::VideoWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Контент");
    connect(this, &VideoWidget::pushImage,
            this, &VideoWidget::onPushImage, Qt::QueuedConnection);
}


void VideoWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    if (scaledImage.isNull())
    {
        return;
    }

    p.drawImage(drawingPoint, scaledImage);
}

bool VideoWidget::isEmpthy()
{
    return scaledImage.isNull();
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
    show();
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
