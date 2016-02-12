#include "Handler_Module.h"

/************************************************
    FromClientToAgent_StartGame_REQ
************************************************/
void FromClientToAgent_StartGame_REQ ( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize ) {

    UserSession * pSession = ( UserSession * ) pServerSession;
    {
        UserPacket pack = pSession->GetUserPacket();
        pack.GetProtocol() = MAKEDWORD( Games_Protocol, StartGame_REQ );
        pack.GetReady() = 1;
        pack.ToPrint();
        g_AgentServer->SendToGameServer( (BYTE*)&pack, pack.GetPacketSize() );
    }
}

/************************************************
    FromGameToAgent_StartGame_BRD
************************************************/
void FromGameToAgent_StartGame_BRD ( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
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

/*****************************************************
    Init_Poker_SetUsercards
*****************************************************/
int Init_Poker_SetUsercards( BYTE * _poker, BYTE _size )
{
    BYTE newPoker[POKER_SIZE + 1];
    g_GameMgr.UpdateShuffle( newPoker, _size );

    int i(0), sIndex(0);
    BYTE index = 0;
    int play_size = (_size - 3) / 3;
    sIndex = i + play_size;
    for (; i<(sIndex); i++) {
        index = newPoker[i];
        if ( index<MAX_POKER ) {
            _poker[index] = PK_USER_0;
        }
    }
    sIndex = i + play_size;
    for (; i<(sIndex); i++) {
        index = newPoker[i];
        if ( index<MAX_POKER ) {
            _poker[index] = PK_USER_1;
        }
    }
    sIndex = i + play_size;
    for (; i<(sIndex); i++) {
        index = newPoker[i];
        if ( index<MAX_POKER ) {
            _poker[index] = PK_USER_2;
        }
    }
    for (; i < _size; i++) {
        index = newPoker[i];
        if ( index<MAX_POKER ) {
            _poker[index] = PK_BANKER;
        }
    }
}


/*****************************************************
    InitCards_Get_Usercards
*****************************************************/
BYTE InitCards_Get_Usercards( TablePacket & pack, BYTE byVal, BYTE seatId ) {
    char * poker = pack.GetDisplayPokers(seatId);
    BYTE * pMove = pack.GetPokers();
    char szPoker[8] = {0};
    char szPokerList[128] = {0};
    BYTE byPoker(0), byCount(0);
    for (int  i=0; i<POKER_SIZE; i++) {
        byPoker = pMove[i];
        if ( byPoker == byVal ) {
            memset( szPoker, 0x0, sizeof(szPoker) );
            if ( byCount!=0 ) {
                strcat( szPokerList, ",");
            }
            sprintf( szPoker, "%d", i );
            strcat( szPokerList, szPoker);
            byCount++;
        }
    }
    *poker = '\0';
    strcat( poker, szPokerList);
    pack.GetDisplayPokerSize(seatId) = byCount;
}

/*****************************************************
    FromAgentToGame_StartGame_REQ
*****************************************************/
void FromAgentToGame_StartGame_REQ ( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
    if ( wSize>=sizeof(UserPacket) )
    {
        UserPacket user;
        user.SetPacket( (BYTE*)pMsg, wSize );
        user.ToPrint();

        GameTable * table = g_GameMgr.GetTable( user.GetTableId() );
        if (!table) {
            return;
        }

        {
            TablePacket & pack = table->GetTablePacket();
            pack.GetProtocol() = MAKEDWORD( Games_Protocol, StartGame_BRD );

            BYTE _seatid = user.GetSeatId();
            if (_seatid<3) {
                user.GetReady() = PK_READY;            // 用户参数包,准备标识
                pack.GetReady( _seatid ) = PK_READY;   // 桌子参数包,准备标识
            }

            if ( pack.GetReady(0)==PK_READY &&
                 pack.GetReady(1)==PK_READY &&
                 pack.GetReady(2)==PK_READY ) {

                {
                    pack.GetProtocol() = MAKEDWORD( Games_Protocol, InitCards_BRD );
                    pack.GetPokerSize(0) = USER_PLAYER;
                    pack.GetPokerSize(1) = USER_PLAYER;
                    pack.GetPokerSize(2) = USER_PLAYER;
                    BYTE * pokers = pack.GetPokers();
                    Init_Poker_SetUsercards( pokers, POKER_SIZE );
                    pack.GetInitcards()  = PK_INITCARDS;
                    InitCards_Get_Usercards(pack,PK_USER_0,0);
                    InitCards_Get_Usercards(pack,PK_USER_1,1);
                    InitCards_Get_Usercards(pack,PK_USER_2,2);
                    g_pCnpokerServer->SendToAgentServer( (BYTE*)&pack, pack.GetPacketSize() );
                }

                {
                    pack.GetProtocol() = MAKEDWORD( Games_Protocol, CalledLicense_BRD );
                    pack.GetPlaySeatId() = pack.GetBankerId();
                    pack.GetBankerId() = 0;
                    pack.GetLimitedTimes() = 16;
                    g_pCnpokerServer->SendToAgentServer( (BYTE*)&pack, pack.GetPacketSize() );
                }
                return;
            }

            pack.ToPrint();
            g_pCnpokerServer->SendToAgentServer( (BYTE*)&pack, pack.GetPacketSize() );
        }
    }
}