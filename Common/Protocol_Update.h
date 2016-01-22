#ifndef _PROTOCOLCA_UPDATE_H_INCLUDED_
#define _PROTOCOLCA_UPDATE_H_INCLUDED_

#include "Protocol.h"

enum eUPDATE_PROTOCOL
{
  	RoomInfo_SYN			= 600,      // 房间信息
	RoomInfo_DBR,
	RoomInfo_ANC,

	TableInfo_SYN           = 610,      // 桌子信息
	TableInfo_DBR,
	TableInfo_ANC,

	OnlineInfo_SYN          = 620,      // 在线信息
	OnlineInfo_DBR,
	OnlineInfo_ANC,

	WRankInfo_SYN           = 630,      // 周排行版信息
	WRankInfo_DBR,
	WRankInfo_ANC,

	DRankInfo_SYN           = 640,      // 日排行版信息
	DRankInfo_DBR,
	DRankInfo_ANC,

/*********************************************************
    step 2: 第二版本
*********************************************************/
	UpdateLobby_SYN         = 800, //更新场次信息
	UpdateLobby_ANC         = 800, //更新大厅信息
	Fields_DBR              = 810, //更新场次信息
	Rooms_DBR               = 811, //更新房间信息
	DayRanking_DBR          = 812, //更新日排行版
	WeekRanking_DBR         = 813, //更新周排行版
};

#endif // _PROTOCOLCA_H_INCLUDED_
