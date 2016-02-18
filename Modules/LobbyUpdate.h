#ifndef _LobbyUpdate_H_
#define _LobbyUpdate_H_
#include "PacketRank.h"
#include "PacketHandler.h"

class LobbyUpdate : public UtilityTimer
{
public:
	LobbyUpdate();
	~LobbyUpdate();

public:
    BOOL Update( UINT uiTicket );

    void SendInit();

    RankPacket & GetDay();
    RankPacket & GetWeek();

    CHAR * GetJsonDay();
    CHAR * GetJsonWeek();

private:
    BYTE m_byFirst;
    RankPacket m_pDayRanks;
    RankPacket m_pWeekRanks;

};

extern LobbyUpdate * g_pLobbyUpdate;

#endif

