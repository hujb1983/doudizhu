#include <UtilityDefine.h>
#include <UtilitySingleton.h>
#include <UtilityMemoryFactory.h>
#include <UtilitySolarHashTable.h>
#include <UtilitySingleListT.h>
#include <UtilityDoubleListT.h>
#include <UtilityLinkedList.h>
#include <UtilityFunctionMap.h>
#include <UtilityCircuitQueue.h>
#include <TemplateMainServer.h>
#include <TemplatePacketHandler.h>
#include <TemplateServerConfig.h>
#include <TemplateSessionFactory.h>

class AgentServer : public TemplateMainServer
{
public:
	AgentServer()
	{
		
	}
	
	~AgentServer()
	{
		
	}
	
	BOOL Init()
	{
		InitConfig( );
		InitDafaultConfig( "./ServerConfig.ini" );
		
		SetServerType(AGENT_SERVER);
		LoadServerConfig( "./ServerConfig.ini" );
		
		LoadCompleteServerConfig();
		if ( TemplateMainServer::Init() ) {
			return TRUE;
		}
		return FALSE;
	}
};

AgentServer server;


int main() 
{ 
	TemplateSessionFactory::Instance()->Init();
	
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
	
	return 0;
}
