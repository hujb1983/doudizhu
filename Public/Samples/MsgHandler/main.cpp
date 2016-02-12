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
#include "AgentServer.h"

int main() 
{ 
	if( !server.Init() ) {
		return 0;
	}
	
	TemplatePacketHandler::Init();
	PacketHandlerServer packet;

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