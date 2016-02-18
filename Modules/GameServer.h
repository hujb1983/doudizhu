#ifndef _GameServer_H_
#define _GameServer_H_
#include <TemplateSeasoning.h>
#include <TemplateSessionFactory.h>
#include <TemplatePacketHandler.h>
#include <TemplateMainServer.h>
#include "PacketHandler.h"

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

		SetServerType(GAME_SERVER);
		LoadServerConfig( "./ServerConfig.ini" );
		LoadCompleteServerConfig();

		printf( "GameServer Init! \n");
		if ( TemplateMainServer::Init() ) {
			return FALSE;
		}

		// Initialize the PacketHandler;
        TemplatePacketHandler::Init();
		PacketHandler handler;

		return TRUE;
	}
};

extern GameServer * g_pGameServer;

#endif

