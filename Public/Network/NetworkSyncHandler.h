#ifndef __NetworkSyncHandler_H_
#define __NetworkSyncHandler_H_
#include <UtilityInclude.h>
#include "NetworkDefine.h"
#include "NetworkSession.h"

class NetworkSyncHandler
{
	friend void * epoll_thread(void * param);
	friend void * io_thread(void * param);
	friend void * send_thread(void * param);
	friend void * connect_thread(void * param);
	friend void * accept_thread(void * param);
	friend class Acceptor;
	
public:
	NetworkSyncHandler();
	~NetworkSyncHandler();
	
	BOOL 		Init( NetworkServer *pServer, LPSYNCHANDLER_DESC lpDesc );
	BOOL 		StartListen(const char *IP, WORD wPort);
	void 		Update();
	void        Shutdown();
	BOOL 		IsRunning() { return !m_bShutdown;}
	DWORD		Connect(NetworkObject * pNet, char *IP, WORD wPort);
	BOOL 		IsListening();

	inline 
	DWORD       GetNumberOfConnections() {	return m_numActiveSessions; }
	inline 
	DWORD       GetKey() {	return m_dwKey; }
	
	void 		AddIoEvent(struct epoll_event * pEvent);
	int 		ModEpollEvent(NetworkSession *pSession, DWORD nEvent);
	int 		AddEpollEvent(NetworkSession *pSession);
	void 		DelEpollEvent(NetworkSession *pSession);
	
private:
	NetworkSession * AllocAcceptSession();
	NetworkSession * AllocConnectSession();
	void FreeSession(NetworkSession * pSession);
	
	void ProcessConnectSuccessList();
	void ProcessConnectFailList();
	void ProcessAcceptedSessionList();
	void ProcessActiveSessionList();

	void KickDeadSession();
	void ProcessSend();
	void KickAllSession();
	
private:
	BOOL m_bShutdown;
	
	NetworkSessionPool * m_pAcceptSessionPool;
	NetworkSessionPool * m_pConnectSessionPool;
	
	NetworkAcceptor  * m_pAcceptor;
	NetworkConnector * m_pConnector;
	
	NetworkServer 	   * m_pServer;
	NetworkSessionList * m_pActiveSessionList;
	NetworkSessionList * m_pAcceptedSessionList;
	NetworkSessionList * m_pConnectSuccessList;
	NetworkSessionList * m_pConnectFailList;
	NetworkSessionList * m_pTemplateList;

	DWORD 		m_dwKey;
	int 		m_epoll;
	DWORD		m_numIoThreads;
	pthread_t	m_hIoThread[MAX_IO_WORKER_THREAD];
	pthread_t	m_hEpollThread;
	
	UtilityCircuitQueue<struct epoll_event> * m_pEvents;
	UtilityMutex m_lockEvents;
	UtilityCond	m_condEvents;
	
	DWORD m_dwMaxPacketSize;
	DWORD m_numActiveSessions;
	DWORD m_dwMaxAcceptSession;
	
	fnCallBackCreateAcceptedObject m_fnCreateAcceptedObject;
	fnCallBackDestroyAcceptedObject m_fnDestroyAcceptedObject;
	fnCallBackDestroyConnectedObject m_fnDestroyConnectedObject;
};

#endif //  __Yond_ini_INCLUDED_
