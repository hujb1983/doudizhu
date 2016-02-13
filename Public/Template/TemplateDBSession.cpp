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
    TemplatePacketHandler::ParsePacket_DB( pid, this, (MSG_BASE*)pMsg, wSize );
}

void TemplateDBSession::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{
	DEBUG_MSG( LVL_DEBUG, "TemplateDBSession::OnConnect. \n");
	TemplateServerSession::OnConnect( bSuccess, dwNetworkIndex );

	if ( bSuccess )
    {
		DEBUG_MSG( LVL_DEBUG, "TemplateDBSession::OnConnect success. \n");
		TemplateServerSession::SendServerType();
		return;
	}

    DEBUG_MSG( LVL_DEBUG, "TemplateDBSession::OnConnect fail. \n");
}

void TemplateDBSession::OnDisconnect()
{
    DEBUG_MSG( LVL_DEBUG, "TemplateDBSession::OnDisconnect. \n");
    TemplateServerSession::OnDisconnect();
}

void TemplateDBSession::OnLogString( char * pszLog)
{

}
