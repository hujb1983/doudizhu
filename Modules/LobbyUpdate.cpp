#include "LobbyUpdate.h"
#include "LobbyServer.h"

LobbyUpdate::LobbyUpdate()
: UtilityTimer(6000)
{
    m_byFirst = TRUE;
}

LobbyUpdate::~LobbyUpdate()
{

}

BOOL LobbyUpdate::UpdateDate( UINT uiTicket )
{
    BYTE byRet = this->UpdateTimer( uiTicket );
    if ( byRet==TRUE ) {
        DEBUG_MSG( LVL_DEBUG, "UtilityTimer::Update(%d)", uiTicket );
        this->StartTimer();
        SendToDB();
        Sleep(3000);
    }
}

void LobbyUpdate::SendToDB()
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

FieldsPacket & LobbyUpdate::GetFields()
{   return m_pFields;   }

RoomsPacket & LobbyUpdate::GetRooms( BYTE byIndex )
{   return m_pRooms[byIndex]; }
