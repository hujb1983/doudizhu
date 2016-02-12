#ifndef _LoginServer_H_
#define _LoginServer_H_
#include <TemplateSessionFactory.h>
#include <TemplatePacketHandler.h>
#include <TemplateMainServer.h>

/**************************************************************
	Login专属类型
**************************************************************/
NetworkObject * LoginServer_CreateClientObject() {
    DEBUG_MSG( LVL_TRACE, "LoginServer_CreateClientObject. \n");
	TemplateUserSession * pObj = TemplateSessionFactory::Instance()->AllocUserSession();
	if ( pObj==NULL ) {
		DEBUG_MSG( LVL_TRACE, "AllocUserSession Fail.\n");
		return NULL;
	}
	pObj->NotSendHeader();
	pObj->NotRecvHeader();
	return (NetworkObject*)(pObj);
}

class LoginServer : public TemplateMainServer
{
public:
	LoginServer()
	{
	}
	
	~LoginServer()
	{
	}
	
	virtual BOOL Init()
	{
		printf( "LoginServer::Init! \n");

		InitConfig( );
		InitDafaultConfig( "./ServerConfig.ini" );

		SetServerType(LOGIN_SERVER);
		LoadServerConfig( "./ServerConfig.ini" );
		LoadCompleteServerConfig();
		
		Printf(m_desc[0]);
		Printf(m_desc[1]);
		
		printf( "LoginServer Init! \n");
		
		if ( !TemplateMainServer::Init() ) {
			return FALSE;
		}
		
		return TRUE;
	}
};


#endif

