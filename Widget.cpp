#include "Widget.h"

#include <QApplication>
#include <QScreen>
#include <QListWidget>
#include <QHBoxLayout>
#include <QPushButton>

#include <Singleton.h>
#include <QLabel>

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      pListWidget(new QListWidget())
{
    setWindowTitle("Главное окно");
    auto startButton = new QPushButton("Старт");
    connect(startButton, &QPushButton::clicked,
            this, &Widget::onStartClicked);

    auto stopButton = new QPushButton("Стоп");
    connect(stopButton, &QPushButton::clicked,
            this, &Widget::onStopClicked);

    connect(pListWidget, &QListWidget::doubleClicked, this, &Widget::onStartClicked);

    QHBoxLayout *buttonsLay = new QHBoxLayout();
    buttonsLay->addStretch();
    buttonsLay->addWidget(startButton);
    buttonsLay->addWidget(stopButton);

    QVBoxLayout *mainLay = new QVBoxLayout(this);
    mainLay->addWidget(new QLabel("Доступные файлы:"));
    mainLay->addWidget(pListWidget);
    mainLay->addLayout(buttonsLay);

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
    resetCurrentItem();
    pCurrentItem = pListWidget->currentItem();
    if (pCurrentItem == nullptr)
    {
        return;
    }
    pCurrentItem->setData(Qt::BackgroundRole, QBrush(QColor(193, 222, 232)));
    auto fileName = pCurrentItem->data(Qt::DisplayRole).toString();
    Singleton::start(fileName);

    pListWidget->selectionModel()->setCurrentIndex(QModelIndex(), QItemSelectionModel::Clear);
}

void Widget::onStopClicked()
{
    resetCurrentItem();
    qDebug()<<"11111111111";
    Singleton::stop();
    qDebug()<<"2222222222222";
}

void Widget::resetCurrentItem()
{
    if (pCurrentItem == nullptr)
    {
        return;
    }

    pCurrentItem->setData(Qt::BackgroundRole, QBrush(Qt::white));
    pCurrentItem = nullptr;
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
