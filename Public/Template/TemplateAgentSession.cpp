#include "TemplateInclude.h"
#include "TemplatePacket.h"
#include "TemplatePacketHandler.h"

TemplateAgentSession::TemplateAgentSession()
{
}

TemplateAgentSession::~TemplateAgentSession()
{

}

void TemplateAgentSession::Clear()
{

}

void TemplateAgentSession::OnRecv( BYTE *pMsg, WORD wSize )
{
    int pid = 0;
    if ( wSize>=sizeof(TemplatePacket) )
    {
        TemplatePacket * packet = (TemplatePacket *) pMsg;
        pid = packet->GetProtocol();
        DEBUG_MSG( LVL_TRACE, "Agent_PID:%d", pid);
    }
	
	if (pid!=0) 
	{
		TemplatePacketHandler::ParsePacket_Agent( pid, this, (MSG_BASE*)pMsg, wSize );
	}
}

void TemplateAgentSession::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{
	DEBUG_MSG( LVL_DEBUG, "TemplateAgentSession::OnConnect.");
	TemplateServerSession::OnConnect( bSuccess, dwNetworkIndex );

	if ( bSuccess )
    {
		DEBUG_MSG( LVL_DEBUG, "TemplateAgentSession::OnConnect success.");
		TemplateServerSession::SendServerType();
		return;
	}

    DEBUG_MSG( LVL_DEBUG, "TemplateAgentSession::OnConnect fail.");
}

void TemplateAgentSession::OnDisconnect()
{
    DEBUG_MSG( LVL_DEBUG, "TemplateAgentSession::OnDisconnect.");
    TemplateServerSession::OnDisconnect();
}

void TemplateAgentSession::OnLogString( char * pszLog)
{

}
