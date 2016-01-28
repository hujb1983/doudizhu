#ifndef _TemplateServerConfig_H_
#define _TemplateServerConfig_H_
#include "TemplateInclude.h"

class TemplateServerConfig
{
public:
	TemplateServerConfig();
	virtual ~TemplateServerConfig();

public:
	void SetServerType( BYTE byServerType );
	void LoadConfig( const char * szConfig );
	
private://本地服务器类型配置
	void LoadLocalServer( const char * szServerTypeName, UtilityIni & ini );
	void LoadConnectObjects( const char * szServerTypeName, UtilityIni & ini );
	
private:
	BYTE byServerType;
	BYTE byServerHandler;
	BYTE byClientHandler;
	
private://配置需要连接的服务器群
	TemplateLoginSession * pLoginSession;
	TemplateAgentSession * pAgentSession;
	TemplateLobbySession * pLobbySession;
	TemplateGameSession * pGameSession;
	TemplateDBSession * pDBSession;
};

#endif // _AGENTPLAYER_H_INCLUDED_
