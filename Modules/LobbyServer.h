#ifndef _LobbyServer_H_
#define _LobbyServer_H_
#include <TemplateSeasoning.h>
#include <TemplateSessionFactory.h>
#include <TemplatePacketHandler.h>
#include <TemplateMainServer.h>
#include "PacketHandler.h"

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

		InitConfig( );
		InitDafaultConfig( "./ServerConfig.ini" );

		SetServerType(LOBBY_SERVER);
		LoadServerConfig( "./ServerConfig.ini" );
		LoadCompleteServerConfig();

		printf( "LobbyServer Init! \n");
		if ( !TemplateMainServer::Init() ) {
			return FALSE;
		}

		// Initialize the PacketHandler;
        TemplatePacketHandler::Init();
		PacketHandler handler;

		return TRUE;
	}
};

extern LobbyServer * g_pLobbyServer;

#endif

