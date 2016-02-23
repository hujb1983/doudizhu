#include "LoginServer.h"


int main(int argc, char ** argv)
{
    TemplateMainServer::InitSessionArray();
	TemplateSessionFactory::Instance()->Init();

	g_pLoginServer = new LoginServer;
	if( !g_pLoginServer->Init() ) {
		return -1;
	}

	int nShutdown = 1;
	while( nShutdown ) {
		usleep(20);

		if ( !g_pLoginServer->Update( 0 ) ) {
			break;
		}
	}

	TemplatePacketHandler::Release();
	SAFE_DELETE(g_pLoginServer);
	return 0;
}

