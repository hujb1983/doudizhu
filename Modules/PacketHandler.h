#ifndef _PacketHandler_H_
#define _PacketHandler_H_
#include <TemplatePacketHandler.h>
#include <CommonProtocol.h>
#include "Handler_Module.h"
#include "ProtocolServerType.h"
#include "ProtocolGame.h"
#include "ProtocolLogin.h"
#include "ProtocolUpdate.h"

class PacketHandler : public TemplatePacketHandler
{
public:
	PacketHandler();
	~PacketHandler();

public:
	BOOL Register_Client();
	BOOL Register_Login();
	BOOL Register_Agent();
	BOOL Register_Lobby();
	BOOL Register_Games();
	BOOL Register_DB();
};

#endif
