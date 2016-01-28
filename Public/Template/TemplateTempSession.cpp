#include "TemplateInclude.h"
#include "TemplateMainServer.h"
#include "TemplateSessionFactory.h"

TemplateTempSession::TemplateTempSession()
{
}

TemplateTempSession::~TemplateTempSession()
{

}

void TemplateTempSession::Clear()
{
	
}

void TemplateTempSession::OnRecv( BYTE *pMsg, WORD wSize ) 
{
	assert( m_bFirst==TRUE);
	if ( !m_bFirst) {
		return;
	}
	m_bFirst = FALSE;
	
	DEBUG_MSG( LVL_TRACE, "TempSession::OnRecv.");
	MSG_SERVER_TYPE * recvMsg = (MSG_SERVER_TYPE *)pMsg;
	
	TemplateServerSession * Obj = NULL;
	if ( recvMsg->m_byServerType == LOGIN_SERVER ) {
		DEBUG_MSG( LVL_TRACE, "TemplateTempSession [LOGIN_SERVER] Succ.");
		Obj = TemplateSessionFactory::Instance()->AllocLoginSession();
	}
	else if ( recvMsg->m_byServerType == AGENT_SERVER ) {
		DEBUG_MSG( LVL_TRACE, "TemplateTempSession [AGENT_SERVER] Succ.");
		Obj = TemplateSessionFactory::Instance()->AllocAgentSession();
	}
	else if ( recvMsg->m_byServerType == LOBBY_SERVER ) {
		DEBUG_MSG( LVL_TRACE, "TemplateTempSession [LOBBY_SERVER] Succ.");
		Obj = TemplateSessionFactory::Instance()->AllocLobbySession();
	}
	else if ( recvMsg->m_byServerType == GAME_SERVER ) {
		DEBUG_MSG( LVL_TRACE, "TemplateTempSession [GAME_SERVER] Succ.");
		Obj = TemplateSessionFactory::Instance()->AllocGameSession();
	}
	else if ( recvMsg->m_byServerType == DB_SERVER ) {
		DEBUG_MSG( LVL_TRACE, "TemplateTempSession [DB_SERVER] Succ.");
		Obj = TemplateSessionFactory::Instance()->AllocDBSession();
	}
	
	if ( Obj != NULL) {
		NetworkSession * pSession = this->m_pSession;
		if ( pSession != NULL ) {
			m_pSession->UnbindNetworkObject();
			pSession->BindNetworkObject(Obj);
		}
		
		DWORD wKey = TemplateMainServer::AllocSessionKey(); // 申请本服务器的全局Key
		Obj->SetSessionIndex(wKey);//赋值Key
		TemplateMainServer::SetSession(Obj);//存储对象
	}
	
	TemplateSessionFactory::Instance()->FreeTempSession(this);
}

void TemplateTempSession::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{
	
}

void TemplateTempSession::OnDisconnect()
{

}

void TemplateTempSession::OnLogString( char * pszLog)
{

}
