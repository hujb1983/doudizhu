#ifndef _ProtocolUpdate_H_
#define _ProtocolUpdate_H_

enum eUPDATE_PROTOCOL
{
  	RoomsInfo_SYN			= 600,      // 房间信息
	RoomsInfo_DBR,
	RoomsInfo_ANC,

	TablesInfo_SYN           = 610,      // 桌子信息
	TablesInfo_DBR,
	TablesInfo_ANC,

	OnlineInfo_SYN          = 620,      // 在线信息
	OnlineInfo_DBR,
	OnlineInfo_ANC,

	WeekRanks_SYN           = 630,      // 周排行版信息
	WeekRanks_DBR,
	WeekRanks_ANC,

	DayRanks_SYN           = 640,      // 日排行版信息
	DayRanks_DBR,
	DayRanks_ANC,
};

#endif // _ProtocolUpdate_H_