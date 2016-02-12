#include "Handler_Module.h"

/*********************************************************
    FromClientToAgent_JoinTable_REQ
*********************************************************/
void FromClientToAgent_JoinTable_REQ ( TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
    JsonMap js_map;
    if ( js_map.set_json( (char *) pMsg ) == -1 ) {
        return;
    }

    UserSession * pSession = ( UserSession * ) pServerSession;
    int  _fieldid(0), _roomid(0);
    js_map.ReadInteger( "roomid",  _fieldid );
    js_map.ReadInteger( "tableid", _roomid  );

    {
        UserPacket pack = pSession->GetUserPacket();
        pack.GetProtocol() = MAKEDWORD( Games_Protocol, JoinTable_REQ );
        pack.GetFieldId() = _fieldid;
        pack.GetRoomId() = _roomid;
        pack.ToPrint();
        g_AgentServer->SendToLobbyServer( (BYTE*)&pack, pack.GetPacketSize() );
    }
}

/*********************************************************
    FromLobbyToAgent_JoinTable_ANC
*********************************************************/
void FromLobbyToAgent_JoinTable_ANC ( TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
    if ( wSize>=sizeof(UserPacket) )
    {
        UserPacket pack;
        pack.SetPacket( (BYTE*) pMsg, wSize );
        pack.GetProtocol() = MAKEDWORD( Games_Protocol, JoinTable_ANC );

        UserSession * pSession = NULL;
        pSession = g_AgentServer->GetUserSession( pack.GetUserKey() );
        if ( pSession ) {
            pSession->SetUserPacket( (BYTE*)&pack, pack.GetPacketSize() );
            pack.ToPrint();
        }

        g_AgentServer->SendToGameServer( (BYTE*)&pack, wSize );
    }
}

/*********************************************************
    FromGameToAgent_JoinTable_BRD
*********************************************************/
void FromGameToAgent_JoinTable_BRD  ( TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
    if ( wSize>=sizeof(TablePacket) )
    {
        TablePacket table;
        table.SetPacket( (BYTE*)pMsg, wSize );
        table.GetProtocol() = MAKEDWORD( Games_Protocol, JoinTable_BRD );
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