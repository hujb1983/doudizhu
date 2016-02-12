#include "Handler_Module.h"

/*****************************************************
    FromGame_CalledLicense_BRD
*****************************************************/
void FromGameToAgent_CalledLicense_BRD ( TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
    if ( wSize>=sizeof(TablePacket) )
    {
        TablePacket table;
        table.SetPacket( (BYTE*)pMsg, wSize );
        table.GetProtocol() = MAKEDWORD( Games_Protocol, CalledLicense_BRD );
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
            g_AgentServer->SendToBuffer( userkey1, (BYTE*)szBuff, uiLength );
            DEBUG_MSG( LVL_DEBUG, "%s", szBuff);
        }
        if ( userkey2!=0 ){
            memset( szBuff, 0x0, sizeof(szBuff) );
            uiLength = table.JsonData(1, szBuff, sizeof(szBuff) );
            g_AgentServer->SendToBuffer( userkey2, (BYTE*)szBuff, uiLength );
            DEBUG_MSG( LVL_DEBUG, "%s", szBuff);
        }
        if ( userkey3!=0 ){
            memset( szBuff, 0x0, sizeof(szBuff) );
            uiLength = table.JsonData(2, szBuff, sizeof(szBuff) );
            g_AgentServer->SendToBuffer( userkey3, (BYTE*)szBuff, uiLength );
            DEBUG_MSG( LVL_DEBUG, "%s", szBuff);
        }
    }
}

/*****************************************************
    FromAgent_CalledLicense_REQ
*****************************************************/
void FromAgentToGame_CalledLicense_REQ (TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
    DEBUG_MSG( LVL_DEBUG, "[ MSG_Handler_License_REQ %s ] \n",  (char*)pMsg );

    JsonMap js_map;
    if ( js_map.set_json( (char *) pMsg ) == -1 ) {
        return;
    }

    int _seatid(0), _battleid(0);
    js_map.ReadInteger( "battleid", _battleid );

    GameBattle * pBattle = NULL;
    pBattle = g_GameMgr.GetBattle( _battleid );
    if ( pBattle==NULL ) {
        return;
    }

    // ���û�������;
    int _basics    = pBattle->getMinMoney();
    int _multiple  = pBattle->getMultiple();
    int _brokerage = pBattle->getBrokerage();
    _seatid = pBattle->getCalled();

    {
        char szPlayerkey[256] = {0};
        pBattle->GetAllPlayerKey( szPlayerkey, sizeof(szPlayerkey) );

        char buff[256]   = {0};
        char format[128] = 	"{\"protocol\":\"%d\","
                            "%s,"
                            "\"battleid\":\"%d\","
                            "\"basics\":\"%d\","
                            "\"multiple\":\"%d\","
                            "\"brokerage\":\"%d\","
                            "\"seatid\":\"%d\","
                            "\"times\":\"%d\" }";   // ��ʱ�趨Ϊ18��;

        snprintf( buff, sizeof(buff), format,
                MAKEDWORD( Games_Protocol, CalledLicense_BRD ),
                szPlayerkey,
                _battleid,
                _basics,
                _multiple,
                _brokerage,
                _seatid,
                16 );

        WORD nLen = strlen( buff );
        g_pCnpokerServer->SendToAgentServer( (BYTE*)buff, nLen );


        /* step5. �͵���ʱ�ж϶���...  */
        // pBattle->SetCalledOvertime();
    }
}

