#ifndef _CommonPacketHandler_H_
#define _CommonPacketHandler_H_
#include "CommonDefine.h"
#include "CommonServerSession.h"

typedef VOID (*fnHandler)( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize );

class PacketHandler
{
public:
	PacketHandler(void);
	~PacketHandler(void);

public:
	BOOL RegisterHandler();

	BOOL Register_Client();
	BOOL Register_Lobby ();
	BOOL Register_Games ();

	BOOL AddHandler_Client ( WORD category, WORD protocol, fnHandler fnHandler);
	BOOL AddHandler_Lobby  ( WORD category, WORD protocol, fnHandler fnHandler);
	BOOL AddHandler_Games  ( WORD category, WORD protocol, fnHandler fnHandler);

	void ParsePacket_Client( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize );
    void ParsePacket_Lobby ( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize );
    void ParsePacket_Games ( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize );

private:
	struct FUNC_Client   : public BASE_FUNC {
		fnHandler	m_fnHandler;
	};

		struct FUNC_Client   : public BASE_FUNC {
		fnHandler	m_fnHandler;
	};
	
		struct FUNC_Client   : public BASE_FUNC {
		fnHandler	m_fnHandler;
	};
	
		struct FUNC_Client   : public BASE_FUNC {
		fnHandler	m_fnHandler;
	};
	
	struct FUNC_Lobby : public BASE_FUNC {
		fnHandler	m_fnHandler;
	};

	struct FUNC_Games : public BASE_FUNC {
		fnHandler	m_fnHandler;
	};

	FunctionMap	*	m_pFuncMap_Client;
	FunctionMap	*	m_pFuncMap_Lobby;
	FunctionMap	*	m_pFuncMap_Games;
	FunctionMap	*	m_pFuncMap_Client;
	FunctionMap	*	m_pFuncMap_Lobby;
	FunctionMap	*	m_pFuncMap_Games;
};

extern PacketHandler g_PacketHandler;

#endif
