#include "LobbyUpdate.h"
#include "LobbyServer.h"

LobbyUpdate::LobbyUpdate()
{
    m_byFirst = TRUE;
}

LobbyUpdate::~LobbyUpdate()
{

}

BOOL LobbyUpdate::Update( UINT uiTicket )
{

}

void LobbyUpdate::SendInit()
{
    m_pDayRanks.GetProtocol() = MAKEDWORD( (WORD)FromLobbyToDB_PID, (WORD)DayRanks_SYN );
    g_pLobbyServer->SendToDB( (BYTE*)&m_pDayRanks, sizeof(RankPacket) );

    m_pWeekRanks.GetProtocol() = MAKEDWORD( (WORD)FromLobbyToDB_PID, (WORD)WeekRanks_SYN );
    g_pLobbyServer->SendToDB( (BYTE*)&m_pWeekRanks, sizeof(RankPacket) );
}

RankPacket & LobbyUpdate::GetDay()
{   return m_pDayRanks; }

RankPacket & LobbyUpdate::GetWeek()
{   return m_pWeekRanks; }

CHAR * LobbyUpdate::GetJsonDay()
{   return m_pDayRanks.GetJsonData();  }

CHAR * LobbyUpdate::GetJsonWeek()
{   return m_pWeekRanks.GetJsonData();  }

