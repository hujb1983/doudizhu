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

class CDafaultConfig : public TemplateServerConfig
{
public:
	CDafaultConfig()
	{
		
	}
	
	~CDafaultConfig()
	{
		
	}
	
};


int main() 
{ 
	CDafaultConfig _dafaultConfig;
	_dafaultConfig.InitConfig( );
	_dafaultConfig.InitDafaultConfig( "./ServerConfig.ini" );
	_dafaultConfig.Printf( _dafaultConfig.m_ddesc[0] );
	_dafaultConfig.Printf( _dafaultConfig.m_ddesc[1] );
	return 0;
}