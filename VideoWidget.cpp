#include "VideoWidget.h"

#include <QPainter>

#include <QDebug>
VideoWidget::VideoWidget(QWidget *parent)
    : QWidget(parent)
{
    connect(this, &VideoWidget::pushImage,
            this, &VideoWidget::onPushImage,
			Qt:: DirectConnection/* QueuedConnection*/);
}


void VideoWidget::onPushImage(const QImage &image)
{
    drawingImage = image;
	qDebug()<<"try draw";
    repaint();
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    if (drawingImage.isNull())
    {
        return;
    }

    p.drawImage(0, drawingImage.height(), drawingImage);
}

void VideoWidget::emitPushImage(const QImage &image)
{
    emit pushImage(image);
}
