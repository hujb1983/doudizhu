#include "Handler_Module.h"
#include "AgentServer.h"
#include "GameServer.h"

/*****************************************************
    MSG_Handler_CreateBank_BRD
*****************************************************/
void FromGameToAgent_CreateBank_BRD ( TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
    if ( wSize>=sizeof(TablePacket) )
    {
        TablePacket table;
        table.SetPacket( (BYTE*)pMsg, wSize );
        table.GetProtocol() = MAKEDWORD( Games_Protocol, CreateBank_BRD );
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

/*****************************************************
    MSG_Handler_CreateBank_REQ
*****************************************************/
void FromAgentToGame_CreateBank_REQ ( TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
    DEBUG_MSG( LVL_DEBUG, "CreateBank_REQ to recv: %s \n", (char*)pMsg );

    JsonMap js_map;
    if ( js_map.set_json( (char *) pMsg ) == -1 ) {
        return;
    }

    int _nBattleid(0);
    js_map.ReadInteger("battleid",  _nBattleid);
    GameBattle *pBattle = g_GameMgr.GetBattle( _nBattleid );
    if ( pBattle==NULL ) {
        return;
    }

    int  _dmodel    = pBattle->getModel();
    int  _multiple  = pBattle->getMultiple();
    BYTE _bySeatid  = pBattle->getBanker();
    int  _bankerkey = pBattle->getKey( _bySeatid );

    char szMsg[1024] = {0};
    char bankerpoker[128]  = {0};
    char poker[60]  = {0};
    char szPlayerkey[256] = {0};
    pBattle->GetAllPlayerKey( szPlayerkey, sizeof(szPlayerkey) );

    char format[256] = 	"{\"protocol\":\"%d\","
                        "%s,"
                        "\"multiple\":\"%d\","
                        "\"dmodel\":\"%d\","
                        "\"battleid\":\"%d\","
                        "\"banker\":%d,"
                        "\"bankerkey\":%d,"
                        "\"bankercount\":%d,"
                        "\"bankerpoker\":\"%s\","
                        "\"count\":3,"
                        "\"poker\":\"%s\"}";

    pBattle->getBasecards( _bySeatid, poker, sizeof(poker)  );
    int retCount = pBattle->getUsercards( _bySeatid, bankerpoker, sizeof(bankerpoker) );
    sprintf( szMsg, format,  MAKEDWORD( Games_Protocol, CreateBank_BRD ), szPlayerkey,
            _multiple, _dmodel, _nBattleid, _bySeatid,
            _bankerkey, retCount, bankerpoker, poker );
    // }}}@ ������е���

    // @{{{ ���͵�������ң�
    WORD nLen = strlen( szMsg );
    g_pCnpokerServer->SendToAgentServer( (BYTE*)szMsg, nLen );

    // �������
    pBattle->SetPlaying( _bySeatid );
    pBattle->SetBattleStatus( eGB_PLAYING );
    pBattle->getDiscardTimes() = 0;

    DEBUG_MSG( LVL_DEBUG, "CreateBank_REQ to agent: %s \n", (char*)szMsg );
}
