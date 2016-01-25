#include "NetworkInclude.h"

void * connect_thread(void * param)
{
	printf ( "--->connect_thread 0x%x \n", pthread_self() );
	
	NetworkConnector * pClass = (NetworkConnector *) param;
	NetworkSession * pSession;
	
	while (true)
	{
		sem_wait( &pClass->m_semConnect );
		
		if ( pClass->m_bShutdown ) {
			pthread_exit (NULL);
		}
		
		while ( !pClass->m_pConnectingList->empty() ) {
			if ( pClass->m_bShutdown ) {
				pthread_exit (NULL);
			}
			
			pClass->m_pConnectingList->Lock();
			pSession = pClass->m_pConnectingList->front();
			pClass->m_pConnectingList->pop_front();
			pClass->m_pConnectingList->Unlock();
			
			int err = connect( pSession->GetSocket(), (SOCKADDR*)( pSession->GetSockAddr() ),sizeof(SOCKADDR_IN));
			
			if (err == SOCKET_ERROR) {
				pClass->m_pSync->m_pConnectFailList->Lock();
				pClass->m_pSync->m_pConnectFailList->push_back( pSession );			
				pClass->m_pSync->m_pConnectFailList->Unlock();
			}
			else {
				NetworkSocketOption::Nonblocking( pSession->GetSocket() );
				NetworkSocketOption::DisableBuffering( pSession->GetSocket() );
				pClass->m_pSync->m_pConnectSuccessList->Lock();
				pClass->m_pSync->m_pConnectSuccessList->push_back( pSession );			
				pClass->m_pSync->m_pConnectSuccessList->Unlock();
			}
		}
	}
}

NetworkConnector::NetworkConnector(void) 
{
	m_pConnectingList	= NULL;
	m_bShutdown 		= FALSE;
	m_hThread 			= 0;
}

NetworkConnector::~NetworkConnector(void)
{
	if ( !m_bShutdown )
		Shutdown();
	
	if ( m_pConnectingList )
		delete m_pConnectingList;
}

void NetworkConnector::Init( NetworkSyncHandler * _pSync) 
{
	m_pSync = _pSync;
	if ( m_pConnectingList ) {
		delete m_pConnectingList;
	}
	
	m_pConnectingList = new NetworkSessionList;
	
	if ( sem_init(&m_semConnect,0,0) != 0) {
		perror("Semaphore initialization failed");
	}
	pthread_create(&m_hThread, NULL, connect_thread, (void*)this );
}

void NetworkConnector::Connect( NetworkSession * pSession )
{
	m_pConnectingList->Lock();
	m_pConnectingList->push_back( pSession );			
	m_pConnectingList->Unlock();
	sem_post(&m_semConnect);
}

void NetworkConnector::Shutdown()
{
	m_bShutdown = TRUE;
	sem_post(&m_semConnect);
	pthread_cancel(m_hThread);
	pthread_join(m_hThread, NULL);
	sem_destroy(&m_semConnect);
}