#include "LobbyServer.h"

int main(int argc, char ** argv)
{
	TemplateMainServer::InitSessionArray();
	TemplateSessionFactory::Instance()->Init();
	
	g_pLobbyServer = new LobbyServer;
	if( !g_pLobbyServer->Init() ) {
		return -1;
	}

	int nShutdown = 1;
	while( nShutdown ) {
		usleep(20);

		if ( !g_pLobbyServer->Update( 0 ) ) {
			break;
		}
	}

	TemplatePacketHandler::Release();
	SAFE_DELETE(g_pLobbyServer);
	return 0;
}

