#include "NetworkInclude.h"

void * accept_thread(void * param)
{
	NetworkAcceptor	* pClass = (NetworkAcceptor *) param;
	NetworkSession 	* pSession;
	
	while ( !pClass->m_bShutdown )
	{
		struct sockaddr_in addr;
		int len = sizeof(struct sockaddr_in);
		memset(&addr, 0, sizeof(struct sockaddr_in));	
	
		SOCKET sock = accept(pClass->m_listenSocket, (sockaddr *)&addr, (socklen_t*)&len );
		if (sock == -1)
			continue;
	
		NetworkSocketOption::Nonblocking( sock );
		NetworkSocketOption::DisableBuffering( sock );
				
		NetworkSession * pSession = pClass->m_pSync->AllocAcceptSession();
		if (pSession == NULL) {
			continue;
		}
		
		pSession->SetSocket(sock);
		pSession->SetSockAddr(addr);
			
		pClass->m_pSync->m_pAcceptedSessionList->Lock();
		pClass->m_pSync->m_pAcceptedSessionList->push_back( pSession );			
		pClass->m_pSync->m_pAcceptedSessionList->Unlock();
	}
	
	pthread_exit(0);
}

NetworkAcceptor::NetworkAcceptor(void) 
{
	m_listenSocket	= INVALID_SOCKET;
	m_bShutdown		= 0;
	m_hAcceptThread = 0;
}

NetworkAcceptor::~NetworkAcceptor(void)
{
	Shutdown();
}

void NetworkAcceptor::Init( NetworkSyncHandler * _pSync) 
{
	m_pSync = _pSync;
}

BOOL NetworkAcceptor::StartListen( const char *szIP, WORD wPort )
{
	if ( m_listenSocket != INVALID_SOCKET ) {
		return FALSE;
	}
		
	m_listenSocket = socket(AF_INET, SOCK_STREAM, 0);

	if ( m_listenSocket == INVALID_SOCKET ) {	
		return FALSE;
	}
	
	NetworkSocketOption::ReuseAddr(m_listenSocket);
	
	memset( &m_sockaddr, 0, sizeof(m_sockaddr) );
	
	m_sockaddr.sin_family		= AF_INET;
	m_sockaddr.sin_addr.s_addr	= ( szIP == NULL || strlen (szIP) == 0) ? htonl(INADDR_ANY) : inet_addr(szIP);
	m_sockaddr.sin_port 		= htons( wPort );
	
	int err = bind (m_listenSocket, (SOCKADDR *)&m_sockaddr, sizeof(m_sockaddr) );
	
	if ( err == SOCKET_ERROR )
	{
		NetworkSocketOption::CloseSocket(m_listenSocket);	
		return FALSE;
	}

	err = listen( m_listenSocket, 5 );
	if ( err == SOCKET_ERROR )
	{
		NetworkSocketOption::CloseSocket( m_listenSocket );
		return  FALSE;
	}
	
	pthread_create( &m_hAcceptThread, NULL, accept_thread, (void*) this );
	
	return TRUE;
}

void NetworkAcceptor::Shutdown()
{
	if ( m_listenSocket != INVALID_SOCKET )
	{
		NetworkSocketOption::CloseSocket(m_listenSocket);
		m_bShutdown = TRUE;
		pthread_cancel(m_hAcceptThread);
		pthread_join(m_hAcceptThread, NULL);
	}
	m_listenSocket = INVALID_SOCKET;
	m_hAcceptThread = 0;
	m_bShutdown = 0;
}
