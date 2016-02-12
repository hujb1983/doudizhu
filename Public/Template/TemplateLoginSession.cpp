#include "TemplateInclude.h"

TemplateLoginSession::TemplateLoginSession()
{
}

TemplateLoginSession::~TemplateLoginSession()
{

}

void TemplateLoginSession::Clear()
{

}

void TemplateLoginSession::OnRecv( BYTE *pMsg, WORD wSize ) {

}

void TemplateLoginSession::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{
	DEBUG_MSG( LVL_DEBUG, "TemplateLoginSession::OnConnect. \n");
	TemplateServerSession::OnConnect( bSuccess, dwNetworkIndex );

	if ( bSuccess )
    {
		DEBUG_MSG( LVL_DEBUG, "TemplateLoginSession::OnConnect success. \n");
		TemplateServerSession::SendServerType();
		return;
	}

    DEBUG_MSG( LVL_DEBUG, "TemplateLoginSession::OnConnect fail. \n");
}

void TemplateLoginSession::OnDisconnect()
{
    DEBUG_MSG( LVL_DEBUG, "TemplateLoginSession::OnDisconnect. \n");
    TemplateServerSession::OnDisconnect();
}

void TemplateLoginSession::OnLogString( char * pszLog)
{

}
