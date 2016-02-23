#include "GameServer.h"

int main(int argc, char ** argv)
{
	TemplateMainServer::InitSessionArray();
	TemplateSessionFactory::Instance()->Init();

	g_pGameServer = new GameServer;
	if( !g_pGameServer->Init() ) {
		return -1;
	}

	int nShutdown = 1;
	while( nShutdown ) {
		usleep(20);
		if ( !g_pGameServer->Update( 0 ) ) {
			break;
		}
	}

	TemplatePacketHandler::Release();
	SAFE_DELETE(g_pGameServer);
	return 0;
}

