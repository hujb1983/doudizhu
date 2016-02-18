#include "TemplateInclude.h"
#include "TemplatePacket.h"
#include "TemplatePacketHandler.h"

TemplateDBSession::TemplateDBSession()
{
}

TemplateDBSession::~TemplateDBSession()
{

}

void TemplateDBSession::Clear()
{

}

void TemplateDBSession::OnRecv( BYTE *pMsg, WORD wSize )
{
    int pid = 0;
    if ( wSize>=sizeof(TemplatePacket) )
    {
        TemplatePacket * packet = (TemplatePacket *) pMsg;
        pid = packet->GetProtocol();
        DEBUG_MSG( LVL_TRACE, "DB_PID:%d", pid);
    }
		
	if (pid!=0) {
		TemplatePacketHandler::ParsePacket_DB( pid, this, (MSG_BASE*)pMsg, wSize );
	}
}

void TemplateDBSession::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{
	DEBUG_MSG( LVL_DEBUG, "TemplateDBSession::OnConnect.");
	TemplateServerSession::OnConnect( bSuccess, dwNetworkIndex );

	if ( bSuccess )
    {
		DEBUG_MSG( LVL_DEBUG, "TemplateDBSession::OnConnect success.");
		TemplateServerSession::SendServerType();
		return;
	}

    DEBUG_MSG( LVL_DEBUG, "TemplateDBSession::OnConnect fail.");
}

void TemplateDBSession::OnDisconnect()
{
    DEBUG_MSG( LVL_DEBUG, "TemplateDBSession::OnDisconnect.");
    TemplateServerSession::OnDisconnect();
}

void TemplateDBSession::OnLogString( char * pszLog)
{

}
