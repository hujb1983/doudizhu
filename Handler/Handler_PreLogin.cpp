#include "Handler_Module.h"
#include <UtilityDrng.h>
#include <UtilityMD5.h>
#include <MydbcQueryResult.h>
#include <UtilityParserJson.h>
#include "PacketLogin.h"
#include "LoginServer.h"
#include "DBServer.h"


#define CODE_KEY_LEN 32

/************************************************
    FromClientToLogin_PreLogin_REQ
************************************************/
void FromClientToLogin_PreLogin_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
	UtilityParserJson jsMap;
    if ( jsMap.SetJson( (char*) pMsg ) ) {
        return;
    }

	LoginPacket packet;
	packet.ToInit();
    packet.GetUserKey()  = pServerSession->GetSessionIndex();
    packet.GetAccessID() = 100;
    packet.GetGameType() = 2;
    packet.GetLoginType() = 6;

    char  * _cUsername = packet.GetUsername();
    char  * _cPassword = packet.GetPassword();
    char  * _cSshKey   = packet.GetSSHKey();

    jsMap.ReadString ( "username",  _cUsername, 33 );
    jsMap.ReadString ( "password",  _cPassword, 33 );
    jsMap.ReadString ( "sshkey",    _cSshKey  , 33 );

    packet.GetProtocol() = MAKEDWORD( FromLoginToDB_PID, PreLogin_REQ );
    g_pLoginServer->SendToDB( (BYTE*)&packet, sizeof(LoginPacket) );
}

/************************************************
    FromDBToLogin_PreLogin_ANC
************************************************/
void FromDBToLogin_PreLogin_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
	if ( wSize<sizeof(LoginPacket) ) {
		return; // 发送的包数据不正确,丢失;
	}

	LoginPacket * packet = (LoginPacket *) pMsg;

	char szJsonBuff[1024]  = {0};
	char format[256] = 	"{\"protocol\":\"%d\","
						" \"data\":{"
						" \"errmsg\":\"0\","
						" \"sshkey\":\"%s\","
						" \"userid\":\"%d\","
						" \"sip\":\"%s\","
						" \"port\":\"%d\"} }";

	sprintf( szJsonBuff, format, MAKEDWORD( (WORD)FromLoginToClient_PID, (WORD)PreLogin_ANC ),
        packet->GetSSHKey(), packet->GetUserid(), packet->GetAddress(), packet->GetPort() );

    DEBUG_MSG( LVL_DEBUG, "szJsonBuff = {%s}", szJsonBuff);
    WORD wKey = packet->GetUserKey();
    g_pLoginServer->SendTo( wKey, (BYTE*)szJsonBuff, strlen(szJsonBuff) );
}

/************************************************
    Query_PreLogin
************************************************/
#pragma pack(push,1)
class Query_PreLogin : public MydbcQueryResult
{
	_DECLARE_QUERY_POOL( Query_PreLogin );

public:
	LoginPacket m_cPacket;

	enum {
		RESULT_COL_NUM = 4,
		PARAM_COL_NUL  = 0,
	};

	struct sRESULT {
		int 		    m_iError;
		unsigned int    m_uiUserID;
		unsigned int    m_uiPort;
		char            m_szIP[16];
		sRESULT() {
			memset( this, 0, sizeof(sRESULT) );
		}
	};

	ULONG uLength[RESULT_COL_NUM]; // 4
	vector<sRESULT> vctRes;

	void AllocData() {
		sRESULT m_RESULT;
		memset(&m_RESULT, 0, sizeof( m_RESULT) );
		vctRes.push_back( m_RESULT );
	}

	void InitData() { vctRes.clear(); }
	void dealData() { vctRes.pop_back(); }

	_BEGIN_BINDING_DATA( sRESULT, vctRes, uLength, 1, RESULT_COL_NUM)
		_BINDING_COLUMN(0, m_iError)
		_BINDING_COLUMN(1, m_uiUserID)
		_BINDING_COLUMN(2, m_uiPort)
		_BINDING_COLUMN(3, m_szIP)
	_END_BINDING_DATA()
};
_IMPL_QUERY_POOL(Query_PreLogin);
#pragma pack(pop)


/************************************************
    FromLoginToDB_PreLogin_REQ
************************************************/
void FromLoginToDB_PreLogin_REQ ( TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
	if ( wSize<sizeof(LoginPacket) ) {
		return; // 发送的包数据不正确,丢失;
	}

	LoginPacket * packet = (LoginPacket *) pMsg;
	char * _cUsername = packet->GetUsername();
	char * _cPassword = packet->GetPassword();
	char * _cSshKey   = packet->GetSSHKey();
	int _iGameID	= packet->GetGameType();
	int _iLoginType = packet->GetLoginType();

	// 生成 用户 MD5s( 随机数 + lastime + rid )
	char szUserSshKey[ CODE_KEY_LEN + 1 ] = { 0 }; // 33位
	char szRandom[11] = {0};    // 生成一个5位的随机值
	if ( is_support_drng() ) {// 支持随机数
		GetRandom(szRandom);
	}
	else {// 不支持随机数
		GetRandom_C(szRandom);
	}
	printf("Random = %s\n", szRandom);

	// MD5加密
	string tmpStr(szRandom);
	string outMD5 = UtilityMD5(tmpStr).toString() ;
	sprintf( (char *)szUserSshKey, "%s", outMD5.c_str() );
	szUserSshKey[ CODE_KEY_LEN ] = '\0';
	printf("User SSH Key = %s\n", szUserSshKey );

	char szQueryBuff[256] = {0};
	snprintf( szQueryBuff, sizeof(szQueryBuff), "call p_PreLogin(\'%s\',\'%s\',\'%s\',\'%s\', %d, %d)",
		_cUsername, _cPassword, _cSshKey, szUserSshKey, _iGameID, _iLoginType );

	Query_PreLogin * pQuery = Query_PreLogin::ALLOC();
    if ( NULL == pQuery ) {
        return;
    }
	pQuery->m_cPacket.SetPacket( (BYTE*)packet, sizeof(LoginPacket) );
	pQuery->SetIndex( MAKEDWORD( (WORD)FromDBToDB_PID, (WORD)PreLogin_DBR ) );
	pQuery->SetQuery( szQueryBuff );
	pQuery->SetVoidObject( pServerSession );
	pServerSession->DBQuery( pQuery );
	return;
}


/************************************************
    FromDBToDB_PreLogin_DBR
************************************************/
void FromDBToDB_PreLogin_DBR ( TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
    MSG_DBPROXY_RESULT * msg = (MSG_DBPROXY_RESULT*) pMsg;
    Query_PreLogin * pQuery = (Query_PreLogin*) msg->m_pData;
    if ( pQuery ) {
		if (pQuery->vctRes.size()!=0)
        {
			if (pQuery->vctRes[0].m_iError==0)
			{
				LoginPacket * packet = &pQuery->m_cPacket;
				packet->GetUserid() = pQuery->vctRes[0].m_uiUserID;

				char * szIP = packet->GetAddress();
				memcpy( szIP, pQuery->vctRes[0].m_szIP, strlen(pQuery->vctRes[0].m_szIP) );
				packet->GetPort() = pQuery->vctRes[0].m_uiPort;

                packet->GetProtocol() = MAKEDWORD( FromDBToLogin_PID, PreLogin_ANC );
                pServerSession->Send( (BYTE*)packet, sizeof(LoginPacket) );
			}
		}
		Query_PreLogin::FREE(pQuery);
    }
}
