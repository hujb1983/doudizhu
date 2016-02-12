#ifndef _GameServer_H_
#define _GameServer_H_
#include <TemplateSessionFactory.h>
#include <TemplatePacketHandler.h>
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
	
	virtual BOOL Init()
	{
		printf( "GameServer Init! \n");

		InitConfig( );
		InitDafaultConfig( "./ServerConfig.ini" );

		SetServerType(AGENT_SERVER);
		LoadServerConfig( "./ServerConfig.ini" );
		LoadCompleteServerConfig();
		
		Printf(m_desc[0]);
		Printf(m_desc[1]);
		
		printf( "GameServer Init! \n");
		
		if ( TemplateMainServer::Init() ) {
			return TRUE;
		}
		
		return FALSE;
	}
};


#endif

