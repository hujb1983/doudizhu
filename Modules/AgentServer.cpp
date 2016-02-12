#include "AgentServer.h"

int main() 
{ 
	TemplateSessionFactory::Instance()->Init();
	
	AgentServer server;
	if( !server.Init() ) {
		return -1;
	}
		
	int nShutdown = 1;
	while( nShutdown ) {
		usleep(20);

		if ( !server.Update( 0 ) ) {
			break;
		}
	}

	TemplatePacketHandler::Release();
	// TemplateSessionFactory::Instance();
	return 0;
}