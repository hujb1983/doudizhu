#include "TemplateInclude.h"

TemplateAgentSession::TemplateAgentSession()
{
}

TemplateAgentSession::~TemplateAgentSession()
{

}

void TemplateAgentSession::Clear()
{

}

void TemplateAgentSession::OnRecv( BYTE *pMsg, WORD wSize ) {

}

void TemplateAgentSession::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{
	DEBUG_MSG( LVL_DEBUG, "TemplateAgentSession::OnConnect. \n");
	TemplateServerSession::OnConnect( bSuccess, dwNetworkIndex );

	if ( bSuccess )
    {
		DEBUG_MSG( LVL_DEBUG, "TemplateAgentSession::OnConnect success. \n");
		TemplateServerSession::SendServerType();
		return;
	}

    DEBUG_MSG( LVL_DEBUG, "TemplateAgentSession::OnConnect fail. \n");
}

void TemplateAgentSession::OnDisconnect()
{
    DEBUG_MSG( LVL_DEBUG, "TemplateAgentSession::OnDisconnect. \n");
    TemplateServerSession::OnDisconnect();
}

void TemplateAgentSession::OnLogString( char * pszLog)
{

}
