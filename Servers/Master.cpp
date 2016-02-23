#ifndef _LoginServer_H_
#define _LoginServer_H_
#include <TemplateMainServer.h>

class LoginServer : public TemplateMainServer
{
public:
	LoginServer()
	{
	}
	
	~LoginServer()
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

#endif

