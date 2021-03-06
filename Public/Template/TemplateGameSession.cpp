#include "TemplateInclude.h"
#include "TemplatePacket.h"
#include "TemplatePacketHandler.h"

TemplateGameSession::TemplateGameSession()
{
}

TemplateGameSession::~TemplateGameSession()
{

}

void TemplateGameSession::Clear()
{

}

void TemplateGameSession::OnRecv( BYTE *pMsg, WORD wSize )
{
    int pid = 0;
    if ( wSize>=sizeof(TemplatePacket) )
    {
        TemplatePacket * packet = (TemplatePacket *) pMsg;
        pid = packet->GetProtocol();
        DEBUG_MSG( LVL_TRACE, "Games_PID:%d", pid);
    }
	
	if (pid!=0) 
	{
		TemplatePacketHandler::ParsePacket_Games( pid, this, (MSG_BASE*)pMsg, wSize );
	}
}

void TemplateGameSession::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{
	DEBUG_MSG( LVL_DEBUG, "TemplateGameSession::OnConnect.");
	TemplateServerSession::OnConnect( bSuccess, dwNetworkIndex );

	if ( bSuccess )
    {
		DEBUG_MSG( LVL_DEBUG, "TemplateGameSession::OnConnect success.");
		TemplateServerSession::SendServerType();
		return;
	}

    DEBUG_MSG( LVL_DEBUG, "TemplateGameSession::OnConnect fail.");
}

void TemplateGameSession::OnDisconnect()
{
    DEBUG_MSG( LVL_DEBUG, "TemplateGameSession::OnDisconnect.");
    TemplateServerSession::OnDisconnect();
}

void TemplateGameSession::OnLogString( char * pszLog)
{

}
