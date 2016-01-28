#include "TemplateInclude.h"

TemplateUserSession::TemplateUserSession()
{
}

TemplateUserSession::~TemplateUserSession()
{

}

void TemplateUserSession::Clear()
{
	
}

void TemplateUserSession::OnRecv( BYTE *pMsg, WORD wSize ) {
	
}

void TemplateUserSession::OnConnect( BOOL bSuccess, DWORD dwNetworkIndex )
{
	/*
	WORD _wUserKey = TemplateMain::AllocSessionKey();
	if ( _wUserKey == 0 ) {
	    return;
    }
	this->SetUserKey( _wUser );
    TemplateMain::SetSession( _wKey, this);
	*/
	
	char buff[1024]  =  {0};
	char format[256] = 	"{\"protocol\":\"%d\",\"data1\":{\"type\":\"text/json\"}}";
	MSG_ENTERSERVER_ANC msg2;
	sprintf( buff, format, msg2.m_dwProtocol);
	WORD len = strlen(buff);
    this->Send( (BYTE*)buff, len );
}

void TemplateUserSession::OnDisconnect()
{

}

void TemplateUserSession::OnLogString( char * pszLog)
{

}
