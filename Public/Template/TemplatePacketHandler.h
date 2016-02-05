#ifndef _TemplatePacketHandler_H_
#define _TemplatePacketHandler_H_
#include <CommonInclude.h>
#include "TemplateServerSession.h"

typedef VOID (*fnHandler)( TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize );

class TemplatePacketHandler
{
public:
	TemplatePacketHandler(void);
	~TemplatePacketHandler(void);

public:
    static BOOL Init();
    static BOOL Release();

	virtual BOOL Register_Client();
	virtual BOOL Register_Login ();
	virtual BOOL Register_Agent ();
	virtual BOOL Register_Lobby ();
	virtual BOOL Register_Games ();
	virtual BOOL Register_DB    ();

	BOOL AddHandler_Client ( WORD category, WORD protocol, fnHandler fnHandler);
	BOOL AddHandler_Login  ( WORD category, WORD protocol, fnHandler fnHandler);
	BOOL AddHandler_Agent  ( WORD category, WORD protocol, fnHandler fnHandler);
	BOOL AddHandler_Lobby  ( WORD category, WORD protocol, fnHandler fnHandler);
	BOOL AddHandler_Games  ( WORD category, WORD protocol, fnHandler fnHandler);
	BOOL AddHandler_DB     ( WORD category, WORD protocol, fnHandler fnHandler);

	static void ParsePacket_Client( DWORD dwProtocol, TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize );
    static void ParsePacket_Login ( DWORD dwProtocol, TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize );
    static void ParsePacket_Agent ( DWORD dwProtocol, TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize );
	static void ParsePacket_Lobby ( DWORD dwProtocol, TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize );
    static void ParsePacket_Games ( DWORD dwProtocol, TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize );
    static void ParsePacket_DB    ( DWORD dwProtocol, TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize );

private:
	struct FUNC_Client   : public BASE_FUNC {
		fnHandler	m_fnHandler;
	};

	struct FUNC_Login   : public BASE_FUNC {
		fnHandler	m_fnHandler;
	};

	struct FUNC_Agent   : public BASE_FUNC {
		fnHandler	m_fnHandler;
	};

	struct FUNC_Lobby   : public BASE_FUNC {
		fnHandler	m_fnHandler;
	};

	struct FUNC_Games : public BASE_FUNC {
		fnHandler	m_fnHandler;
	};

	struct FUNC_DB : public BASE_FUNC {
		fnHandler	m_fnHandler;
	};

	static UtilityFunctionMap * m_pFuncMap_Client;
	static UtilityFunctionMap * m_pFuncMap_Login;
	static UtilityFunctionMap * m_pFuncMap_Agent;
	static UtilityFunctionMap * m_pFuncMap_Lobby;
	static UtilityFunctionMap * m_pFuncMap_Games;
	static UtilityFunctionMap * m_pFuncMap_DB;
};

#endif
