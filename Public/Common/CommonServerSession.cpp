#include "CommonServerSession.h"
#include "CommonInclude.h"

CommonServerSession::CommonServerSession()
{
}

CommonServerSession::~CommonServerSession()
{
}

void CommonServerSession::Init()
{
	this->Clear();

}

void CommonServerSession::Clear()
{
	m_dwSessionIndex 	    = 0;
	m_wConnectPort 		    = 0;
	m_bForConnect 		    = FALSE;
	m_dwLastHeartbeatTime   = NetworkSession::GetTickCount();
	m_bConnection 		    = FALSE;
	m_strConnectIP.clear();
}


void CommonServerSession::Update()	// 心跳
{
#if 0
	if ( this->IsForConnect() )
	{
		DWORD dwCurTick = Session::GetTickCount();
		if ( dwCurTick - m_dwLastHeartbeatTime > 10000)
		{
			m_dwLastHeartbeatTime = dwCurTick;

			MSG_HEARTBEAT msg;
			msg.m_byCategory	= 0;
	//		msg.m_byProtocol    = SERVERCOMMON_HEARTBEAT;
			Send( (BYTE*)&msg, sizeof(MSG_HEARTBEAT) );
		}
	}
#endif
}

void CommonServerSession::Release()
{
	m_strConnectIP.clear();
}

void CommonServerSession::OnAccept( DWORD dwNetworkIndex )
{
	SetForConnect( FALSE );
	SetSessionIndex( dwNetworkIndex );
	m_bConnection = TRUE;
}

void CommonServerSession::OnConnect( BOOL bSucces, DWORD dwNetworkIndex )
{
	if ( bSucces )
	{
		SetForConnect( TRUE );
		SetSessionIndex( dwNetworkIndex );
		m_bConnection = TRUE;
	}
}

void CommonServerSession::OnDisconnect()
{
	m_bConnection = FALSE;
}

void CommonServerSession::OnRecv( BYTE *pMsg, WORD wSize )
{
}

void CommonServerSession::OnLogString( char * pszLog )
{

}

void CommonServerSession::SendServerType()
{
	MSG_SERVER_TYPE 	msg;
	msg.m_byCategory 	= 0;
	msg.m_byCategory 	= 0;
	msg.m_byServerType 	= GetServerType(); // AGENT_SERVER
	Send( (BYTE *)&msg, sizeof(MSG_SERVER_TYPE) );

}

void CommonServerSession::SetAddr( char * pszIP, WORD wPort )
{
	m_strConnectIP = pszIP;
	m_wConnectPort = wPort;
}

BOOL CommonServerSession::TryToConnect()
{
	if ( m_strConnectIP.empty() ) {
		return FALSE;
	}

	if ( m_bConnection )
		return FALSE;

	return TRUE;
}

void CommonServerSession::DBQuery( Query * pQuery ) {
    //g_CnpokerServer->DBQuery(pQuery);
    //m_Database.DBQuery( pQuery );
}

WORD CommonServerSession::GetUserKey() {
    return 0;
}

int CommonServerSession::GetUserid() {
    return 0;
}
