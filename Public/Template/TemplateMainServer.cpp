#include "TemplateInclude.h"
#include "TemplateMainServer.h"

TemplateServerSession * TemplateMainServer::m_pSessionArray[MAX_PORT+1];
UtilityKeyGenerator TemplateMainServer::m_cObjectKeys;

TemplateMainServer::TemplateMainServer(void)
{
	m_bShutdown		= FALSE;
	m_pServer 		= NULL;
}

TemplateMainServer::~TemplateMainServer(void)
{
}

BOOL TemplateMainServer::Init()
{
}

BOOL TemplateMainServer::StartServerSideListen(WORD wPort)
{
	if ( m_pServer!=NULL ) {
		if( !m_pServer->IsListening( SERVER_SYNCHANDLER) ) {
			if ( !m_pServer->StartListen(SERVER_SYNCHANDLER, "", wPort) )  {
				return true;
			}
		}
	}
	return false;
}

BOOL TemplateMainServer::StartClientSideListen(WORD wPort)
{
	if ( m_pServer!=NULL ) {
		if( !m_pServer->IsListening( CLIENT_SYNCHANDLER) ) {
			if ( !m_pServer->StartListen(CLIENT_SYNCHANDLER, "", wPort) )  {
				return true;
			}
		}
	}
	return false;
}

BOOL TemplateMainServer::ConnectToServer( TemplateServerSession * pSession, char * pszIP, WORD wPort )
{
	if (pSession!=NULL) {
		return m_pServer->Connect( SERVER_SYNCHANDLER, (NetworkObject *)pSession, pszIP, wPort );
		Sleep(1000);
	}
	return FALSE;
}

BOOL TemplateMainServer::MaintainConnection()
{
	if (m_bShutdown) {
		return TRUE;
	}

	/* if (m_pLobbyServer->TryToConnect()) {
		ConnectToServer( m_pLobbyServer, (char *)m_pLobbyServer->GetConnnectIP().c_str(), m_pLobbyServer->GetConnnectPort() );
	} */
}

BOOL TemplateMainServer::Update( DWORD dwDeltaTick )
{
	if (m_bShutdown) {
		return TRUE;
	}
	
	MaintainConnection();
}

BOOL TemplateMainServer::SendTo( WORD wKey, BYTE * pMsg, WORD wSize)
{
	TemplateServerSession * pSession = TemplateMainServer::m_pSessionArray[wKey];
	if (pSession!=NULL) {
		pSession->Send(pMsg, wSize);
	}
	return TRUE;
}

/**************************************************************
	服务器共享连接信息
**************************************************************/
void TemplateMainServer::InitSessionArray() {
	TemplateMainServer::m_cObjectKeys.Create(1,MAX_PORT);
}
void TemplateMainServer::CloseSessionArray(){

}
DWORD TemplateMainServer::AllocSessionKey() {
	TemplateMainServer::m_cObjectKeys.GetKey();
}
void TemplateMainServer::FreeSessionKey(DWORD wIndex) {
	TemplateMainServer::m_cObjectKeys.RestoreKey( wIndex );
}
DWORD TemplateMainServer::SetSession(TemplateServerSession * pSession) {
	WORD wKey = pSession->GetSessionIndex();
	if ( TemplateMainServer::m_pSessionArray[wKey]!=NULL ) {
		TemplateMainServer::FreeSession(wKey); //先释放
	}
	TemplateMainServer::m_pSessionArray[wKey] = pSession;
}
void TemplateMainServer::FreeSession(DWORD wIndex) {
	if (wIndex<MAX_PORT) {
		WORD wKey = (WORD)wIndex;
		TemplateMainServer::m_pSessionArray[wKey] = NULL;
		TemplateMainServer::FreeSessionKey(wKey);
	}
}
	
/**************************************************************
	创建服务器信息
**************************************************************/
NetworkObject * CreateServerSideAcceptedObject() {
	DEBUG_MSG( LVL_DEBUG, "CreateServerSideAcceptedObject. \n" );
	TemplateTempSession * obj = TemplateSessionFactory::Instance()->AllocTempSession();
	if (obj==NULL) {
        DEBUG_MSG( LVL_ERROR, "TemplateTempSession Fail . \n");
		return NULL;
	}
	return (NetworkObject*)(obj);
}

VOID DestroyServerSideAcceptedObject( NetworkObject *pObjs ) {
	DEBUG_MSG( LVL_TRACE, "DestroyServerSideAcceptedObject. \n");
	TemplateServerSession * pSession = (TemplateServerSession*)pObjs;
	eSERVER_TYPE eType = pSession->GetServerType();
	if ( eType==TEMP_SERVER ) {
		DEBUG_MSG( LVL_TRACE, ">>>FreeGameSession( %x )\n", pObjs);
		TemplateTempSession * obj = (TemplateTempSession*)pObjs;
		TemplateSessionFactory::Instance()->FreeTempSession(obj);
	}
	else if ( eType==LOGIN_SERVER ) {
		DEBUG_MSG( LVL_TRACE, ">>>FreeTempSession( %x )\n", pObjs);
		TemplateLoginSession * obj = (TemplateLoginSession*)pObjs;
		TemplateSessionFactory::Instance()->FreeLoginSession(obj);
    }
	else if ( eType==AGENT_SERVER ) {
		DEBUG_MSG( LVL_TRACE, ">>>FreeTempSession( %x )\n", pObjs);
		TemplateAgentSession * obj = (TemplateAgentSession*)pObjs;
		TemplateSessionFactory::Instance()->FreeAgentSession(obj);
    }
	else if ( eType==LOBBY_SERVER ) {
		DEBUG_MSG( LVL_TRACE, ">>>FreeTempSession( %x )\n", pObjs);
		TemplateLobbySession * obj = (TemplateLobbySession *)pObjs;
		TemplateSessionFactory::Instance()->FreeLobbySession(obj);
    }
	else if ( eType==GAME_SERVER ) {
		DEBUG_MSG( LVL_TRACE, ">>>FreeTempSession( %x )\n", pObjs);
		TemplateGameSession * obj = (TemplateGameSession *)pObjs;
		TemplateSessionFactory::Instance()->FreeGameSession(obj);
    }
	else if ( eType==DB_SERVER ) {
		DEBUG_MSG( LVL_TRACE, ">>>FreeTempSession( %x )\n", pObjs);
		TemplateDBSession * obj = (TemplateDBSession *)pObjs;
		TemplateSessionFactory::Instance()->FreeDBSession(obj);
    }
}

VOID DestroyServerSideConnectedObject( NetworkObject *pNetworkObject ) {
     DEBUG_MSG( LVL_TRACE, "DestroyServerSideConnectedObject. \n");
}

/**************************************************************
	创建客户端信息
**************************************************************/
NetworkObject * CreateClientSideAcceptedObject() {
    DEBUG_MSG( LVL_TRACE, "CreateClientSideAcceptedObject. \n");
	TemplateUserSession * pObj = TemplateSessionFactory::Instance()->AllocUserSession();
	if ( pObj==NULL ) {
		DEBUG_MSG( LVL_TRACE, "AllocUserSession Fail.\n");
		return NULL;
	}
	pObj->Init();
	return (NetworkObject*)(pObj);
}

VOID DestroyClientSideAcceptedObject( NetworkObject * pObjs ) {
    DEBUG_MSG( LVL_TRACE, "DestroyClientSideAcceptedObject. \n");
	TemplateUserSession * pSession = (TemplateUserSession *)pObjs;
	assert( pSession );
	pSession->Release();
}

VOID DestroyClientSideConnectedObject( NetworkObject * pNetworkObject ) {
	DEBUG_MSG( LVL_TRACE, "DestroyClientSideConnectedObject. \n");
}

