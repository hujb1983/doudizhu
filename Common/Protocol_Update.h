#ifndef _PROTOCOLCA_UPDATE_H_INCLUDED_
#define _PROTOCOLCA_UPDATE_H_INCLUDED_

#include "Protocol.h"

enum eUPDATE_PROTOCOL
{
  	RoomInfo_SYN			= 600,      // ������Ϣ
	RoomInfo_DBR,
	RoomInfo_ANC,

	TableInfo_SYN           = 610,      // ������Ϣ
	TableInfo_DBR,
	TableInfo_ANC,

	OnlineInfo_SYN          = 620,      // ������Ϣ
	OnlineInfo_DBR,
	OnlineInfo_ANC,

	WRankInfo_SYN           = 630,      // �����а���Ϣ
	WRankInfo_DBR,
	WRankInfo_ANC,

	DRankInfo_SYN           = 640,      // �����а���Ϣ
	DRankInfo_DBR,
	DRankInfo_ANC,

/*********************************************************
    step 2: �ڶ��汾
*********************************************************/
	UpdateLobby_SYN         = 800, //���³�����Ϣ
	UpdateLobby_ANC         = 800, //���´�����Ϣ
	Fields_DBR              = 810, //���³�����Ϣ
	Rooms_DBR               = 811, //���·�����Ϣ
	DayRanking_DBR          = 812, //���������а�
	WeekRanking_DBR         = 813, //���������а�
};

#endif // _PROTOCOLCA_H_INCLUDED_
