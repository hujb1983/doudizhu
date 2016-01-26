#ifndef _TemplateSessionFactory_H_
#define _TemplateSessionFactory_H_
#include <CommonInclude.h>
#include "TemplateInclude.h"

class TemplateSessionFactory : public UtilitySingleton<TemplateSessionFactory>
{
public:
	TemplateSessionFactory();
	~TemplateSessionFactory();

private:
	UtilityMemoryFactory<TemplateTempSession> 	* m_pTempSessionPool;
	UtilityMemoryFactory<TemplateUserSession> 	* m_pUserSessionPool;
	UtilityMemoryFactory<TemplateLoginSession> 	* m_pLoginSessionPool;
	UtilityMemoryFactory<TemplateAgentSession> 	* m_pAgentSessionPool;
	UtilityMemoryFactory<TemplateLobbySession> 	* m_pLobbySessionPool;
	UtilityMemoryFactory<TemplateGameSession>	* m_pGameSessionPool;
	UtilityMemoryFactory<TemplateDBSession>		* m_pDBSessionPool;

public:
	void Init(void);
	void Release(void);

	TemplateTempSession * AllocTempSession();
	void FreeTempSession(TemplateTempSession * pSession);
	
	TemplateUserSession * AllocUserSession();
	void FreeUserSession(TemplateUserSession * pSession);

	TemplateLoginSession * AllocLoginSession();
	void FreeLoginSession(TemplateLoginSession * pSession);

	TemplateAgentSession * AllocAgentSession();
	void FreeAgentSession(TemplateAgentSession * pSession);
	
	TemplateLobbySession * AllocLobbySession();
	void FreeLobbySession(TemplateLobbySession * pSession);
	
	TemplateGameSession * AllocGameSession();
	void FreeGameSession(TemplateGameSession * pSession);
	
	TemplateDBSession * AllocDBSession();
	void FreeDBSession(TemplateDBSession * pSession);
};

#endif
