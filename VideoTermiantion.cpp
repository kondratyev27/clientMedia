#include "VideoTermiantion.h"

#include <MCU/Core/Packets/RAW.hpp>

#include <QDebug>

static long int crv_tab[256];
static long int cbu_tab[256];
static long int cgu_tab[256];
static long int cgv_tab[256];
static long int tab_76309[256];
static unsigned char clp[1024];   //for clip in CCIR601

void init_yuv420p_table()
{
	long int crv,cbu,cgu,cgv;
	int i,ind;

	crv = 104597; cbu = 132201;  /* fra matrise i global.h */
	cgu = 25675;  cgv = 53279;

	for (i = 0; i < 256; i++)
	{
		crv_tab[i] = (i-128) * crv;
		cbu_tab[i] = (i-128) * cbu;
		cgu_tab[i] = (i-128) * cgu;
		cgv_tab[i] = (i-128) * cgv;
		tab_76309[i] = 76309*(i-16);
	}

	for (i = 0; i < 384; i++)
		clp[i] = 0;
	ind = 384;
	for (i = 0;i < 256; i++)
		clp[ind++] = i;
	ind = 640;
	for (i = 0;i < 384; i++)
		clp[ind++] = 255;
}


void yuv420p_to_rgb24(unsigned char* yuvbuffer,unsigned char* rgbbuffer, int width,int height)
{
	int y1, y2, u, v;
	unsigned char *py1, *py2;
	int i, j, c1, c2, c3, c4;
	unsigned char *d1, *d2;
	unsigned char *src_u, *src_v;
	static int init_yuv420p = 0;

	src_u = yuvbuffer + width * height;   // u
	src_v = src_u + width * height / 4;  // v

	py1 = yuvbuffer;   // y
	py2 = py1 + width;
	d1 = rgbbuffer;
	d2 = d1 + 3 * width;

	if (init_yuv420p == 0)
	{
		init_yuv420p_table();
		init_yuv420p = 1;
	}

	for (j = 0; j < height; j += 2)
	{
		for (i = 0; i < width; i += 2)
		{
			u = *src_u++;
			v = *src_v++;

			c1 = crv_tab[v];
			c2 = cgu_tab[u];
			c3 = cgv_tab[v];
			c4 = cbu_tab[u];

			//up-left
			y1 = tab_76309[*py1++];
			*d1++ = clp[384+((y1 + c1)>>16)];
			*d1++ = clp[384+((y1 - c2 - c3)>>16)];
			*d1++ = clp[384+((y1 + c4)>>16)];

			//down-left
			y2 = tab_76309[*py2++];
			*d2++ = clp[384+((y2 + c1)>>16)];
			*d2++ = clp[384+((y2 - c2 - c3)>>16)];
			*d2++ = clp[384+((y2 + c4)>>16)];

			//up-right
			y1 = tab_76309[*py1++];
			*d1++ = clp[384+((y1 + c1)>>16)];
			*d1++ = clp[384+((y1 - c2 - c3)>>16)];
			*d1++ = clp[384+((y1 + c4)>>16)];

			//down-right
			y2 = tab_76309[*py2++];
			*d2++ = clp[384+((y2 + c1)>>16)];
			*d2++ = clp[384+((y2 - c2 - c3)>>16)];
			*d2++ = clp[384+((y2 + c4)>>16)];
		}
		d1  += 3*width;
		d2  += 3*width;
		py1 += width;
		py2 += width;
	}
}

VideoTermiantion::VideoTermiantion(const std::string &id) :
    MCU::Tm_Termination( id )
{

}

MCU::Tm_TerminationActionResult VideoTermiantion::HandleCreate(MCU::Tm_TerminationArgsPtr args)
{
	m_Channels.push_back( std::make_shared<MCU::Tm_Channel> (MCU::Tm_Channel::Input));
    return {MCU::CAUSE_SUCCESS};
}

void VideoTermiantion::HandleTopologyChange(int channelIndex, bool isConnected)
{
    if (isConnected)
    {
        widget.show();
    }
    else
    {
        widget.hide();
    }
}

int VideoTermiantion::ProcessImpl()
{
    if (!m_Channels[0]->m_InUse)
    {
        return 20;
    }

    if (m_Channels[0]->m_Queue.Empty())
    {
        return 20;
    }

    auto pPacket = m_Channels[0]->m_Queue.Dequeue();


    auto pRawPacket = std::static_pointer_cast<MCU::Tm_RAW_Packet>(pPacket);



	auto rgb = Make_RGBA_Packet(pRawPacket->m_Resolution);
qDebug()<<"emit";
	yuv420p_to_rgb24(pRawPacket->m_Data,rgb->m_Data, pRawPacket->m_Resolution.m_Width, pRawPacket->m_Resolution.m_Height);
	QImage image(rgb->m_Data, pRawPacket->m_Resolution.m_Width, pRawPacket->m_Resolution.m_Height, QImage::Format_RGB32);
    widget.emitPushImage(image);
    return 20;
}

VideoTermiantion::Args::Args()
{

}

std::string VideoTermiantion::Args::ToString() const
{
    return std::string();
}
