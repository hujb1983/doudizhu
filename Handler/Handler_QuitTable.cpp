#include "Handler_Module.h"

/************************************************
    FromClientToAgent_QuitTable_REQ
************************************************/
void FromClientToAgent_QuitTable_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    DEBUG_MSG( LVL_DEBUG, "QuitTable_REQ to recv: %s \n", (char*) pMsg );

    UserSession * pSession = ( UserSession * ) pServerSession;
    {
        UserPacket & user = pSession->GetUserPacket();
        user.GetProtocol() = MAKEDWORD( Games_Protocol, QuitTable_REQ );
        user.ToPrint();
        g_AgentServer->SendToGameServer( (BYTE*)&user, user.GetPacketSize() );
    }
}

/************************************************
    FromGameToAgent_QuitTable_BRD
************************************************/
void FromGameToAgent_QuitTable_BRD(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    if ( wSize>=sizeof(TablePacket) )
    {
        TablePacket table;
        table.SetPacket( (BYTE*)pMsg, wSize );
        table.GetProtocol() = MAKEDWORD( Games_Protocol, QuitTable_BRD );
        table.ToPrint();

        UINT userkey1 = table.GetUserKey(0);
        UINT userkey2 = table.GetUserKey(1);
        UINT userkey3 = table.GetUserKey(2);

        char szBuff[4069] = {0};
        WORD uiLength = 0;
        BYTE * pokers = table.GetPokers();
        if ( userkey1!=0 ){
            memset( szBuff, 0x0, sizeof(szBuff) );
            uiLength = table.JsonData(0, szBuff, sizeof(szBuff) );
            g_AgentServer->SendToClient( userkey1, (BYTE*)szBuff, uiLength );
            DEBUG_MSG( LVL_DEBUG, "%s", szBuff);
        }
        if ( userkey2!=0 ){
            memset( szBuff, 0x0, sizeof(szBuff) );
            uiLength = table.JsonData(1, szBuff, sizeof(szBuff) );
            g_AgentServer->SendToClient( userkey2, (BYTE*)szBuff, uiLength );
            DEBUG_MSG( LVL_DEBUG, "%s", szBuff);
        }
        if ( userkey3!=0 ){
            memset( szBuff, 0x0, sizeof(szBuff) );
            uiLength = table.JsonData(2, szBuff, sizeof(szBuff) );
            g_AgentServer->SendToClient( userkey3, (BYTE*)szBuff, uiLength );
            DEBUG_MSG( LVL_DEBUG, "%s", szBuff);
        }
    }
}

/************************************************
    FromAgentToGame_QuitTable_REQ
************************************************/
void FromAgentToGame_QuitTable_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
   if ( wSize < sizeof(UserPacket) ) {
        return ;
    }

    BYTE _called(0);
    UserPacket user;
    user.SetPacket( (BYTE*)pMsg, wSize );

    GameTable * table = g_GameMgr.GetTable( user.GetTableId() );
    if (!table) {
        return;
    }

    TablePacket & pack = table->GetTablePacket();

    BYTE _seatid = user.GetSeatId();
    if (_seatid>2) {
        return;
    }

    if ( pack.GetTimeStep()==PK_DEALING ||
         pack.GetTimeStep()==PK_CALLING ||
         pack.GetTimeStep()==PK_PLAYING ) {
         pack.GetOnline(_seatid)=false;
    }
    else {
        pack.GetPosition(_seatid) = 0;
    }

    pack.GetProtocol() = MAKEDWORD( Games_Protocol, QuitTable_BRD );
    g_pCnpokerServer->SendToAgentServer( (BYTE*)&pack, pack.GetPacketSize() );
    return;
}

