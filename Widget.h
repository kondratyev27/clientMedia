#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>

#include <QTcpSocket>

#include <QListWidgetItem>

class QListWidget;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void onReadyRead();

    void onStartClicked();
    void onStopClicked();

    void resetCurrentItem();

private:
    void createSocket();

    QListWidgetItem *pCurrentItem = nullptr;

    QListWidget *pListWidget;
    QTcpSocket socket;
};

#endif // WIDGET_H
