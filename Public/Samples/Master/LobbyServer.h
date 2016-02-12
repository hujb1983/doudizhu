#ifndef _LobbyServer_H_
#define _LobbyServer_H_
#include <TemplateMainServer.h>

class LobbyServer : public TemplateMainServer
{
public:
	LobbyServer()
	{
	}
	
	~LobbyServer()
	{
	}
	
	virtual BOOL Init()
	{
		printf( "LobbyServer Init! \n");
		
		InitConfig();
		InitDafaultConfig( "./ServerConfig.ini" );
		
		SetServerType(LOBBY_SERVER);
		LoadServerConfig( "./ServerConfig.ini" );
		
		LoadCompleteServerConfig();
		
		Printf(m_desc[0]);
		Printf(m_desc[1]);
		
		if ( TemplateMainServer::Init() ) {
			return TRUE;
		}
		
		return FALSE;
	}
	
};

#endif

