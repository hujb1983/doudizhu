#include "NetworkInclude.h"

void * epoll_thread(void * param)
{
	NetworkSyncHandler * pSync = (NetworkSyncHandler *) param;
	pSync->m_epoll = epoll_create(SOCKET_HOLDER_SIZE);
	
	if (pSync->m_epoll == -1) {
		pthread_exit(0);
	}

	struct epoll_event * events = new struct epoll_event[SOCKET_HOLDER_SIZE];
	while( !pSync->m_bShutdown )
	{
		int fd_count = epoll_wait(pSync->m_epoll, events, SOCKET_HOLDER_SIZE, 5000);

		for ( int i = 0; i < fd_count; i++ )
		{
			//printf("\n==================== epoll_thread ============\n");
			NetworkSession * pSession = (NetworkSession *) events[i].data.ptr;

			if ( (events[i].events & EPOLLHUP) || (events[i].events & EPOLLERR) ) {
				pSession->Remove();
				continue;
			}
			if ( events[i].events & EPOLLOUT ) {
				pSession->OnSend();
				pSync->ModEpollEvent(pSession, EPOLLIN | EPOLLET | EPOLLERR | EPOLLHUP);
			}

			if ( events[i].events & EPOLLIN ) {
				pSync->AddIoEvent(&events[i]);
			}
		}
	}

	delete [] events;

	printf ("epoll_thread 0x%x exit \n ", pthread_self() );
	pthread_exit(0);
}

void * io_thread( void * param )
{
	NetworkSyncHandler * pSync = (NetworkSyncHandler *) param;
	printf("--->io_thread:0x%x\n", pthread_self());

	NetworkSession * pSession = NULL;

	struct epoll_event event;

	while (true)
	{
		pSync->m_lockEvents.Lock();
		pSync->m_condEvents.Wait(&pSync->m_lockEvents);

		//printf("\n---------------- io thread condEvent ------------------ \n");
		if ( pSync->m_bShutdown ) {
			pSync->m_lockEvents.Unlock();
			printf (" io_thread 0x%x exit \n ", pthread_self() );
			pthread_exit (NULL);
		}

		if ( !pSync->m_pEvents->Dequeue(&event, 1) ) {
			pSync->m_lockEvents.Unlock();
			continue;
		}

		pSync->m_lockEvents.Unlock();

		pSession = (NetworkSession *) event.data.ptr;

		if ( event.events == 0x800 ) {
			pSession->DoSend(pSync);
		}
		else {
			pSession->DoRecv();
		}
	}
}


NetworkSyncHandler::NetworkSyncHandler()
{
	m_dwKey = 0;
	m_epoll = 0;
	m_numIoThreads = 0;
	m_dwMaxPacketSize = 0;
	m_numActiveSessions = 0;
	m_dwMaxAcceptSession = 0;

	m_pServer 			= NULL;

	m_pAcceptSessionPool	= NULL;
	m_pConnectSessionPool	= NULL;
	m_pAcceptor 			= NULL;
	m_pConnector 			= NULL;

	m_bShutdown = FALSE;

	m_pActiveSessionList	= NULL;
	m_pAcceptedSessionList	= NULL;
	m_pConnectSuccessList	= NULL;
	m_pConnectFailList	= NULL;
	m_pTemplateList		= NULL;

	m_fnCreateAcceptedObject	= NULL;
	m_fnDestroyAcceptedObject	= NULL;
	m_fnDestroyConnectedObject	= NULL;
}

NetworkSyncHandler::~NetworkSyncHandler()
{
	if (!m_bShutdown) {
		this->Shutdown();
	}

	if (m_pAcceptSessionPool) 	delete m_pAcceptSessionPool;
	if (m_pConnectSessionPool) 	delete m_pConnectSessionPool;
	if (m_pAcceptor) 		    delete m_pAcceptor;
	if (m_pConnector) 		    delete m_pConnector;

	if (m_pActiveSessionList) 	delete m_pActiveSessionList;
	if (m_pAcceptedSessionList) 	delete m_pAcceptedSessionList;
	if (m_pConnectSuccessList) 	delete m_pConnectSuccessList;
	if (m_pConnectFailList) 	delete m_pConnectFailList;
	if (m_pTemplateList) 		delete m_pTemplateList;
}

BOOL NetworkSyncHandler::Init( NetworkServer *pServer, LPSYNCHANDLER_DESC lpDesc )
{
	m_pServer	= pServer;

	//assert( !IsBadReadPtr( lpDesc->fnCreateAcceptedObject, sizeof(lpDesc->fnCreateAcceptedObject) ) );
	//assert( !IsBadReadPtr( lpDesc->fnDestroyAcceptedObject, sizeof(lpDesc->fnDestroyAcceptedObject) ) );
	//assert( !IsBadReadPtr( lpDesc->fnDestroyConnectedObject, sizeof(lpDesc->fnDestroyConnectedObject) ) );

	m_fnCreateAcceptedObject		= lpDesc->fnCreateAcceptedObject;
	m_fnDestroyAcceptedObject		= lpDesc->fnDestroyAcceptedObject;
	m_fnDestroyConnectedObject		= lpDesc->fnDestroyConnectedObject;
	m_dwKey							= lpDesc->dwSyncHandlerKey;

	m_pActiveSessionList	= new NetworkSessionList;
	m_pAcceptedSessionList	= new NetworkSessionList;
	m_pConnectSuccessList	= new NetworkSessionList;
	m_pConnectFailList		= new NetworkSessionList;
	m_pTemplateList			= new NetworkSessionList;

	m_dwMaxAcceptSession	= lpDesc->dwMaxAcceptSession;

	m_pAcceptSessionPool	= new NetworkSessionPool( 	lpDesc->dwMaxAcceptSession + EXTRA_ACCEPTEX_NUM,
														lpDesc->dwSendBufferSize,
														lpDesc->dwRecvBufferSize,
														lpDesc->dwMaxPacketSize,
														lpDesc->dwTimeOut,
														1,
														TRUE );

	m_pConnectSessionPool	= new NetworkSessionPool( 	lpDesc->dwMaxConnectSession,
														lpDesc->dwSendBufferSize,
														lpDesc->dwRecvBufferSize,
														lpDesc->dwMaxPacketSize,
														lpDesc->dwTimeOut,
														m_pAcceptSessionPool->GetLength() + 1,
														FALSE );


	assert( lpDesc->dwMaxPacketSize > sizeof(PACKET_HEADER) );
	m_dwMaxPacketSize =	lpDesc->dwMaxPacketSize;

	m_pEvents = new UtilityCircuitQueue<struct epoll_event>;
	m_pEvents->Create(SOCKET_HOLDER_SIZE*2, SOCKET_HOLDER_SIZE);

	pthread_create( &m_hEpollThread, NULL, epoll_thread, (void*)this);

	assert( lpDesc->dwNumberOfIoThreads <= MAX_IO_WORKER_THREAD );
	m_numIoThreads = lpDesc->dwNumberOfIoThreads;
	
	for( DWORD i = 0; i < m_numIoThreads; ++i )	{
		pthread_create( &m_hIoThread[i], NULL, io_thread, (void*)this);
	}

	if ( lpDesc->dwNumberOfAcceptThreads )	{
		m_pAcceptor	= new NetworkAcceptor;
		m_pAcceptor->Init( this );
	}

	if ( lpDesc->dwNumberOfConnectThreads )	{
		m_pConnector	= new NetworkConnector;
		m_pConnector->Init( this );
	}

	return TRUE;
}

DWORD NetworkSyncHandler::Connect(NetworkObject * pNet, char *szIP, WORD wPort)
{
	if (pNet->m_pSession != NULL)
		return 0;

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addr;
	addr.sin_family			= AF_INET;
	addr.sin_addr.s_addr 	= inet_addr( szIP );
	addr.sin_port 			= htons( wPort );

	NetworkSession * pSession = AllocConnectSession();
	assert( pSession != NULL && "Connect dwMaxConnectSession");

	pSession->SetSocket( sock );
	pSession->SetSockAddr( addr );

	pSession->BindNetworkObject(pNet);
	m_pConnector->Connect(pSession);

	return pSession->GetIndex();
}

BOOL NetworkSyncHandler::StartListen(const char *szIP, WORD wPort)
{
	assert (m_dwMaxAcceptSession > 0);

	if (this->IsListening()) {
		return TRUE;
	}

	if ( !m_pAcceptor->StartListen(szIP, wPort) ) {
		printf("Listen socket creation failed. \n");
		return FALSE;
	}
	return TRUE;
}

BOOL NetworkSyncHandler::IsListening()
{
	return m_pAcceptor->IsListening();
}

//=================================================================================================
/*
	@remarks
*/
//=================================================================================================
NetworkSession * NetworkSyncHandler::AllocAcceptSession()
{
	return m_pAcceptSessionPool->Alloc();
}

NetworkSession * NetworkSyncHandler::AllocConnectSession()
{
	return m_pConnectSessionPool->Alloc();
}

void NetworkSyncHandler::FreeSession(NetworkSession * pSession)
{
	pSession->CloseSocket();
	pSession->Init();
	if (pSession->IsAcceptSocket())
	{
		m_pAcceptSessionPool->Free(pSession);
	}
	else
	{
		m_pConnectSessionPool->Free(pSession);
	}
}

//=================================================================================================
/*
	@remarks
*/
//=================================================================================================
void NetworkSyncHandler::ProcessConnectSuccessList()
{
	NETWORKSESSION_LIST_ITER	it;
	NetworkSession				*pSession;
	NETWORKSESSION_LIST			activeList;

	m_pConnectSuccessList->Lock();
	m_pTemplateList->splice( * m_pConnectSuccessList );
	m_pConnectSuccessList->Unlock();

	while( !m_pTemplateList->empty() )
	{
		pSession = m_pTemplateList->pop_front();

		if (this->AddEpollEvent( pSession )) {
			pSession->OnConnect(TRUE);
			activeList.push_back(pSession);
		}
		else {
			this->FreeSession(pSession);
			pSession->OnConnect(FALSE);
		}
	}

	if ( !activeList.empty() )
	{
		m_numActiveSessions += (DWORD) activeList.size();

		m_pActiveSessionList->Lock();
		m_pActiveSessionList->splice( activeList );
		m_pActiveSessionList->Unlock();
	}
}

void NetworkSyncHandler::ProcessConnectFailList()
{
	NetworkSession	*pSession;

	m_pConnectFailList->Lock();
	while ( ! m_pConnectFailList->empty() )
	{
		pSession = m_pConnectFailList->pop_front();
		this->FreeSession(pSession);
		pSession->OnConnect(FALSE);
	}
	m_pConnectFailList->Unlock();
}

void NetworkSyncHandler::ProcessAcceptedSessionList()
{
	NETWORKSESSION_LIST_ITER it;
	NetworkSession *pSession;

	m_pAcceptedSessionList->Lock();
	m_pTemplateList->splice( *m_pAcceptedSessionList );
	m_pAcceptedSessionList->Unlock();

	NETWORKSESSION_LIST	activeList;
	while( !m_pTemplateList->empty() )
	{
		pSession = m_pTemplateList->pop_front();
		if (m_numActiveSessions >= m_dwMaxAcceptSession) {
			printf("Connection full! no available accept socket! \n");
			FreeSession(pSession);
			continue;
		}

		if (!AddEpollEvent(pSession)) {
			FreeSession(pSession);
			continue;
		}

		NetworkObject * pNet = m_fnCreateAcceptedObject();
		assert(pNet);

		pSession->BindNetworkObject(pNet);
		pSession->OnAccept();

		++m_numActiveSessions;
		activeList.push_back(pSession);
	}

	if ( !activeList.empty() ) {
		m_pActiveSessionList->Lock();
		m_pActiveSessionList->splice( activeList );
		m_pActiveSessionList->Unlock();
	}
}

void NetworkSyncHandler::ProcessActiveSessionList()
{
	NETWORKSESSION_LIST_ITER it;
	NetworkSession *pSession;

	for (it = m_pActiveSessionList->begin(); it != m_pActiveSessionList->end(); ++it)
	{
		pSession = *it;

		if ( pSession->ShouldBeRemoved() ){
			continue;
		}

		if ( pSession->HasDisconnectOrdered() ) {
			if ( pSession->GetSendBuffer()->GetLength() == 0 ) {
				pSession->Remove();
			}
		}
		else
		{
			if ( pSession->IsAcceptSocket() && pSession->IsOnIdle() ) {
				//pSession->OnLogString( "Idle Session." );
				pSession->Remove();
				continue;
			}

			if ( !pSession->ProcessRecvdPacket(m_dwMaxPacketSize) ) {
				pSession->Remove();
			}
		}
	}
}


void NetworkSyncHandler::KickDeadSession()
{
	NETWORKSESSION_LIST_ITER it, it2;
	NetworkSession *pSession;

	m_pActiveSessionList->Lock();
	for (it = m_pActiveSessionList->begin(); it != m_pActiveSessionList->end();)
	{
		pSession = *it;
		if ( pSession->ShouldBeRemoved() ) {
			it2 = it++;
			m_pActiveSessionList->remove( it2 );
			m_pTemplateList->push_back( pSession );
		}
		else {
			++it;
		}
	}
	m_pActiveSessionList->Unlock();

	while ( !m_pTemplateList->empty() ) {
		NetworkSession * pSession = m_pTemplateList->pop_front();

		--m_numActiveSessions;
		NetworkObject * pNet = pSession->GetNetworkObject();

		pSession->UnbindNetworkObject();
		DelEpollEvent( pSession );
		FreeSession( pSession );

		pNet->OnDisconnect();
		if ( pSession->IsAcceptSocket() ) {
			m_fnDestroyAcceptedObject(pNet);
		}
		else {
			m_fnDestroyConnectedObject(pNet);
		}
	}
}

void NetworkSyncHandler::ProcessSend()
{
	NETWORKSESSION_LIST_ITER it;
	NetworkSession *pSession;

	m_pActiveSessionList->Lock();
	for (it = m_pActiveSessionList->begin(); it != m_pActiveSessionList->end(); ++it)
	{
		pSession = *it;

		if ( pSession->ShouldBeRemoved() ) {
			continue;
		}

		if (pSession->PreSend(this)==FALSE ) {
			pSession->Remove();
		}
	}
	m_pActiveSessionList->Unlock();
}

void NetworkSyncHandler::KickAllSession()
{
	NETWORKSESSION_LIST_ITER 	it;

	m_pActiveSessionList->Lock();
	for (it = m_pActiveSessionList->begin(); it != m_pActiveSessionList->end(); ++it) {
		(*it)->Remove();
	}
	m_pActiveSessionList->Unlock();
}

void NetworkSyncHandler::Update()
{
	this->ProcessActiveSessionList();

	if ( !m_pAcceptedSessionList->empty() ) {
		this->ProcessAcceptedSessionList();
	}

	if ( !m_pConnectSuccessList->empty() ) {
		this->ProcessConnectSuccessList();
	}

	if ( !m_pConnectFailList->empty() ) {
		this->ProcessConnectFailList();
	}

	this->KickDeadSession();
}

void NetworkSyncHandler::Shutdown()
{
	m_bShutdown = TRUE;

	close(m_epoll);

	this->KickAllSession();
	this->ProcessActiveSessionList();
	this->KickDeadSession();

	if ( m_pAcceptor ) {
		m_pAcceptor->Shutdown();
	}

	if ( m_pConnector ) {
		m_pConnector->Shutdown();
	}

	pthread_cancel(m_hEpollThread);
	pthread_join(m_hEpollThread, NULL);

	m_condEvents.Broadcast();
	for(int i = 0; i < m_numIoThreads; i++) {
		pthread_join(m_hIoThread[i], NULL);
	}
}

int NetworkSyncHandler::ModEpollEvent(NetworkSession * pSession, DWORD nEvent)
{
	struct epoll_event ev;
	memset(&ev, 0, sizeof(epoll_event));

	ev.events = nEvent | EPOLLET;
	ev.data.ptr = pSession;

	if ( epoll_ctl(m_epoll, EPOLL_CTL_MOD, pSession->GetSocket(), &ev) !=0 ) {
		//pSession->OnLogString("Epoll could not mod event to epoll set on fd %u", pSession->GetSocket() );
		return FALSE;
	}
	return TRUE;

}

int NetworkSyncHandler::AddEpollEvent(NetworkSession *pSession)
{
	struct epoll_event ev;
	memset(&ev, 0, sizeof(epoll_event));

	ev.events = EPOLLIN | EPOLLET | EPOLLERR | EPOLLHUP;
	ev.data.ptr = pSession;

	if ( epoll_ctl(m_epoll, EPOLL_CTL_ADD, pSession->GetSocket(), &ev) !=0 ) {
		//pSession->OnLogString("Epoll could not add event to epoll set on fd %u", pSession->GetSocket() );
		return FALSE;
	}
	return TRUE;
}

void NetworkSyncHandler::DelEpollEvent(NetworkSession *pSession)
{
	struct epoll_event ev;
	memset(&ev, 0, sizeof(epoll_event));

	ev.events = EPOLLIN | EPOLLOUT | EPOLLERR | EPOLLHUP | EPOLLONESHOT;
	ev.data.ptr = pSession;

	if ( epoll_ctl(m_epoll, EPOLL_CTL_DEL, pSession->GetSocket(), &ev) !=0 ) {
		//pSession->OnLogString("Epoll could not del event to epoll set on fd %u", pSession->GetSocket() );
	}
}

void NetworkSyncHandler::AddIoEvent(struct epoll_event * pEvent)
{
	m_lockEvents.Lock();
	m_pEvents->Enqueue(pEvent, 1);
	m_lockEvents.Unlock();

	m_condEvents.Signal();
}
