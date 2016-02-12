#include "Handler_Module.h"
#include "AgentServer.h"
#include "GameServer.h"

/*****************************************************
    FromClient_CalledBank_REQ
*****************************************************/
void FromClientToAgent_CalledBank_REQ ( TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
    JsonMap js_map;
    if ( js_map.set_json( (char *) pMsg ) == -1 ) {
        return;
    }

    int  _calltype(0);
    js_map.ReadInteger( "points",  _calltype );

    UserSession * pSession = ( UserSession * ) pServerSession;
    {
        UserPacket & user = pSession->GetUserPacket();
        user.GetProtocol() = MAKEDWORD( Games_Protocol, Called_REQ );
        user.GetCalled() = _calltype;
        user.ToPrint();
        g_AgentServer->SendToGameServer( (BYTE*)&user, user.GetPacketSize() );
    }
}

/*****************************************************
    FromGame_CalledBank_BRD
*****************************************************/
void FromGameToAgent_CalledBank_BRD ( TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
    if ( wSize>=sizeof(TablePacket) )
    {
        TablePacket table;
        table.SetPacket( (BYTE*)pMsg, wSize );
        table.GetProtocol() = MAKEDWORD( Games_Protocol, Called_BRD );
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
        }
        if ( userkey2!=0 ){
            memset( szBuff, 0x0, sizeof(szBuff) );
            uiLength = table.JsonData(1, szBuff, sizeof(szBuff) );
            g_AgentServer->SendToClient( userkey2, (BYTE*)szBuff, uiLength );
        }
        if ( userkey3!=0 ){
            memset( szBuff, 0x0, sizeof(szBuff) );
            uiLength = table.JsonData(2, szBuff, sizeof(szBuff) );
            g_AgentServer->SendToClient( userkey3, (BYTE*)szBuff, uiLength );
        }
    }
}


/*****************************************************
    Re_Init_Poker_SetUsercards
*****************************************************/
int Re_Init_Poker_SetUsercards( BYTE * _poker, BYTE _size )
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
    InitCards_Get_Basecards
*****************************************************/
void Banker_Alloc_BasicCards( TablePacket & pack, BYTE byUserType ) {

    BYTE * pMove = pack.GetPokers();
    BYTE bankerId = pack.GetBankerId();
    char * b_poker = pack.GetBasicPokers();
    char * poker = pack.GetDisplayPokers(bankerId);
    pack.GetBasicPokerSize() = 3;

    char szPoker[8] = {0};
    char szPokerList[128] = {0};
    BYTE byPoker(0), byCount(0);
    for (int  i=0; i<POKER_SIZE; i++) {
        byPoker = pMove[i];
        if ( byPoker == PK_BANKER ) {
            pMove[i] = byUserType;
            memset( szPoker, 0x0, sizeof(szPoker) );
            if ( byCount!=0 ) {
                strcat( szPokerList, ",");
            }
            sprintf( szPoker, "%d", i );
            strcat( szPokerList, szPoker);
            byCount++;
        }
    }

    pack.GetDisplayPokerSize(bankerId) = 20;
    *b_poker = '\0';
    strcat( b_poker, szPokerList);
    strcat( poker, ",");
    strcat( poker, szPokerList);
}


/*****************************************************
    FromAgentToGame_CalledBank_REQ
*****************************************************/
void FromAgentToGame_CalledBank_REQ ( TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
    if ( wSize < sizeof(UserPacket) ) {
        return ;
    }

    BYTE _called(0);
    UserPacket user;
    user.SetPacket( (BYTE*)pMsg, wSize );
    user.ToPrint();

    GameTable * table = g_GameMgr.GetTable( user.GetTableId() );
    if (!table) {
        return;
    }

    TablePacket & pack = table->GetTablePacket();

    BYTE _seatid = user.GetSeatId();
    if (_seatid>2) {
        return;
    }

    if ( pack.GetPlaySeatId()!=_seatid ) {
        return;
    }

    BYTE byUserSign = PK_USER_0 + _seatid;

    BYTE _count(0);
    if ( pack.GetCalledStatus(0) == PK_CALLED ) { ++_count;}
    if ( pack.GetCalledStatus(1) == PK_CALLED ) { ++_count;}
    if ( pack.GetCalledStatus(2) == PK_CALLED ) { ++_count;}

    _called = user.GetCalled();
    if ( pack.GetModel()==0 ) {     // 普通叫牌
        if ( _called==0 ) {
            pack.GetCalledType(_seatid) = eGB_Waiver;
            pack.GetCalledStatus(_seatid) = PK_CALLED;    // 已经叫牌了
        }
        else {

            do {
                     if ( _called==1 )   {   pack.GetCalledType(_seatid) = eGB_Point1; break;  }
                else if ( _called==2 )   {   pack.GetCalledType(_seatid) = eGB_Point2; break;  }
                else if ( _called==3 )   {   pack.GetCalledType(_seatid) = eGB_Point3; break;  }
                return;
            } while(1);
            if ( _count==0 ) {
                pack.GetMultiple() = _called;
            }
            else if ( _called > pack.GetMultiple() ) {
                pack.GetMultiple() = _called;
            }
            else {
                return; // 后面的人要叫得比前面的高;
            }
            pack.GetCalledStatus(_seatid) = PK_CALLED;    // 已经叫牌了
            pack.GetBankerId() = _seatid;
            if ( pack.GetCalledType(_seatid) == eGB_Point3 ) {
                Banker_Alloc_BasicCards(pack, byUserSign);
                pack.GetProtocol() = MAKEDWORD( Games_Protocol, CreateBank_BRD );
                g_pCnpokerServer->SendToAgentServer( (BYTE*)&pack, pack.GetPacketSize() );

                pack.GetFirst() = true;
                pack.GetPlaySeatId() = pack.GetBankerId();
                pack.GetProtocol() = MAKEDWORD( Games_Protocol, DiscardsLicense_BRD );
                g_pCnpokerServer->SendToAgentServer( (BYTE*)&pack, pack.GetPacketSize() );
                return;
            }
        }
    }
    else {  // 翻倍叫牌
        if ( _called==0 ) {
            pack.GetCalledType(_seatid) = eGB_Waiver;
            pack.GetCalledStatus(_seatid) = PK_CALLED;    // 已经叫牌了
        }
        else {
            pack.GetBankerId() = _seatid;
            pack.GetCalledType(_seatid) = eGB_Apply;
            pack.GetCalledStatus(_seatid) = PK_CALLED;    // 已经叫牌了
            pack.GetMultiple() *= 2;
        }
    }

    // 判断叫牌
    BYTE l_seatid = (_seatid+2)%3;
    BYTE r_seatid = (_seatid+1)%3;
    if (_count==0 || _count==1) {
        pack.GetProtocol() = MAKEDWORD( Games_Protocol, Called_BRD );
        g_pCnpokerServer->SendToAgentServer( (BYTE*)&pack, pack.GetPacketSize() );

        pack.GetPlaySeatId() = r_seatid;
        pack.GetProtocol() = MAKEDWORD( Games_Protocol, CalledLicense_BRD );
        g_pCnpokerServer->SendToAgentServer( (BYTE*)&pack, pack.GetPacketSize() );
    }
    else {

        BYTE _hasCalled(0); // 计算叫地主次数
        if ( pack.GetCalledType(0)!=eGB_Waiver )   {   ++_hasCalled;  }
        if ( pack.GetCalledType(1)!=eGB_Waiver )   {   ++_hasCalled;  }
        if ( pack.GetCalledType(3)!=eGB_Waiver )   {   ++_hasCalled;  }

        if (_hasCalled == 0) {
            pack.GetProtocol() = MAKEDWORD( Games_Protocol, InitCards_BRD );
            pack.GetCalledStatus(0) = 0;
            pack.GetCalledStatus(1) = 0;
            pack.GetCalledStatus(2) = 0;
            pack.GetCalledType(0) = eGB_0;
            pack.GetCalledType(1) = eGB_0;
            pack.GetCalledType(2) = eGB_0;
            pack.GetPokerSize(0) = USER_PLAYER;
            pack.GetPokerSize(1) = USER_PLAYER;
            pack.GetPokerSize(2) = USER_PLAYER;
            BYTE * pokers = pack.GetPokers();
            Re_Init_Poker_SetUsercards( pokers, POKER_SIZE );   // 重新发牌
            pack.GetInitcards()  = PK_INITCARDS;
            g_pCnpokerServer->SendToAgentServer( (BYTE*)&pack, pack.GetPacketSize() );
            return; // 重新洗牌消息
        }

        if (_count==2) {
            if ( pack.GetCalledType(r_seatid)==eGB_Waiver ) {
                Banker_Alloc_BasicCards(pack, byUserSign);
                pack.GetProtocol() = MAKEDWORD( Games_Protocol, CreateBank_BRD );
                g_pCnpokerServer->SendToAgentServer( (BYTE*)&pack, pack.GetPacketSize() );

                pack.GetFirst() = true;
                pack.GetPlaySeatId() = pack.GetBankerId();
                pack.GetProtocol() = MAKEDWORD( Games_Protocol, DiscardsLicense_BRD );
                g_pCnpokerServer->SendToAgentServer( (BYTE*)&pack, pack.GetPacketSize() );
                return;
            }
            else {
                // 第一个叫了，那还可以叫一次
                pack.GetProtocol() = MAKEDWORD( Games_Protocol, Called_BRD );
                g_pCnpokerServer->SendToAgentServer( (BYTE*)&pack, pack.GetPacketSize() );
            }
        }

        if (_count==3) {
            if ( pack.GetCalledType(_seatid)==eGB_Waiver ) {
                Banker_Alloc_BasicCards(pack, byUserSign);
                pack.GetProtocol() = MAKEDWORD( Games_Protocol, CreateBank_BRD );
                g_pCnpokerServer->SendToAgentServer( (BYTE*)&pack, pack.GetPacketSize() );

                pack.GetFirst() = true;
                pack.GetPlaySeatId() = pack.GetBankerId();
                pack.GetProtocol() = MAKEDWORD( Games_Protocol, DiscardsLicense_BRD );
                g_pCnpokerServer->SendToAgentServer( (BYTE*)&pack, pack.GetPacketSize() );
                return;
            }
        }
    }
}