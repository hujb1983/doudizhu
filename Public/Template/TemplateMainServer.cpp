#include "TemplateInclude.h"
#include "TemplateMainServer.h"
#include "TemplateSeasoning.h"
#include "TemplatePacketHandler.h"

TemplateServerSession * TemplateMainServer::m_pSessionArray[MAX_PORT+1];
UtilityKeyGenerator TemplateMainServer::m_cObjectKeys;
WORD TemplateMainServer::m_uiCountKey;

TemplateMainServer::TemplateMainServer(void)
{
	m_bShutdown		= FALSE;
	m_pServer 		= NULL;
}

TemplateMainServer::~TemplateMainServer(void)
{
    if ( m_pServer ) {
		delete m_pServer;
	}
}

BOOL TemplateMainServer::Init()
{
	m_desc[0].fnCreateAcceptedObject    = CreateServerSideAcceptedObject;
	m_desc[0].fnDestroyAcceptedObject	= DestroyServerSideAcceptedObject;
	m_desc[0].fnDestroyConnectedObject	= DestroyServerSideConnectedObject;
    m_desc[1].fnCreateAcceptedObject	= CreateClientSideAcceptedObject;
	m_desc[1].fnDestroyAcceptedObject	= DestroyClientSideAcceptedObject;
	m_desc[1].fnDestroyConnectedObject	= DestroyClientSideConnectedObject;

    m_pServer = new NetworkServer;
    if ( !m_pServer->Init( m_desc, 2 ) ) {
		return FALSE;
	}

	if ( m_wPort[0]!=0 ) {
        DEBUG_MSG( LVL_DEBUG, "StartServerSideListen:(%d);", m_wPort[0]);
        StartServerSideListen(m_wPort[0]);
	}
	if ( m_wPort[1]!=0 ) {
        DEBUG_MSG( LVL_DEBUG, "StartClientSideListen:(%d);", m_wPort[1]);
        StartClientSideListen(m_wPort[1]);
	}
	return TRUE;
}

void TemplateMainServer::StartServer()
{
	TemplateSessionFactory::Instance()->Init();

	if( !this->Init() )
    {
        printf( "Init failed! \n");
		return;
	}

    m_bShutdown = TRUE;
	while( m_bShutdown )
    {
		usleep(20);
		if ( !Update( 0 ) )
        {
			break;
		}
	}

	TemplateSessionFactory::Instance()->DestroyInstance();
	TemplatePacketHandler::Release();
	printf( "Shutdown Server! \n");
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
        Sleep(1000);
        DEBUG_MSG( LVL_DEBUG, "ConnectToServer(%s,%d)." , pszIP, wPort);
		return m_pServer->Connect( SERVER_SYNCHANDLER, (NetworkObject *)pSession, pszIP, wPort );
	}
	return FALSE;
}

void TemplateMainServer::ServerConnector( TemplateServerSession * pSession )
{
    if ( pSession ) {
        if ( pSession->TryToConnect() ) {
            WORD wPort = pSession->GetConnnectPort();
            std::string szIP = pSession->GetConnnectIP();
            ConnectToServer( pSession, (char*)szIP.c_str(), wPort );
        }
	}
}

BOOL TemplateMainServer::MaintainConnection()
{
	if (m_bShutdown) {
		return TRUE;
	}

	// 连接指定服务器
	ServerConnector( m_pLoginSession );
	ServerConnector( m_pAgentSession );
	ServerConnector( m_pLobbySession );
	ServerConnector( m_pGameSession  );
	ServerConnector( m_pDBSession    );
}

BOOL TemplateMainServer::Update( DWORD dwDeltaTick )
{
	if (m_pServer) {
		m_pServer->Update();
	}

	MaintainConnection();

    TemplateSeasoning system;
    if ( system.GetOpenDatabase()==TRUE ) {
	    UpdateDatabase( dwDeltaTick );
	}

	return TRUE;
}

BOOL TemplateMainServer::UpdateDatabase( DWORD dwDeltaTick )
{
    WORD wJumpObject = 0;
    WORD wSumObject = TemplateMainServer::m_uiCountKey;
    for( int i=1; wJumpObject<wSumObject; ++i )
    {
        // DEBUG_MSG( LVL_DEBUG, "%d", i);
        TemplateServerSession * pSession = TemplateMainServer::m_pSessionArray[i];
        if ( pSession )
        {
            pSession->UpdateDatabase();
            wJumpObject++;
        }
    }
}

BOOL TemplateMainServer::SendTo( WORD wKey, BYTE * pMsg, WORD wSize)
{
	TemplateServerSession * pSession = TemplateMainServer::m_pSessionArray[wKey];
	if (pSession!=NULL) {
		pSession->Send( pMsg, wSize );
	}
	return TRUE;
}

BOOL TemplateMainServer::SendToLogin( BYTE * pMsg, WORD wSize ) 
{
	if (m_pLoginSession) {
		m_pLoginSession->Send( pMsg, wSize );
	}
	return TRUE;
}

BOOL TemplateMainServer::SendToAgent( BYTE * pMsg, WORD wSize ) 
{
	if (m_pAgentSession) {
		m_pAgentSession->Send( pMsg, wSize );
	}
	return TRUE;
}

BOOL TemplateMainServer::SendToLobby( BYTE * pMsg, WORD wSize ) 
{
	if (m_pLobbySession) {
		m_pLobbySession->Send( pMsg, wSize );
	}
	return TRUE;
}

BOOL TemplateMainServer::SendToGames( BYTE * pMsg, WORD wSize ) 
{
	if (m_pGameSession) {
		m_pGameSession->Send( pMsg, wSize );
	}
	return TRUE;
}

BOOL TemplateMainServer::SendToDB( BYTE * pMsg, WORD wSize ) 
{
	if (m_pDBSession) {
		m_pDBSession->Send( pMsg, wSize );
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
	DEBUG_MSG( LVL_DEBUG, " SetSession(%d)", wKey);
	TemplateMainServer::m_pSessionArray[wKey] = pSession;
	TemplateMainServer::m_uiCountKey++;
}
void TemplateMainServer::FreeSession(DWORD wIndex) {
	if (wIndex<MAX_PORT) {
		WORD wKey = (WORD)wIndex;
		TemplateMainServer::m_pSessionArray[wKey] = NULL;
		TemplateMainServer::FreeSessionKey(wKey);
		TemplateMainServer::m_uiCountKey--;
	}
}

/**************************************************************
	创建服务器信息
**************************************************************/
NetworkObject * CreateServerSideAcceptedObject() {
	DEBUG_MSG( LVL_DEBUG, "CreateServerSideAcceptedObject." );
	TemplateTempSession * obj = TemplateSessionFactory::Instance()->AllocTempSession();
	if (obj==NULL) {
        DEBUG_MSG( LVL_ERROR, "TemplateTempSession Fail.");
		return NULL;
	}
	obj->Clear();
	return (NetworkObject*)(obj);
}

VOID DestroyServerSideAcceptedObject( NetworkObject *pObjs ) {
	DEBUG_MSG( LVL_TRACE, "DestroyServerSideAcceptedObject.");
	TemplateServerSession * pSession = (TemplateServerSession*)pObjs;
	eSERVER_TYPE eType = pSession->GetServerType();
	if ( eType==TEMP_SERVER ) {
		DEBUG_MSG( LVL_TRACE, ">>>FreeTempSession(%x)", pObjs);
		TemplateTempSession * obj = (TemplateTempSession*)pObjs;
		TemplateMainServer::FreeSession( obj->GetSessionIndex() );
		TemplateSessionFactory::Instance()->FreeTempSession(obj);
	}
	else if ( eType==LOGIN_SERVER ) {
		DEBUG_MSG( LVL_TRACE, ">>>FreeLoginSession(%x)", pObjs);
		TemplateLoginSession * obj = (TemplateLoginSession*)pObjs;
		TemplateMainServer::FreeSession( obj->GetSessionIndex() );
		
		TemplateSessionFactory::Instance()->FreeLoginSession(obj);
    }
	else if ( eType==AGENT_SERVER ) {
		DEBUG_MSG( LVL_TRACE, ">>>FreeAgentSession(%x)", pObjs);
		TemplateAgentSession * obj = (TemplateAgentSession*)pObjs;
		TemplateMainServer::FreeSession( obj->GetSessionIndex() );
		obj->Release();
		TemplateSessionFactory::Instance()->FreeAgentSession(obj);
    }
	else if ( eType==LOBBY_SERVER ) {
		DEBUG_MSG( LVL_TRACE, ">>>FreeLobbySession(%x)", pObjs);
		TemplateLobbySession * obj = (TemplateLobbySession *)pObjs;
		TemplateMainServer::FreeSession( obj->GetSessionIndex() );
		obj->Release();
		TemplateSessionFactory::Instance()->FreeLobbySession(obj);
    }
	else if ( eType==GAME_SERVER ) {
		DEBUG_MSG( LVL_TRACE, ">>>FreeGameSession(%x)", pObjs);
		TemplateGameSession * obj = (TemplateGameSession *)pObjs;
		TemplateMainServer::FreeSession( obj->GetSessionIndex() );
		obj->Release();
		TemplateSessionFactory::Instance()->FreeGameSession(obj);
    }
	else if ( eType==DB_SERVER ) {
		DEBUG_MSG( LVL_TRACE, ">>>FreeDBSession(%x)", pObjs);
		TemplateDBSession * obj = (TemplateDBSession *)pObjs;
		TemplateMainServer::FreeSession( obj->GetSessionIndex() );
		obj->Release();
		TemplateSessionFactory::Instance()->FreeDBSession(obj);
    }
}

VOID DestroyServerSideConnectedObject( NetworkObject *pNetworkObject ) {
     DEBUG_MSG( LVL_TRACE, "DestroyServerSideConnectedObject.");
}

/**************************************************************
	创建客户端信息
**************************************************************/
NetworkObject * CreateClientSideAcceptedObject() {
    DEBUG_MSG( LVL_TRACE, "CreateClientSideAcceptedObject.");
	TemplateUserSession * pObj = TemplateSessionFactory::Instance()->AllocUserSession();
	if ( pObj==NULL ) {
		DEBUG_MSG( LVL_TRACE, "AllocUserSession Fail.");
		return NULL;
	}
	pObj->Init();
	return (NetworkObject*)(pObj);
}

VOID DestroyClientSideAcceptedObject( NetworkObject * pObjs ) {
    DEBUG_MSG( LVL_TRACE, "DestroyClientSideAcceptedObject.");
	TemplateUserSession * pSession = (TemplateUserSession *)pObjs;
	assert( pSession );
	pSession->Release();
	TemplateSessionFactory::Instance()->FreeUserSession(pSession);
}

VOID DestroyClientSideConnectedObject( NetworkObject * pNetworkObject ) {
	DEBUG_MSG( LVL_TRACE, "DestroyClientSideConnectedObject.");
}

