#ifndef _GameServer_H_
#define _GameServer_H_
#include <TemplateMainServer.h>

class GameServer : public TemplateMainServer
{
public:
	GameServer()
	{
	}
	
	~GameServer()
	{
	}
	
	BOOL Init()
	{
		InitConfig( );
		InitDafaultConfig( "./ServerConfig.ini" );
		
		SetServerType(AGENT_SERVER);
		LoadServerConfig( "./ServerConfig.ini" );
		
		LoadCompleteServerConfig();
		if ( TemplateMainServer::Init() ) {
			return TRUE;
		}
		return FALSE;
	}
};

GameServer gGameServer;

#endif

