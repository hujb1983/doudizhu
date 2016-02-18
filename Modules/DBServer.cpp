#include "DBServer.h"

int main(int argc, char ** argv)
{
	TemplateMainServer::InitSessionArray();
	TemplateSessionFactory::Instance()->Init();

	g_pDBServer = new DBServer;
	if( !g_pDBServer->Init() ) {
		return -1;
	}

	int nShutdown = 1;
	while( nShutdown ) {
		usleep(20);

		if ( !g_pDBServer->Update( 0 ) ) {
			break;
		}
	}

	TemplatePacketHandler::Release();
	SAFE_DELETE(g_pDBServer);
	return 0;
}

