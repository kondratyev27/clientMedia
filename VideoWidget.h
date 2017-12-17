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
signals:
    void pushImage(const QImage &image);

private slots:
    void onPushImage(const QImage &image);

private:
    QImage drawingImage;

};

#endif // VIDEOWIDGET_H
