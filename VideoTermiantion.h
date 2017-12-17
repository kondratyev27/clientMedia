#ifndef VIDEOTERMIANTION_H
#define VIDEOTERMIANTION_H


#include <MCU/Core/Termination.hpp>
#include <MCU/Core/Packets/RAW.hpp>
#include <QDebug>
#include <VideoWidget.h>

QDebug &operator<<(QDebug &stream, const MCU::Tm_Size &size);

class VideoTermiantion : public MCU::Tm_Termination
{
public:

    struct Args: MCU::Tm_ConcreteTerminationArgs< VideoTermiantion > {
        Args();
        std::string ToString() const;
    };


    VideoTermiantion(const std::string &id);

    MCU::Tm_TerminationActionResult HandleCreate( MCU::Tm_TerminationArgsPtr args ) override;
    void HandleTopologyChange( int channelIndex, bool isConnected ) override;
    int ProcessImpl() override;

private:
    VideoWidget widget;
};

#endif // VIDEOTERMIANTION_H
