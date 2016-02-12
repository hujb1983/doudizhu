
#ifndef _AgentServer_H_
#define _AgentServer_H_

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



void MSG_Test( TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
	DEBUG_MSG( LVL_DEBUG, "MSG_Test!");	
}

class PacketHandlerServer : public TemplatePacketHandler
{
public:
	PacketHandlerServer()
	{
		Register_Client();
	}
	
	~PacketHandlerServer()
	{
	}
	
	BOOL Register_Client()
	{
		AddHandler_Client( 700, 100, MSG_Test );
		AddHandler_Client( 700, 101, MSG_Test );
		AddHandler_Client( 700, 102, MSG_Test );	
		AddHandler_Client( 700, 103, MSG_Test );	
	}
};

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
		return TemplateMainServer::Init();
	}
};

AgentServer server;

#endif

