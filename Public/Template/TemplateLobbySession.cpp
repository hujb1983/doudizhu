#include "TemplateInclude.h"
#include "TemplatePacket.h"
#include "TemplatePacketHandler.h"

TemplateLobbySession::TemplateLobbySession()
{
}

TemplateLobbySession::~TemplateLobbySession()
{

}

void TemplateLobbySession::Clear()
{

}

void TemplateLobbySession::OnRecv( BYTE *pMsg, WORD wSize )
{
	int pid = 0;
    if ( wSize>=sizeof(TemplatePacket) )
    {
        TemplatePacket * packet = (TemplatePacket *) pMsg;
        pid = packet->GetProtocol();
        DEBUG_MSG( LVL_TRACE, "DB_PID:%d", pid);
    }
		
	if (pid!=0) {
		TemplatePacketHandler::ParsePacket_Lobby( pid, this, (MSG_BASE*)pMsg, wSize );
	}
}

void TemplateLobbySession::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{
	DEBUG_MSG( LVL_DEBUG, "TemplateLobbySession::OnConnect.");
	TemplateServerSession::OnConnect( bSuccess, dwNetworkIndex );

	if ( bSuccess )
    {
		DEBUG_MSG( LVL_DEBUG, "TemplateLobbySession::OnConnect success.");
		TemplateServerSession::SendServerType();
		return;
	}

    DEBUG_MSG( LVL_DEBUG, "TemplateLobbySession::OnConnect fail.");
}

void TemplateLobbySession::OnDisconnect()
{
    DEBUG_MSG( LVL_DEBUG, "TemplateLobbySession::OnDisconnect.");
    TemplateServerSession::OnDisconnect();
}

void TemplateLobbySession::OnLogString( char * pszLog)
{

}
