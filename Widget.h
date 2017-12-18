#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>

#include <QTcpSocket>

#include <QListWidgetItem>

#include <ServerParams.h>

class QListWidget;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    void closeEvent(QCloseEvent *event);

private slots:
    void onReadyRead();

    void onStartClicked();
    void onStopClicked();
    void onSettingsClicked();

    void onStreamingError();

private:
    ServerParams readParams();
    void saveParams(const ServerParams &params);
    void createSocket();
    void requestData(const ServerParams &params);
    void resetCurrentItem();

    QListWidgetItem *pCurrentItem = nullptr;

    QListWidget *pListWidget;
    QTcpSocket socket;
    ServerParams serverParams;
};

#endif // WIDGET_H
