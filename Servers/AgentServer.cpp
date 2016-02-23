#include "AgentServer.h"

int main(int argc, char ** argv) 
{ 
	TemplateMainServer::InitSessionArray();
	TemplateSessionFactory::Instance()->Init();
	
	g_pAgentServer = new AgentServer;
	if( !g_pAgentServer->Init() ) {
		return -1;
	}
		
	int nShutdown = 1;
	while( nShutdown ) {
		usleep(20);

		if ( !g_pAgentServer->Update( 0 ) ) {
			break;
		}
	}

	TemplatePacketHandler::Release();
	SAFE_DELETE(g_pAgentServer);
	
	return 0;
}