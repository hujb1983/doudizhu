#ifndef _NetworkIOCPServer_H_
#define _NetworkIOCPServer_H_
#include <UtilityInclude.h>

class NetworkIOCPServer
{
	friend void* send_thread( void* param );

public:
	NetworkIOCPServer();
	virtual ~NetworkIOCPServer();

	BOOL 		Init( LPSYNCHANDLER_DESC lpDesc, DWORD dwNumberofIoHandlers );
	BOOL 		StartListen( DWORD dwIoHandlerKey, const char *pIP, WORD wPort );
	void 		Update();
	void 		Shutdown();
	DWORD 		Connect( DWORD dwHandlerKey, NetworkObject *pNetworkObject, char *pszIP, WORD wPort );
	BOOL 		IsListening( DWORD dwHandlerKey );
	DWORD 		GetNumberOfConnections( DWORD dwHandlerKey );

private:
	void 		CreateSyncHandler( LPSYNCHANDLER_DESC lpDesc );

	pthread_t 	m_hSendThread;
	BOOL 		m_bShutdown;
	
	SYNCHANDLER_MAP m_mapHandlers;
};

#endif // _IOCPSERVER_H_INCLUDED_

