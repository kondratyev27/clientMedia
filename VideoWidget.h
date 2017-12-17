#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QImage>

class VideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

    void emitPushImage(const QImage &image);

signals:
    void pushImage(const QImage &image);

public slots:

private slots:
    void onPushImage(const QImage &image);

private:

    QImage drawingImage;

};

#endif // VIDEOWIDGET_H
