#ifndef _UtilityServerInfo_H_
#define _UtilityServerInfo_H_
#include <UtilityDefine.h>
#include <UtilityIni.h>
using namespace std;

#define IP_MAX_LEN  (16)

/*****************************************
// 服务器类别
*****************************************/
enum eSERVER_TYPE {
	UNKNOWN_SERVER 	 = 0,
	AGENT_SERVER		, 		// 代理服务器
	GAME_SERVER 		,		// 游戏服务器
	DB_SERVER           ,       // 数据库服务器
	LOGIN_SERVER 		,		// 登录服务器
	WORLD_SERVER 		,		// 聊天服务器
	LOBBY_SERVER 		,		// 大厅
	TEMP_SERVER 		,		// 临时
};

struct SERVER_INFO {
	char 	m_strIp[IP_MAX_LEN]; 	// IP
	DWORD 	m_dwPort; 				// PORT
	SERVER_INFO() {
		memset(this, 0, sizeof(SERVER_INFO));
		strcpy(m_strIp, "");
		m_dwPort = 0;
	}
};

class UtilityServerInfo
{
public:
	UtilityServerInfo(void);
	~UtilityServerInfo(void);

	// 初始化
	BOOL	Init(char * strFileName);

	BOOL	GetString( const char * strSection, 
					   const char * szName, 
					   const char * szDefault, 
					   char * pszValue );
					   
	int 	GetInt( const char * strSection, 
					const char * szName, 
					const char * szDefault );

	// 获取服务器端口信息
	SERVER_INFO GetServerInfo(eSERVER_TYPE type);

private:
	UtilityIni * pIniFile;	
};
extern UtilityServerInfo g_InfoParser;

#endif // _INFOPARSER_H_INCLUDED_
