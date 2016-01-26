#ifndef _TemplateMainServer_H_
#define _TemplateMainServer_H_
#include <CommonInclude.h>
#include <NetworkInclude.h>
#include <NetworkInclude.h>
#include "TemplateSessionFactory.h"

NetworkObject * CreateServerSideAcceptedObject();
VOID DestroyServerSideAcceptedObject( NetworkObject *pNetworkObject );
VOID DestroyServerSideConnectedObject( NetworkObject *pNetworkObject );

NetworkObject * CreateClientSideAcceptedObject();
VOID DestroyClientSideAcceptedObject( NetworkObject * pNetworkObject );
VOID DestroyClientSideConnectedObject( NetworkObject * pNetworkObject );


/**************************************************************
	服务器框架模板
**************************************************************/
class TemplateMainServer
{
	enum { CLIENT_SYNCHANDLER = 0, SERVER_SYNCHANDLER = 1, };

public:
	TemplateMainServer(void);
	~TemplateMainServer(void);

	virtual BOOL Init();

	BOOL StartServerSideListen(WORD wPort);
	BOOL StartClientSideListen(WORD wPort);

	BOOL Update( DWORD dwDeltaTick );

	BOOL ConnectToServer( TemplateServerSession * pSession, char * pszIP, WORD wPort );
    BOOL MaintainConnection();
	
private:
	BYTE m_bShutdown;
	NetworkServer * m_pServer;
};


#endif // _AGENTSERVER_H_INCLUDED_
