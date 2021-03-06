#include "Singleton.h"

#include <QDebug>
#include <QMessageBox>

#include <MCU/Terminations/RTSP/Client.hpp>
//#include <MCU/Terminations/RTSP/Client.hpp>
#include <MCU/Core/Container.hpp>
#include <MCU/Terminations/Conference/VideoConference.hpp>
#include <MCU/Terminations/File/Reader.hpp>
#include <MCU/Terminations/File/Writer.hpp>
#include <MCU/Terminations/Codecs/VideoCodec.hpp>
#include <MCU/Core/ProxyTermination.hpp>
#include <VideoTermiantion.h>

Singleton &Singleton::instance()
{
    static Singleton self;
    return self;
}

void Singleton::appendImage(const QImage &image)
{
    emit instance().pVideoWidget->pushImage(image.copy());
}

void Singleton::start(QString &fileName, const QString &userName, const QString &password)
{
    auto &self = instance();
    stop();

    auto rtsp_args = std::make_shared<MCU::Tm_RTSP_Client::Tm_Args>();
    rtsp_args->m_URL = "rtsp://192.168.102.50:5554/" + fileName.toStdString();
    rtsp_args->m_AuthInfo = MCU::Tm_AuthInfo(userName.toStdString(), password.toStdString());
    auto rc = MCU::Tm_Container::CreateTermination("rtsp", rtsp_args);
    if (!rc)
    {
        auto errorStr = QString("Failed to create server: %1 (%2)").arg((int)rc.m_Cause).arg(QString::fromStdString(rc.m_CauseDescription));
        qDebug() << errorStr;
        return;
    }

    MCU::Tm_Topology topology;
    topology.Add("rtsp", 0, "dec", 0);
    topology.Add("dec", 1, "video", 0);

    if (!MCU::Tm_Container::ModifyTopology("default", topology, true))
    {
        QString errorStr("Ошибка создания топологии");
        qDebug()<<errorStr;
        return;
    }


    self.timer.start();
    self.isStarted = true;
}

void Singleton::stop()
{
    auto &self = instance();
    if (self.isStarted == false)
    {
        return;
    }
    self.timer.stop();
    self.pVideoWidget->setVisible(false);
    self.pVideoWidget->clear();
    MCU::Tm_Topology topology;
    if (!MCU::Tm_Container::ModifyTopology("default", topology, true))
    {
        QString errorStr("Ошибка создания топологии");
        qDebug()<<errorStr;
    }
    qDebug()<<"destroy =" << MCU::Tm_Container::DestroyTermination("rtsp");
    self.isStarted = false;
}

void Singleton::onTimerTimeout()
{
    if (pVideoWidget->isEmpthy())
    {
        emit streamingError();
        stop();
    }
}

void Singleton::onStreamingFinished()
{
    if (isStarted)
    {
        QMessageBox::critical(nullptr, "Ошбика!", "Разрвано соеднинеие с rtsp сервером");
        stop();
    }
}

Singleton::Singleton(QObject *parent)
    : QObject(parent),
      pVideoWidget(new VideoWidget)
{
    if (!MCU::Tm_Container::CreateContext("default"))
    {
        auto errorStr = "Failed to create context";
        qDebug() << errorStr;
    }

    MCU::Tm_VideoCodec::Tm_StreamArgs dec_stream;
    dec_stream.m_Codec = MCU::CODEC_RAW_YUV420;
    auto dec_args = std::make_shared<MCU::Tm_VideoCodec::Tm_Args>();
    dec_args->m_Streams.push_back(dec_stream);
    dec_args->m_Implementation = MCU::CODEC_IMPL_FFMPEG;
    auto rc = MCU::Tm_Container::CreateTermination("dec", dec_args);
    if (!rc)
    {
        auto errorStr = QString("Failed to create decoder: %1 (%2)").arg((int)rc.m_Cause).arg(QString::fromStdString(rc.m_CauseDescription));
        qDebug() << errorStr;
    }


    auto video_args = std::make_shared<VideoTermiantion::Args>();
    rc = MCU::Tm_Container::CreateTermination("video", video_args);
    if (!rc)
    {
        auto errorStr = QString("Failed to video ");
        qDebug() << errorStr;
    }

    connect(&timer, &QTimer::timeout, this, &Singleton::onTimerTimeout);
    timer.setInterval(1000);
    timer.setSingleShot(true);

    connect(pVideoWidget, &VideoWidget::dataStreamingFinished,
            this, &Singleton::onStreamingFinished);
}
