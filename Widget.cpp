#include "Widget.h"

#include <QApplication>
#include <QScreen>
#include <QListWidget>
#include <QHBoxLayout>
#include <QPushButton>

#include <Singleton.h>

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      pListWidget(new QListWidget())
{
    auto startButton = new QPushButton("Старт");
    connect(startButton, &QPushButton::clicked,
            this, &Widget::onStartClicked);

    auto stopButton = new QPushButton("Стоп");
    connect(stopButton, &QPushButton::clicked,
            this, &Widget::onStopClicked);

    QHBoxLayout *buttonsLay = new QHBoxLayout();
    buttonsLay->addStretch();
    buttonsLay->addWidget(startButton);
    buttonsLay->addWidget(stopButton);

    QVBoxLayout *mainLay = new QVBoxLayout(this);
    mainLay->addLayout(buttonsLay);
    mainLay->addWidget(pListWidget);

    createSocket();
}

Widget::~Widget()
{
}

void Widget::onReadyRead()
{
    qDebug()<<Q_FUNC_INFO;
    auto data = socket.readAll();
    qDebug()<<"data =" << data;
    QString str(data);
    pListWidget->addItems(str.split(","));
}

void Widget::onStartClicked()
{
    auto selectedItem = pListWidget->currentIndex();
    auto fileName = selectedItem.data(Qt::DisplayRole).toString();
    Singleton::start(fileName);
}

void Widget::onStopClicked()
{
    qDebug()<<"11111111111";
    Singleton::stop();
    qDebug()<<"2222222222222";
}

void Widget::createSocket()
{
    connect(&socket, &QTcpSocket::readyRead, this, &Widget::onReadyRead);
    connect(&socket, &QTcpSocket::connected, this, [](){
        qDebug()<<"connected!";
    });
    connect(&socket,static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>
            (&QTcpSocket::error), this, [](QAbstractSocket::SocketError error)
    {
        qDebug()<<"Error ="<<error;
    });
    socket.connectToHost("192.168.102.50", 49999);
}
