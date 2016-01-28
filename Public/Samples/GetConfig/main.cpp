#include <UtilityDefine.h>
#include <UtilityIni.h>

int main() 
{ 
	UtilityIni _ini( "./ServerConfig.ini" );
	
	std::string szName = _ini.GetString("DB_SERVER", "name");
	std::string szIP   = _ini.GetString("DB_SERVER", "ip");
	std::string szPort = _ini.GetString("DB_SERVER", "port");
	
	printf( "**************************\n" );
	printf( "String Type! \n" );
	printf( "name = %s \n", szName.c_str() );
	printf( "ip = %s \n", 	szIP.c_str() );
	printf( "port = %s \n", szPort.c_str() );
	printf( "**************************\n\n" );
	
	// Key值不区分大小写
	int iPort = _ini.GetInteger("DB_sERVER", "Port");
	printf( "**************************\n" );
	printf( "Integer Type! \n" );
	printf( "port = %s \n", szPort.c_str() );
	printf( "**************************\n\n" );
	return 0;
}