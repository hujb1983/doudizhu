#ifndef _AgentServer_H_
#define _AgentServer_H_
#include <TemplateSeasoning.h>
#include <TemplateSessionFactory.h>
#include <TemplatePacketHandler.h>
#include <TemplateMainServer.h>
#include "PacketHandler.h"

class AgentServer : public TemplateMainServer
{
public:
	AgentServer()
	{
	}

	~AgentServer()
	{
	}

	virtual BOOL Init()
	{
		printf( "AgentServer Init! \n");

		InitConfig( );
		InitDafaultConfig( "./ServerConfig.ini" );

		SetServerType(AGENT_SERVER);
		LoadServerConfig( "./ServerConfig.ini" );
		LoadCompleteServerConfig();

		TemplateSeasoning system;
		system.GetClientSendHead() = TRUE;
		system.GetClientRecvHead() = FALSE;

		printf( "AgentServer Init! \n");
		if ( !TemplateMainServer::Init() ) {
			return FALSE;
		}

		// Initialize the PacketHandler;
		TemplatePacketHandler::Init();
		PacketHandler handler;

		return TRUE;
	}
};

extern AgentServer * g_pAgentServer;

#endif

