#ifndef _NetworkAcceptor_H_
#define _NetworkAcceptor_H_
#include <UtilityDefine.h>
#include <NetworkDefine.h>

class NetworkAcceptor
{
	friend void * accept_epoll_event_thread(void * param);
	friend void * accept_thread(void * param);

public:
	NetworkAcceptor(void);
	~NetworkAcceptor(void);
	
	void Init( NetworkSyncHandler * pSync );
	
	BOOL StartListen( const char *szIP, WORD wPort);

	void Shutdown();

	inline BOOL IsListening() { 
		return m_listenSocket != INVALID_SOCKET; 
	}

	inline SOCKET GetListenSocket() { 
		return m_listenSocket; 
	}
	
public:	
	NetworkSyncHandler * m_pSync;
	
	SOCKET m_listenSocket;
	SOCKADDR_IN m_sockaddr;
	
	int m_bShutdown;
	pthread_t m_hAcceptThread;
};

#endif //  __ACCEPTOR_H_INCLUDED_
