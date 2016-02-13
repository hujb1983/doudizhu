#ifndef _LoginServer_H_
#define _LoginServer_H_
#include <TemplateSeasoning.h>
#include <TemplateSessionFactory.h>
#include <TemplatePacketHandler.h>
#include <TemplateMainServer.h>

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
		
		Printf( m_desc[0] );
		Printf( m_desc[1] );
		
		printf( "LoginServer Init! \n");
		
		TemplateSeasoning system;
		system.GetClientSandHead() = FALSE;
		system.GetClientRecvHead() = FALSE;
		system.GetOpenDatabase()   = FALSE;
		
		if ( !TemplateMainServer::Init() ) {
			return FALSE;
		}
		
		return TRUE;
	}
};


#endif

