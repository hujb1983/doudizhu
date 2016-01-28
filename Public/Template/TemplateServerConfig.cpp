#include <UtilityIni.h>
#include "TemplateServerConfig.h"

TemplateServerConfig::TemplateServerConfig()
{
	
}

TemplateServerConfig::~TemplateServerConfig()
{

}

void TemplateServerConfig::SetServerType( BYTE byServerType )
{
	
}

void TemplateServerConfig::LoadConfig(const char * szConfig)
{
	UtilityIni _ini( szConfig );
	LoadLocalServer(_ini);
	LoadConnectObjects(_ini);
}

void TemplateServerConfig::LoadLocalServer( const char * szServerTypeName, UtilityIni & ini )
{
	std::string szHandler;
	szHandler = _ini.GetString(szServerTypeName, "ServerHandler", "true" );
	if (strcpy(szHandler.c_str(),"true")==0 ) {
		_ini.GetString(szServerTypeName, "ClientHandler", "true" );
		_ini.GetString(szServerTypeName, "ClientHandler", "true" );
	}
	szHandler = _ini.GetString(szServerTypeName, "ClientHandler", "true" );
	if (strcpy(szHandler.c_str(),"true")==0 ) {
		_ini.GetString(szServerTypeName, "ClientHandler", "true" );
		_ini.GetString(szServerTypeName, "ClientHandler", "true" );	
	}
}

void TemplateServerConfig::LoadConnectObjects( UtilityIni & ini )
{
	
}
