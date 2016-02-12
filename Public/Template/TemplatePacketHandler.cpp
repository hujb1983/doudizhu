#include "TemplatePacketHandler.h"


UtilityFunctionMap * TemplatePacketHandler::m_pFuncMap_Client = NULL;
UtilityFunctionMap * TemplatePacketHandler::m_pFuncMap_Login  = NULL;
UtilityFunctionMap * TemplatePacketHandler::m_pFuncMap_Agent  = NULL;
UtilityFunctionMap * TemplatePacketHandler::m_pFuncMap_Lobby  = NULL;
UtilityFunctionMap * TemplatePacketHandler::m_pFuncMap_Games  = NULL;
UtilityFunctionMap * TemplatePacketHandler::m_pFuncMap_DB     = NULL;


TemplatePacketHandler::TemplatePacketHandler(void)
{
}

TemplatePacketHandler::~TemplatePacketHandler(void)
{
}

BOOL TemplatePacketHandler::Init()
{
	if ( !TemplatePacketHandler::m_pFuncMap_Client )
    {
        TemplatePacketHandler::m_pFuncMap_Client = new UtilityFunctionMap;
        TemplatePacketHandler::m_pFuncMap_Login  = new UtilityFunctionMap;
        TemplatePacketHandler::m_pFuncMap_Agent  = new UtilityFunctionMap;
        TemplatePacketHandler::m_pFuncMap_Lobby  = new UtilityFunctionMap;
        TemplatePacketHandler::m_pFuncMap_Lobby  = new UtilityFunctionMap;
        TemplatePacketHandler::m_pFuncMap_Games  = new UtilityFunctionMap;
        TemplatePacketHandler::m_pFuncMap_DB     = new UtilityFunctionMap;
	}
}

BOOL TemplatePacketHandler::Release()
{
    SAFE_DELETE( TemplatePacketHandler::m_pFuncMap_Client);
	SAFE_DELETE( TemplatePacketHandler::m_pFuncMap_Login );
	SAFE_DELETE( TemplatePacketHandler::m_pFuncMap_Agent );
	SAFE_DELETE( TemplatePacketHandler::m_pFuncMap_Lobby );
	SAFE_DELETE( TemplatePacketHandler::m_pFuncMap_Games );
	SAFE_DELETE( TemplatePacketHandler::m_pFuncMap_DB    );
}

BOOL TemplatePacketHandler::Register_Client()
{
}

BOOL TemplatePacketHandler::Register_Login()
{
}

BOOL TemplatePacketHandler::Register_Agent()
{
}

BOOL TemplatePacketHandler::Register_Lobby()
{
}

BOOL TemplatePacketHandler::Register_Games()
{
}

BOOL TemplatePacketHandler::Register_DB()
{

}

BOOL TemplatePacketHandler::AddHandler_Client ( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_Client * pFuncInfo = new FUNC_Client;
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	return TemplatePacketHandler::m_pFuncMap_Client->Add( pFuncInfo );
}

BOOL TemplatePacketHandler::AddHandler_Login ( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_Login * pFuncInfo = new FUNC_Login;
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	return TemplatePacketHandler::m_pFuncMap_Login->Add( pFuncInfo );
}

BOOL TemplatePacketHandler::AddHandler_Agent ( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_Agent * pFuncInfo = new FUNC_Agent;
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	return TemplatePacketHandler::m_pFuncMap_Agent->Add( pFuncInfo );
}

BOOL TemplatePacketHandler::AddHandler_Lobby ( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_Lobby * pFuncInfo = new FUNC_Lobby;
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	return TemplatePacketHandler::m_pFuncMap_Lobby->Add( pFuncInfo );
}

BOOL TemplatePacketHandler::AddHandler_Games ( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_Games * pFuncInfo = new FUNC_Games;
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	return TemplatePacketHandler::m_pFuncMap_Games->Add( pFuncInfo );
}

BOOL TemplatePacketHandler::AddHandler_DB ( WORD category, WORD protocol, fnHandler fnHandler)
{
	FUNC_DB * pFuncInfo = new FUNC_DB;
	pFuncInfo->m_dwFunctionKey	= MAKELONG( category, protocol );
	pFuncInfo->m_fnHandler		= fnHandler;
	return TemplatePacketHandler::m_pFuncMap_DB->Add( pFuncInfo );
}

void TemplatePacketHandler::ParsePacket_Client ( DWORD dwProtocol, TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
	FUNC_Client * pFuncInfo = (FUNC_Client *)TemplatePacketHandler::m_pFuncMap_Client->Find( dwProtocol );
	if (pFuncInfo) {
		pFuncInfo->m_fnHandler( pServerSession, pMsg, wSize );
	}
}

void TemplatePacketHandler::ParsePacket_Login ( DWORD dwProtocol, TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
	assert(NULL != pMsg);
	FUNC_Login * pFuncInfo = (FUNC_Login *)TemplatePacketHandler::m_pFuncMap_Login->Find( dwProtocol );
	if (pFuncInfo) {
		pFuncInfo->m_fnHandler( pServerSession, pMsg, wSize );
	}
}

void TemplatePacketHandler::ParsePacket_Agent ( DWORD dwProtocol, TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
	assert(NULL != pMsg);
	FUNC_Agent * pFuncInfo = (FUNC_Agent *)TemplatePacketHandler::m_pFuncMap_Agent->Find( dwProtocol );
	if (pFuncInfo) {
		pFuncInfo->m_fnHandler( pServerSession, pMsg, wSize );
	}
}

void TemplatePacketHandler::ParsePacket_Lobby ( DWORD dwProtocol, TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
	assert(NULL != pMsg);
	FUNC_Lobby * pFuncInfo = (FUNC_Lobby *)TemplatePacketHandler::m_pFuncMap_Lobby->Find( dwProtocol );
	if (pFuncInfo) {
		pFuncInfo->m_fnHandler( pServerSession, pMsg, wSize );
	}
}

void TemplatePacketHandler::ParsePacket_Games ( DWORD dwProtocol, TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
	assert(NULL != pMsg);
	FUNC_Games * pFuncInfo = (FUNC_Games *)TemplatePacketHandler::m_pFuncMap_Games->Find( dwProtocol );
	if (pFuncInfo) {
		pFuncInfo->m_fnHandler( pServerSession, pMsg, wSize );
	}
}

void TemplatePacketHandler::ParsePacket_DB ( DWORD dwProtocol, TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
	assert(NULL != pMsg);
	FUNC_DB * pFuncInfo = (FUNC_DB *)TemplatePacketHandler::m_pFuncMap_DB->Find( dwProtocol );
	if (pFuncInfo) {
		pFuncInfo->m_fnHandler( pServerSession, pMsg, wSize );
	}
}
