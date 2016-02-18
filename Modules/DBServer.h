#ifndef _DBServer_H_
#define _DBServer_H_
#include <TemplateSeasoning.h>
#include <TemplateSessionFactory.h>
#include <TemplatePacketHandler.h>
#include <TemplateMainServer.h>
#include "PacketHandler.h"


class DBServer : public TemplateMainServer
{
public:
	DBServer()
	{
	}

	~DBServer()
	{
	}

	virtual BOOL Init()
	{
		printf( "DBServer Init! \n");

		InitConfig( );
		InitDafaultConfig( "./ServerConfig.ini" );

		SetServerType(DB_SERVER);
		LoadServerConfig( "./ServerConfig.ini" );
		LoadCompleteServerConfig();

		TemplateSeasoning system;
		system.GetOpenDatabase() = TRUE;

		if ( !TemplateMainServer::Init() ) {
			return FALSE;
		}

		// Initialize the PacketHandler;
        TemplatePacketHandler::Init();
		PacketHandler handler;

		return TRUE;
	}
};

extern DBServer * g_pDBServer;

#endif

