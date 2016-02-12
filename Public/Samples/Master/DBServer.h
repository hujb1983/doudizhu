#ifndef _DBServer_H_
#define _DBServer_H_
#include <TemplateMainServer.h>

class DBServer : public TemplateMainServer
{
public:
	DBServer()
	{
	}
	
	~DBServer()
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

DBServer gDBServer;

#endif

