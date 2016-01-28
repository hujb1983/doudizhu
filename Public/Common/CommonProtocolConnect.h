#ifndef _CommonProtocolConnect_H_
#define _CommonProtocolConnect_H_
#include "CommonProtocol.h"

/***** Client -> Login *****/
enum eCONNECT_PROTOCOL
{
	ClientType_SYN		= 100,
	ClientType_ANC		= 101,
	ServerType_SYN 		= 200,
	ServerType_ANC		= 201 ,
	Heartbeat_SYN		= 300,
	Heartbeat_ANC		= 301,
};

#endif // _CommonProtocol_H_