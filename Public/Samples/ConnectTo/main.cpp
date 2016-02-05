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
		Printf( m_ddesc[0] );
		Printf( m_ddesc[1] );
		
		SetServerType(AGENT_SERVER);
		LoadServerConfig( "./ServerConfig.ini" );
		Printf( m_desc[0] );
		Printf( m_desc[1] );
		return TRUE;
	}
};

AgentServer server;

int main() 
{ 
	TemplateSessionFactory::Instance()->Init();
	
	if( !server.Init() ) {
		return -1;
	}
	
	
	return 0;
}