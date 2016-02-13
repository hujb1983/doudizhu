#ifndef _DBServer_H_
#define _DBServer_H_
#include <TemplateSeasoning.h>
#include <TemplateSessionFactory.h>
#include <TemplatePacketHandler.h>
#include <TemplateMainServer.h>

class DBServer : public TemplateMainServer
{
public:
	DBServer()
	{
	}
	
	~DBServer()
	{
	}
	
	virtual BOOL Init()
	{
		printf( "DBServer Init! \n");

		InitConfig( );
		InitDafaultConfig( "./ServerConfig.ini" );

		SetServerType(DB_SERVER);
		LoadServerConfig( "./ServerConfig.ini" );
		LoadCompleteServerConfig();
		
		Printf(m_desc[0]);
		Printf(m_desc[1]);
		
		printf( "DBServer Init! \n");
		
		TemplateSeasoning system;
		system.GetOpenDatabase() = TRUE;
		
		if ( TemplateMainServer::Init() ) {
			return TRUE;
		}
		
		return FALSE;
	}
};

#endif

