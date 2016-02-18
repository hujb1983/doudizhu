#include "Handler_Module.h"
#include <UtilityParserJson.h>
#include <MydbcQueryResult.h>
#include "PacketUser.h"
#include "AgentServer.h"
#include "LobbyServer.h"

/*********************************************************
	FromClientToAgent_Login_REQ
*********************************************************/
void FromClientToAgent_Login_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    UtilityParserJson jsMap;
    if ( jsMap.SetJson( (char *) pMsg ) == -1 ) {
        return;
    }

    int  _userkey  = pServerSession->GetSessionIndex();
    int  _userid   = 0;
    char _szSSHKEY[128] = {0};

    jsMap.ReadInteger( "userid", _userid );
    jsMap.ReadString ( "sshkey", _szSSHKEY, sizeof(_szSSHKEY) );

    {
        UserPacket packet;
        packet.ToInit();
        packet.GetUserKey()  = _userkey;
        packet.GetUserId()   = _userid;
        memcpy ( packet.GetSSHKey(), _szSSHKEY, sizeof(_szSSHKEY) );

        packet.GetProtocol() = MAKEDWORD( FromAgentToLobby_PID, Login_REQ );
        g_pAgentServer->SendToLobby( (BYTE*)&packet, sizeof(packet) );
    }
}

/*********************************************************
    FromAgentToLobby_Login_REQ
*********************************************************/
void FromAgentToLobby_Login_REQ ( TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
    if ( wSize>=sizeof(UserPacket) )
    {
        UserPacket packet;
        packet.SetPacket( (BYTE*) pMsg, wSize );
        packet.GetAgentKey() = pServerSession->GetSessionIndex();
        packet.GetProtocol() = MAKEDWORD( FromLobbyToDB_PID, Login_REQ );
        g_pLobbyServer->SendToDB( (BYTE*)&packet, sizeof(packet) );
    }
}

/*********************************************************
    Query_Login
*********************************************************/
class Query_Login : public MydbcQueryResult
{
	_DECLARE_QUERY_POOL( Query_Login );

public:
    UserPacket m_cPacket;   // 数据包

	enum { RESULT_COL_NUM = 2, PARAM_COL_NUL  = 0,};

	struct sRESULT {
        BYTE m_byError;
        UINT m_uiLoginTime;
		sRESULT() { memset( this, 0, sizeof(sRESULT) ); }
	};

	ULONG uLength[RESULT_COL_NUM]; // 4
	vector<sRESULT> vctRes;

	void AllocData() {
		sRESULT m_RESULT;
		memset(&m_RESULT, 0, sizeof( m_RESULT) );
		vctRes.push_back( m_RESULT );
	}

	void InitData() { vctRes.clear();       }
	void dealData() { vctRes.pop_back();    }

	_BEGIN_BINDING_DATA( sRESULT, vctRes, uLength, 1, RESULT_COL_NUM)
        _BINDING_COLUMN(0, m_byError)
        _BINDING_COLUMN(1, m_uiLoginTime)
	_END_BINDING_DATA()
};
_IMPL_QUERY_POOL(Query_Login);


/*********************************************************
    FromLobbyToDB_Login_REQ
*********************************************************/
void FromLobbyToDB_Login_REQ (TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
    Query_Login * pQuery = Query_Login::ALLOC();
    if ( NULL == pQuery ) {
        return;
    }

    // 取得数据
    char _sshKey[33];
    if ( wSize>=sizeof(UserPacket) ) {
        pQuery->m_cPacket.SetPacket( (BYTE*) pMsg, wSize );
        pQuery->m_cPacket.ToPrint();
    }

    char szQueryBuff[256] = {0};
	snprintf( szQueryBuff, sizeof(szQueryBuff), " call p_UserLogin(%d, \'%s\'); ",
        pQuery->m_cPacket.GetUserId(), pQuery->m_cPacket.GetSSHKey() );

    pQuery->SetIndex( MAKEDWORD( (WORD)FromDBToDB_PID, (WORD)Login_DBR ) );
    pQuery->SetQuery( szQueryBuff );
    pQuery->SetVoidObject( pServerSession );
    pServerSession->DBQuery( pQuery );
}

/*********************************************************
    Query_GamePacket
*********************************************************/
class Query_GamePacket : public MydbcQueryResult
{
	_DECLARE_QUERY_POOL(Query_GamePacket);

public:

    UserPacket m_cPacket;   // 数据包

	enum { RESULT_COL_NUM = 6, PARAM_COL_NUL = 0, };

	struct sRESULT {
        int  m_byError;
        char m_szName[33];      // 逃跑次数
		int  m_iPoints; 	    // 分数
		int  m_iWons; 		    // 失败次数
		int  m_iFaileds; 	    // 赢的次数
		int  m_iAways; 		    // 逃跑次数
		sRESULT() {
		    memset( this, 0, sizeof(sRESULT) );
		}
	};

	ULONG uLength[RESULT_COL_NUM]; // 4
	vector<sRESULT> vctRes;

	void AllocData()
	{
		sRESULT m_RESULT;
		memset(&m_RESULT, 0, sizeof( m_RESULT) );
		vctRes.push_back( m_RESULT );
	}

	void InitData() { vctRes.clear(); }
	void dealData() { vctRes.pop_back(); }

	_BEGIN_BINDING_DATA( sRESULT, vctRes, uLength, 1, RESULT_COL_NUM )
        _BINDING_COLUMN(0, m_byError)
        _BINDING_COLUMN_PTR(1, m_szName)
		_BINDING_COLUMN(2, m_iPoints)
		_BINDING_COLUMN(3, m_iWons)
		_BINDING_COLUMN(4, m_iFaileds)
		_BINDING_COLUMN(5, m_iAways)
	_END_BINDING_DATA()
};
_IMPL_QUERY_POOL(Query_GamePacket);


/*********************************************************
    UserQuery_GamePacket
*********************************************************/
int UserQuery_GamePacket ( TemplateServerSession * pServerSession, UserPacket & pack, UINT _userid, UINT _gametype = 6 )
{
    Query_GamePacket * pQuery = Query_GamePacket::ALLOC();
    if ( NULL == pQuery ) {
        return -1;     // 比较忙
    }

    // 取得数据
    pQuery->m_cPacket.SetPacket( (BYTE*) &pack, pack.GetPacketSize() );
    pQuery->m_cPacket.ToPrint();

    char szQueryBuff[256] = {0};
	snprintf( szQueryBuff, sizeof(szQueryBuff), " call p_UserGamePacket(%d, %d); ", _userid, _gametype );

    pQuery->SetIndex( MAKEDWORD( (WORD)FromDBToDB_PID, (WORD)GamePacket_DBR ) );
    pQuery->SetQuery( szQueryBuff );
    pQuery->SetVoidObject( pServerSession );
    pServerSession->DBQuery( pQuery );
    return 0;
}

/************************************************
    FromDBToDB_Login_DBR
************************************************/
void FromDBToDB_Login_DBR ( TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
    MSG_DBPROXY_RESULT * msg = (MSG_DBPROXY_RESULT*) pMsg;
    Query_Login * pQuery = (Query_Login*) msg->m_pData;
    if ( pQuery )
    {
        if ( pQuery->vctRes.size() > 0 )
        {
            int iError = pQuery->vctRes[0].m_byError;
            if ( iError == 0 ) {
                pQuery->m_cPacket.GetLoginTime() = pQuery->vctRes[0].m_uiLoginTime;

                pQuery->m_cPacket.GetProtocol() = MAKEDWORD( (WORD)FromDBToLobby_PID, (WORD)Login_ANC );
                pServerSession->Send( (BYTE*)&pQuery->m_cPacket, sizeof(pQuery->m_cPacket) );

                UserQuery_GamePacket(pServerSession, pQuery->m_cPacket,
                    pQuery->m_cPacket.GetUserId());
            }
        }
		Query_Login::FREE(pQuery);
    }
}

/************************************************
    FromDBToDB_GamePacket_DBR
************************************************/
void FromDBToDB_GamePacket_DBR ( TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
    MSG_DBPROXY_RESULT * msg = (MSG_DBPROXY_RESULT*) pMsg;
    Query_GamePacket * pQuery = (Query_GamePacket*) msg->m_pData;
    if ( NULL == pQuery ) {
        return;
    }

    if ( pQuery->vctRes.size() > 0 )
    {
        int iError = pQuery->vctRes[0].m_byError;
        if ( iError == 0 ) {
            pQuery->m_cPacket.GetMoney() = pQuery->vctRes[0].m_iPoints;
            pQuery->m_cPacket.GetWoneds() = pQuery->vctRes[0].m_iWons;
            pQuery->m_cPacket.GetFaileds() = pQuery->vctRes[0].m_iFaileds;
            pQuery->m_cPacket.GetAways() = pQuery->vctRes[0].m_iAways;
            memcpy( pQuery->m_cPacket.GetName(), pQuery->vctRes[0].m_szName, 32 );
            pQuery->m_cPacket.ToPrint();

            pQuery->m_cPacket.GetProtocol() = MAKEDWORD( (WORD)FromDBToLobby_PID, (WORD)GamePacket_ANC );
            pServerSession->Send( (BYTE*)&pQuery->m_cPacket, sizeof(pQuery->m_cPacket) );
        }
        Query_GamePacket::FREE(pQuery);
        return ;    // 与用户游戏参数一起发送
    }
    Query_GamePacket::FREE(pQuery);
}

/*********************************************************
    FromDBToLobby_Login_ANC
*********************************************************/
void FromDBToLobby_Login_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    if ( wSize>=sizeof(UserPacket) ) {
        UserPacket packet;
        packet.SetPacket( (BYTE*) pMsg, wSize );

        packet.GetProtocol() = MAKEDWORD( (WORD)FromLobbyToAgent_PID, (WORD)Login_ANC );
        g_pLobbyServer->SendTo( (WORD)packet.GetAgentKey(), (BYTE*)&packet, sizeof(packet) );
    }
}

/*********************************************************
    FromLobbyToAgent_GamePacket_ANC
*********************************************************/
void FromLobbyToAgent_Login_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    UINT _logintime(0);
    if ( wSize>=sizeof(UserPacket) )
    {
        UserPacket packet;
        packet.SetPacket( (BYTE*)pMsg,wSize );
        _logintime = packet.GetLoginTime();
        packet.GetProtocol() = MAKEDWORD( (WORD)FromLoginToClient_PID, (WORD)Login_ANC );

        char szJsonBuff[1024] = {0};
        if ( _logintime!=0 ) {
            snprintf( szJsonBuff, sizeof(szJsonBuff), " {\"protocol\":%d,\"userid\":%d,\"userkey\":%d,\"errmsg\":%d} ",
                packet.GetProtocol(), packet.GetUserId(),  packet.GetUserKey(),  0 );
        }
        else {
            snprintf( szJsonBuff, sizeof(szJsonBuff), " {\"protocol\":%d,\"userid\":%d,\"userkey\":%d,\"errmsg\":%d} ",
                packet.GetProtocol(), packet.GetUserId(),  packet.GetUserKey(),  999 );
        }

        int iLength = strlen(szJsonBuff);
        g_pAgentServer->SendTo(packet.GetUserKey(), (BYTE*)szJsonBuff, iLength);

        DEBUG_MSG( LVL_DEBUG, "Login_ANC: %s \n", szJsonBuff);
        if ( _logintime!=0 ) {

        }
    }
}

/*********************************************************
    FromDBToLobby_GamePacket_ANC
*********************************************************/
void FromDBToLobby_GamePacket_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    if ( wSize>=sizeof(UserPacket) ) {
        UserPacket packet;
        packet.SetPacket( (BYTE*) pMsg, wSize );

        packet.GetProtocol() = MAKEDWORD( (WORD)FromLobbyToAgent_PID, (WORD)GamePacket_ANC );
        g_pLobbyServer->SendTo( (WORD)packet.GetAgentKey(), (BYTE*)&packet, sizeof(packet) );
    }
}

/*********************************************************
    FromLobbyToAgent_GamePacket_ANC
*********************************************************/
void FromLobbyToAgent_GamePacket_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    UINT _logintime(0);
    if ( wSize>=sizeof(UserPacket) )
    {
        UserPacket packet;
        packet.SetPacket( (BYTE*)pMsg,wSize );
        _logintime = packet.GetLoginTime();
        packet.GetProtocol() = MAKEDWORD( (WORD)FromLobbyToAgent_PID, (WORD)Login_ANC );

        _logintime = packet.GetLoginTime();
        if ( _logintime!=0 )
        {
            if ( packet.GetUserKey()!=0 )
            {
                char _szMsg[1024] = {0};
                char _format[256] = "{\"protocol\":\"%d\",\"userid\":%d,"
                        "\"data\":[{\"points\":%d,\"wons\":%d,\"faileds\":%d,\"aways\":%d,\"name\":\"%s\"}]}";
                snprintf( _szMsg, sizeof(_szMsg), _format, packet.GetProtocol(), packet.GetUserId(),
                    packet.GetWoneds(), packet.GetFaileds(), packet.GetAways(), packet.GetName() );

                WORD nLen = strlen( _szMsg );
                g_pAgentServer->SendTo( packet.GetUserKey(), (BYTE*)_szMsg, nLen);
            }
        }
    }
}
