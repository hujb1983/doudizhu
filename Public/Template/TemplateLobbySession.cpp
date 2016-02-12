#include "TemplateInclude.h"

TemplateLobbySession::TemplateLobbySession()
{
}

TemplateLobbySession::~TemplateLobbySession()
{

}

void TemplateLobbySession::Clear()
{

}

void TemplateLobbySession::OnRecv( BYTE *pMsg, WORD wSize ) {

}

void TemplateLobbySession::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{
	DEBUG_MSG( LVL_DEBUG, "TemplateLobbySession::OnConnect. \n");
	TemplateServerSession::OnConnect( bSuccess, dwNetworkIndex );

	if ( bSuccess )
    {
		DEBUG_MSG( LVL_DEBUG, "TemplateLobbySession::OnConnect success. \n");
		TemplateServerSession::SendServerType();
		return;
	}

    DEBUG_MSG( LVL_DEBUG, "TemplateLobbySession::OnConnect fail. \n");
}

void TemplateLobbySession::OnDisconnect()
{
    DEBUG_MSG( LVL_DEBUG, "TemplateLobbySession::OnDisconnect. \n");
    TemplateServerSession::OnDisconnect();
}

void TemplateLobbySession::OnLogString( char * pszLog)
{

}
