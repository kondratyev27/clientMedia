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

    void closeEvent(QCloseEvent *event) override;
    void clear();
signals:
    void pushImage(const QImage &image);

private slots:
    void onPushImage(const QImage &image);

private:
    void updateScaledImage();

    QImage originalImage;
    QImage scaledImage;
    QPoint drawingPoint;

};

#endif // VIDEOWIDGET_H
