#include "Widget.h"

#include <QApplication>
#include <QScreen>
#include <QListWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSettings>
#include <QMessageBox>
#include <AuthorizationDialog.h>

#include <Singleton.h>
#include <QLabel>

#include <SettingsDialog.h>

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      pListWidget(new QListWidget()),
      serverParams(readParams())
{
    setWindowTitle("Главное окно");
    auto startButton = new QPushButton("Старт");
    connect(startButton, &QPushButton::clicked,
            this, &Widget::onStartClicked);

    auto stopButton = new QPushButton("Стоп");
    connect(stopButton, &QPushButton::clicked,
            this, &Widget::onStopClicked);

    auto settingsButton = new QPushButton("Настройки");
    connect(settingsButton, &QPushButton::clicked,
            this, &Widget::onSettingsClicked);

    connect(pListWidget, &QListWidget::doubleClicked, this, &Widget::onStartClicked);

    QHBoxLayout *buttonsLay = new QHBoxLayout();
    buttonsLay->addWidget(settingsButton);
    buttonsLay->addStretch();
    buttonsLay->addWidget(startButton);
    buttonsLay->addWidget(stopButton);

    QVBoxLayout *mainLay = new QVBoxLayout(this);
    mainLay->addWidget(new QLabel("Доступные файлы:"));
    mainLay->addWidget(pListWidget);
    mainLay->addLayout(buttonsLay);

    createSocket();
    requestData(serverParams);

    connect(&Singleton::instance(), &Singleton::streamingError, this, &Widget::onStreamingError);
}

Widget::~Widget()
{
}

void Widget::closeEvent(QCloseEvent *event)
{
    QApplication::quit();
}

void Widget::onReadyRead()
{
    resetCurrentItem();
    pListWidget->clear();
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

    AuthorizationDialog dlg(this);
    dlg.setFixedSize(dlg.sizeHint());
    if (dlg.exec() == QDialog::Rejected)
    {
        return;
    }

    Singleton::setUserParams(dlg.userName(), dlg.password());
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

void Widget::onSettingsClicked()
{
    SettingsDialog dlg(this);
    dlg.setFixedSize(dlg.sizeHint());
    dlg.setParams(serverParams);
    if (dlg.exec() == QDialog::Accepted)
    {
        auto &&params = dlg.getParams();
        saveParams(params);
        requestData(params);
    }
}

void Widget::onStreamingError()
{
    resetCurrentItem();
    QMessageBox::critical(this, "Ошибка", "Ошибка авторизации!");
}

ServerParams Widget::readParams()
{
    QSettings settings;
    return {settings.value("host").toString(), settings.value("port", 0).toUInt()};
}

void Widget::saveParams(const ServerParams &params)
{
    QSettings settings;
    settings.setValue("host", params.host);
    settings.setValue("port", params.port);
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
//    socket.connectToHost("192.168.102.50", 49999);
}

void Widget::requestData(const ServerParams &params)
{
    if (socket.isOpen())
    {
        socket.disconnectFromHost();
    }

    socket.connectToHost(params.host, params.port);
}
