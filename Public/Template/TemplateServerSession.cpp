#include "TemplateInclude.h"
#include "TemplateSeasoning.h"
#include "TemplateMainServer.h"
#include "TemplatePacketHandler.h"

void CallBackMessage( char * szMessage )
{
    DEBUG_MSG( LVL_DEBUG, " MydbcDatabaseDesc Error : %s! ", szMessage );
}

void CallBackQueryResult( DWORD dwIndex, MydbcQueryResult * pData)
{
    WORD byPacketCategory = (WORD) LOWORD( dwIndex );
    WORD byPacketType     = (WORD) HIWORD( dwIndex );
    ((TemplateServerSession*)pData->GetVoidObject())->DBResult(byPacketCategory, byPacketType, pData);
}

TemplateServerSession::TemplateServerSession()
{
}

TemplateServerSession::~TemplateServerSession()
{
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

void TemplateServerSession::Init()
{
	this->Clear();
	TemplateServerSession::InitDatabase();
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

    TemplateSeasoning system;
    if ( system.GetOpenDatabase()==TRUE ) {
        ReleaseDatabase();
    }
}

BOOL TemplateServerSession::InitDatabase()
{
    TemplateSeasoning system;
    if ( system.GetOpenDatabase()==FALSE ) {
        return FALSE;
    }

    MydbcDatabaseDesc db_descNew;
	db_descNew.DataBaseModuleType			= DBCInterfaceType_MYSQL;
	db_descNew.dwQueryPoolSize				= 2000;
	db_descNew.wQueryProcessorNum			= 1;
	db_descNew.pszDatabaseIP				= system.GetDBAddress();
	db_descNew.pszDatabaseName				= system.GetDBName();
	db_descNew.pszUserName					= system.GetDBUsername();
	db_descNew.pszUserPassword				= system.GetDBPassword();
	db_descNew.fnErrorMessage				= CallBackMessage;
	db_descNew.fnQueryResult                = CallBackQueryResult;

	if ( !m_Database.Initialize(db_descNew) ) {
        printf( "Connect to db failed!");
        return FALSE;
    }

    printf( "Connect to db succ!");
    return TRUE;
}

BOOL TemplateServerSession::UpdateDatabase()
{
    TemplateSeasoning system;
    if ( system.GetOpenDatabase()==FALSE ) {
        return FALSE;
    }

    m_Database.Update();
    return TRUE;
}

BOOL TemplateServerSession::ReleaseDatabase()
{
	m_Database.Release();
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

void TemplateServerSession::DBQuery( Query * pQuery )
{
    m_Database.DBQuery( pQuery );
}

void TemplateServerSession::DBResult( WORD cate, WORD ptcl, MydbcQueryResult * pData )
{
    MSG_DBPROXY_RESULT msg;
    msg.m_byCategory = cate;
    msg.m_byProtocol = ptcl;
    msg.m_pData = pData;
	
	int iPid = MAKEDWORD((WORD)cate,(WORD)ptcl);
    TemplatePacketHandler::ParsePacket_DB( iPid, this, (MSG_BASE*)&msg, sizeof(MSG_DBPROXY_RESULT) );
}
