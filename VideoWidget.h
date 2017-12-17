#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QImage>

#include <QMutex>

class VideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

    void emitPushImage(const QImage &image);

    uchar *getBits() const;

private:

    QMutex mutex;
    QImage drawingImage;
    uchar *bits;

};

#endif // VIDEOWIDGET_H
