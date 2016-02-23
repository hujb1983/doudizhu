#include "LobbyServer.h"

int main(int argc, char ** argv)
{
	TemplateMainServer::InitSessionArray();
	TemplateSessionFactory::Instance()->Init();

	g_pLobbyServer = new LobbyServer;
	if( !g_pLobbyServer->Init() ) {
		return -1;
	}

	DWORD dwTicket = 0;
	int nShutdown = 1;
	while( nShutdown ) {
		usleep(20);

        dwTicket = UtilityTimer::GetTickCount();
		if ( !g_pLobbyServer->Update( dwTicket ) ) {
			break;
		}
	}

	TemplatePacketHandler::Release();
	SAFE_DELETE(g_pLobbyServer);
	return 0;
}

