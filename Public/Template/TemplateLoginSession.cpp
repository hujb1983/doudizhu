#include "TemplateInclude.h"
#include "TemplatePacket.h"
#include "TemplatePacketHandler.h"

TemplateLoginSession::TemplateLoginSession()
{
}

TemplateLoginSession::~TemplateLoginSession()
{

}

void TemplateLoginSession::Clear()
{

}

void TemplateLoginSession::OnRecv( BYTE *pMsg, WORD wSize )
{
    int pid = 0;
    if ( wSize>=sizeof(TemplatePacket) )
    {
        TemplatePacket * packet = (TemplatePacket *) pMsg;
        pid = packet->GetProtocol();
        DEBUG_MSG( LVL_TRACE, "Login_PID:%d", pid);
	}
	
	if (pid!=0) {
		TemplatePacketHandler::ParsePacket_Login( pid, this, (MSG_BASE*)pMsg, wSize );
	}
}

void TemplateLoginSession::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{
	DEBUG_MSG( LVL_DEBUG, "TemplateLoginSession::OnConnect.");
	TemplateServerSession::OnConnect( bSuccess, dwNetworkIndex );

	if ( bSuccess )
    {
		DEBUG_MSG( LVL_DEBUG, "TemplateLoginSession::OnConnect success.");
		TemplateServerSession::SendServerType();
		return;
	}

    DEBUG_MSG( LVL_DEBUG, "TemplateLoginSession::OnConnect fail.");
}

void TemplateLoginSession::OnDisconnect()
{
    DEBUG_MSG( LVL_DEBUG, "TemplateLoginSession::OnDisconnect.");
    TemplateServerSession::OnDisconnect();
}

void TemplateLoginSession::OnLogString( char * pszLog)
{

}
