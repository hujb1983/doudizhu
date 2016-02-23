#ifndef _LobbyUpdate1_H_
#define _LobbyUpdate1_H_
#include "PacketRank.h"
#include "PacketFields.h"
#include "PacketRooms.h"

class LobbyUpdate : public UtilityTimer
{
public:
	LobbyUpdate();
	~LobbyUpdate();

public:
    BOOL UpdateDate( UINT uiTicket );
    void SendToDB();

    RankPacket & GetDay();
    RankPacket & GetWeek();

    FieldsPacket & GetFields();
    RoomsPacket & GetRooms( BYTE byIndex );

private:
    BYTE m_byFirst;

    RankPacket m_pDayRanks;
    RankPacket m_pWeekRanks;

    FieldsPacket m_pFields;
    RoomsPacket m_pRooms[5];
};


#endif

