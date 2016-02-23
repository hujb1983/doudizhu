#ifndef _LoginServer_H_
#define _LoginServer_H_
#include <TemplateSeasoning.h>
#include <TemplateSessionFactory.h>
#include <TemplatePacketHandler.h>
#include <TemplateMainServer.h>
#include "PacketHandler.h"

class LoginServer : public TemplateMainServer
{
public:
	LoginServer()
	{
	}

	~LoginServer()
	{
	}

	virtual BOOL Init()
	{
		printf( "LoginServer::Init! \n");

		InitConfig( );
		InitDafaultConfig( "./ServerConfig.ini" );

		SetServerType(LOGIN_SERVER);
		LoadServerConfig( "./ServerConfig.ini" );
		LoadCompleteServerConfig();

		printf( "LoginServer Init! \n");
		TemplateSeasoning system;
		system.GetClientSendHead() = FALSE;
		system.GetClientRecvHead() = FALSE;
		system.GetOpenDatabase()   = FALSE;

		if ( !TemplateMainServer::Init() ) {
			return FALSE;
		}

		// Initialize the PacketHandler;
		TemplatePacketHandler::Init();
		PacketHandler handler;
		return TRUE;
	}
};

extern LoginServer * g_pLoginServer;

#endif

