#include "TemplateInclude.h"

TemplateServerSession::TemplateServerSession()
{
}

TemplateServerSession::~TemplateServerSession()
{
}

void TemplateServerSession::Init()
{
	this->Clear();
}

void TemplateServerSession::Clear()
{
	m_dwSessionIndex 	    = 0;
	m_wConnectPort 		    = 0;
	m_bForConnect 		    = FALSE;
	m_dwLastHeartbeatTime   = NetworkSession::GetTickCount();
	m_bConnection 		    = FALSE;
	m_strConnectIP.clear();
}


void TemplateServerSession::Update()	// 心跳
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
	//		msg.m_byProtocol    = SERVERTemplate_HEARTBEAT;
			Send( (BYTE*)&msg, sizeof(MSG_HEARTBEAT) );
		}
	}
#endif
}

void TemplateServerSession::Release()
{
	m_strConnectIP.clear();
}

void TemplateServerSession::OnAccept( DWORD dwNetworkIndex )
{
	SetForConnect( FALSE );
	SetSessionIndex( dwNetworkIndex );
	m_bConnection = TRUE;
}

void TemplateServerSession::OnConnect( BOOL bSucces, DWORD dwNetworkIndex )
{
	if ( bSucces )
	{
		SetForConnect( TRUE );
		SetSessionIndex( dwNetworkIndex );
		m_bConnection = TRUE;
	}
}

void TemplateServerSession::OnDisconnect()
{
	m_bConnection = FALSE;
}

void TemplateServerSession::OnRecv( BYTE *pMsg, WORD wSize )
{
}

void TemplateServerSession::OnLogString( char * pszLog )
{
}

void TemplateServerSession::SendServerType()
{
	MSG_SERVER_TYPE 	msg;
	msg.m_byCategory 	= 0;
	msg.m_byCategory 	= 0;
	msg.m_byServerType 	= GetServerType();
	Send( (BYTE *)&msg, sizeof(MSG_SERVER_TYPE) );
}

void TemplateServerSession::SetAddr( char * pszIP, WORD wPort )
{
	m_strConnectIP = pszIP;
	m_wConnectPort = wPort;
}

BOOL TemplateServerSession::TryToConnect()
{
	if ( m_strConnectIP.empty() ) {
		return FALSE;
	}
	if ( m_bConnection )
		return FALSE;
	return TRUE;
}

void TemplateServerSession::DBQuery( Query * pQuery ) {
}
