#include "Widget.h"
#include <QApplication>
#include <QDebug>

#include <MCU/Terminations/RTSP/Client.hpp>
//#include <MCU/Terminations/RTSP/Client.hpp>
#include <MCU/Core/Container.hpp>
#include <MCU/Terminations/Conference/VideoConference.hpp>
#include <MCU/Terminations/File/Reader.hpp>
#include <MCU/Terminations/File/Writer.hpp>
#include <MCU/Terminations/Codecs/VideoCodec.hpp>
#include <MCU/Core/ProxyTermination.hpp>
#include <VideoTermiantion.h>
#include <ATE/Debug/Trace.h>
#include <Singleton.h>

using namespace MCU;
int main(int argc, char *argv[])
{
	Tm_Trace trace("trace.conf");

    QApplication a(argc, argv);
    Singleton::instance();
    Widget w;
    w.move(200, 400);
    w.show();


//    if (!MCU::Tm_Container::CreateContext("default"))
//    {
//        auto errorStr = "Failed to create context";
//        qDebug() << errorStr;
//        return false;
//    }

//    MCU::Tm_VideoCodec::Tm_StreamArgs dec_stream;
//    dec_stream.m_Codec = MCU::CODEC_RAW_YUV420;
////	dec_stream.m_BitRate = args.bitRate;
////	dec_stream.m_Scale = MCU::Tm_Scale(args.outResolution.width(), args.outResolution.height());
//    auto dec_args = std::make_shared<MCU::Tm_VideoCodec::Tm_Args>();
//    dec_args->m_Streams.push_back(dec_stream);
//    dec_args->m_Implementation = MCU::CODEC_IMPL_FFMPEG;
//    auto rc = MCU::Tm_Container::CreateTermination("dec", dec_args);
//    if (!rc)
//    {
//        auto errorStr = QString("Failed to create decoder: %1 (%2)").arg((int)rc.m_Cause).arg(QString::fromStdString(rc.m_CauseDescription));
//        qDebug() << errorStr;
//        return false;
//    }


//    auto rtsp_args = std::make_shared<MCU::Tm_RTSP_Client::Tm_Args>();
//    rtsp_args->m_URL = "rtsp://192.168.102.50:5554/countdown.h264";
//     rc = MCU::Tm_Container::CreateTermination("rtsp", rtsp_args);
//    if (!rc)
//    {
//        auto errorStr = QString("Failed to create server: %1 (%2)").arg((int)rc.m_Cause).arg(QString::fromStdString(rc.m_CauseDescription));
//        qDebug() << errorStr;
//        return false;
//    }

//    auto video_args = std::make_shared<VideoTermiantion::Args>();
//    rc = MCU::Tm_Container::CreateTermination("video", video_args);
//    if (!rc)
//    {
//        auto errorStr = QString("Failed to video ");
//        qDebug() << errorStr;
//        return false;
//    }


//    MCU::Tm_Topology topology;
//    topology.Add("rtsp", 0, "dec", 0);
//    topology.Add("dec", 1, "video", 0);


//    if (!MCU::Tm_Container::ModifyTopology("default", topology, true))
//    {
//        QString errorStr("Ошибка создания топологии");
//        qDebug()<<errorStr;
//    }


    return a.exec();
}
