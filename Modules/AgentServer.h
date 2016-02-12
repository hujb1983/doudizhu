#ifndef _AgentServer_H_
#define _AgentServer_H_
#include <TemplateSessionFactory.h>
#include <TemplatePacketHandler.h>
#include <TemplateMainServer.h>

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
		
		Printf(m_desc[0]);
		Printf(m_desc[1]);
		
		printf( "AgentServer Init! \n");
		
		if ( TemplateMainServer::Init() ) {
			return TRUE;
		}
		
		return FALSE;
	}
};


#endif

