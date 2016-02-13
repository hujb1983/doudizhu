#include "TemplateInclude.h"
#include "TemplateSeasoning.h"
#include "TemplatePacketHandler.h"
#include <UtilityParserJson.h>

TemplateUserSession::TemplateUserSession()
{
}

TemplateUserSession::~TemplateUserSession()
{

}

void TemplateUserSession::Init()
{
    TemplateSeasoning system;
    if ( system.GetClientSandHead()==FALSE ) {
        this->NotRecvHeader();
    }
    if ( system.GetClientRecvHead()==FALSE ) {
        this->NotSendHeader();
    }
}

void TemplateUserSession::Clear()
{

}

void TemplateUserSession::OnRecv( BYTE *pMsg, WORD wSize )
{
    UtilityParserJson jsMap;
    if ( jsMap.SetJson( (char*) pMsg ) ) {
        return;
    }

    int pid = 0;
    jsMap.ReadInteger("protocol", pid);
	TemplatePacketHandler::ParsePacket_Client( pid, this, (MSG_BASE*)pMsg, wSize );
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
}

void TemplateUserSession::OnAccept( DWORD dwNetworkIndex )
{
	char buff[1024]  =  {0};
	char format[256] = 	"{\"protocol\":\"%d\",\"data\":{\"type\":\"text/json\"}}";
	MSG_ENTERSERVER_ANC msg2;
	sprintf( buff, format, msg2.m_dwProtocol );
	WORD len = strlen(buff);
    this->Send( (BYTE*)buff, len );
}

void TemplateUserSession::OnDisconnect()
{

}

void TemplateUserSession::OnLogString( char * pszLog)
{

}
