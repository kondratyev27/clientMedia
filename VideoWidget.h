#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QImage>

#include <QTimer>

class VideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;
    bool isEmpthy();

    void closeEvent(QCloseEvent *event) override;
    void clear();
signals:
    void pushImage(const QImage &image);

    void dataStreamingFinished();

private slots:
    void onPushImage(const QImage &image);

private:
    void updateScaledImage();

    QImage originalImage;
    QImage scaledImage;
    QPoint drawingPoint;
    QTimer timer;

};

#endif // VIDEOWIDGET_H
