#ifndef _TemplateMainServer_H_
#define _TemplateMainServer_H_
#include <CommonInclude.h>
#include <NetworkInclude.h>
#include "TemplateServerConfig.h"
#include "TemplateSessionFactory.h"

NetworkObject * CreateServerSideAcceptedObject();
VOID DestroyServerSideAcceptedObject( NetworkObject *pNetworkObject );
VOID DestroyServerSideConnectedObject( NetworkObject *pNetworkObject );

NetworkObject * CreateClientSideAcceptedObject();
VOID DestroyClientSideAcceptedObject( NetworkObject * pNetworkObject );
VOID DestroyClientSideConnectedObject( NetworkObject * pNetworkObject );

enum { CLIENT_SYNCHANDLER = 0, SERVER_SYNCHANDLER = 1, };

/**************************************************************
	服务器框架模板
**************************************************************/
class TemplateMainServer : public TemplateServerConfig
{
public:
	TemplateMainServer(void);
	~TemplateMainServer(void);

	void StartServer();

	virtual BOOL Init();
	virtual BOOL SendTo( WORD wKey, BYTE * pMsg, WORD wSize);

	BOOL StartServerSideListen( WORD wPort );
	BOOL StartClientSideListen( WORD wPort );

	BOOL Update( DWORD dwDeltaTick );
	BOOL UpdateDatabase( DWORD dwDeltaTick );

	BOOL ConnectToServer( TemplateServerSession * pSession, char * pszIP, WORD wPort );
	void ServerConnector( TemplateServerSession * pSession );
    BOOL MaintainConnection();

public:
	BOOL SendToLogin( BYTE * pMsg, WORD wSize );
	BOOL SendToAgent( BYTE * pMsg, WORD wSize );
	BOOL SendToLobby( BYTE * pMsg, WORD wSize );
	BOOL SendToGames( BYTE * pMsg, WORD wSize );
	BOOL SendToDB( BYTE * pMsg, WORD wSize );
	
private:
	BYTE m_bShutdown;
	NetworkServer * m_pServer;

public:
	static void InitSessionArray();
	static void CloseSessionArray();

	static DWORD AllocSessionKey();
	static void FreeSessionKey(DWORD wIndex);

	static DWORD SetSession(TemplateServerSession * pSession);
	static void FreeSession(DWORD wIndex);

private:
	static TemplateServerSession * m_pSessionArray[MAX_PORT+1];
	static UtilityKeyGenerator m_cObjectKeys;
    static WORD m_uiCountKey;
};


#endif // _AGENTSERVER_H_INCLUDED_
