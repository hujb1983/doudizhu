#ifndef _TemplateServerConfig_H_
#define _TemplateServerConfig_H_
#include "TemplateInclude.h"
#include <UtilityIni.h>

class TemplateServerConfig
{
public:
	TemplateServerConfig();
	virtual ~TemplateServerConfig();

public:
	void InitConfig();
	void SetServerType( BYTE byServerType );
	void LoadServerConfig( const char * szConfig );

	void InitDafaultConfig( const char * szConfig );
	void LoadDafaultConfig( UtilityIni & _ini );

public:
    void Printf( SYNCHANDLER_DESC & desc );

private://本地服务器类型配置
	void LoadLocalServer( const char * szServerTypeName, UtilityIni & ini );
	void LoadConnectObjects( const char * szServerTypeName, UtilityIni & ini );
	void LoadConnectObjectsAddress(const char*, UtilityIni&, TemplateServerSession *);


public:
	BYTE m_byServerType;

	// 服务器IOCP处理
	BYTE m_byDafaultIOSize;
	SYNCHANDLER_DESC m_ddesc[2];

	// 服务器IOCP处理
	BYTE m_byIOSize;
	SYNCHANDLER_DESC m_desc[2];

	// Listen Port.
	WORD m_wPort[2];

public://配置需要连接的服务器群
	TemplateLoginSession * m_pLoginSession;
	TemplateAgentSession * m_pAgentSession;
	TemplateLobbySession * m_pLobbySession;
	TemplateGameSession * m_pGameSession;
	TemplateDBSession * m_pDBSession;
};

#endif // _AGENTPLAYER_H_INCLUDED_
