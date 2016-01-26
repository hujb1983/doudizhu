#include "TemplateSessionFactory.h"

TemplateSessionFactory::TemplateSessionFactory()
{
	m_pTempSessionPool  = NULL;
	m_pUserSessionPool  = NULL;
	m_pLoginSessionPool = NULL;
	m_pAgentSessionPool = NULL;
	m_pLobbySessionPool = NULL; 
	m_pGameSessionPool  = NULL;
	m_pDBSessionPool    = NULL;
}

TemplateSessionFactory::~TemplateSessionFactory()
{
	if (m_pTempSessionPool) 	delete m_pTempSessionPool;
	if (m_pUserSessionPool) 	delete m_pUserSessionPool;
    if (m_pLoginSessionPool) 	delete m_pLoginSessionPool;
	if (m_pAgentSessionPool) 	delete m_pAgentSessionPool;
	if (m_pLobbySessionPool) 	delete m_pLobbySessionPool;
	if (m_pGameSessionPool) 	delete m_pGameSessionPool;
	if (m_pDBSessionPool) 		delete m_pDBSessionPool;
}

void TemplateSessionFactory::Init()
{
    m_pTempSessionPool  = new UtilityMemoryFactory<TemplateTempSession>;
	m_pUserSessionPool  = new UtilityMemoryFactory<TemplateUserSession>;
	m_pLoginSessionPool = new UtilityMemoryFactory<TemplateLoginSession>;
	m_pAgentSessionPool = new UtilityMemoryFactory<TemplateAgentSession>;
	m_pLobbySessionPool = new UtilityMemoryFactory<TemplateLobbySession>;
	m_pGameSessionPool 	= new UtilityMemoryFactory<TemplateGameSession>;
	m_pDBSessionPool 	= new UtilityMemoryFactory<TemplateDBSession>;
	
	m_pTempSessionPool->Initialize(9,1); // 认证服务器；
	m_pUserSessionPool->Initialize(99,1); // 用户；
	m_pLoginSessionPool->Initialize(1,1); // 登录服务器；
	m_pAgentSessionPool->Initialize(1,1); // 代理服务器；
	m_pLobbySessionPool->Initialize(1,1); // 大厅服务器；
	m_pGameSessionPool->Initialize(1,1); // 游戏服务器；
	m_pDBSessionPool->Initialize(1,1); // DB服务器；
}

TemplateTempSession * TemplateSessionFactory::AllocTempSession() {
	if (m_pTempSessionPool) {
		return m_pTempSessionPool->Alloc();
	}
	return NULL;
}
void TemplateSessionFactory::FreeTempSession(TemplateTempSession * pSession) {
	return m_pTempSessionPool->Free(pSession);
}

TemplateUserSession * TemplateSessionFactory::AllocUserSession() {
	if (m_pUserSessionPool) {
		return m_pUserSessionPool->Alloc();
	}
	return NULL;
}
void TemplateSessionFactory::FreeUserSession(TemplateUserSession * pSession) {
	m_pUserSessionPool->Free(pSession);
}

TemplateLoginSession * TemplateSessionFactory::AllocLoginSession() {
	if (m_pLoginSessionPool) {
		return m_pLoginSessionPool->Alloc();
	}
	return NULL;
}
void TemplateSessionFactory::FreeLoginSession(TemplateLoginSession * pSession){
	m_pLoginSessionPool->Free(pSession);
}

TemplateAgentSession * TemplateSessionFactory::AllocAgentSession() {
	if (m_pAgentSessionPool) {
		return m_pAgentSessionPool->Alloc();
	}
	return NULL;
}
void TemplateSessionFactory::FreeAgentSession(TemplateAgentSession * pSession) {
	m_pAgentSessionPool->Free(pSession);
}

TemplateLobbySession * TemplateSessionFactory::AllocLobbySession() {
	if (m_pLobbySessionPool) {
		return m_pLobbySessionPool->Alloc();
	}
	return NULL;
}
void TemplateSessionFactory::FreeLobbySession(TemplateLobbySession * pSession) {
	m_pLobbySessionPool->Free(pSession);
}

TemplateGameSession * TemplateSessionFactory::AllocGameSession() {
	if (m_pGameSessionPool) {
		return m_pGameSessionPool->Alloc();
	}
	return NULL;
}
void TemplateSessionFactory::FreeGameSession(TemplateGameSession * pSession) {
	m_pGameSessionPool->Free(pSession);
}

TemplateDBSession * TemplateSessionFactory::AllocDBSession() {
	if (m_pDBSessionPool) {
		return m_pDBSessionPool->Alloc();
	}
	return NULL;
}
void TemplateSessionFactory::FreeDBSession(TemplateDBSession * pSession) {
	m_pDBSessionPool->Free(pSession);
}

	