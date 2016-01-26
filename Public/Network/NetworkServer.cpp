#include "NetworkInclude.h"

void* send_thread( void* param )
{
	NetworkServer *pIOCPServer = (NetworkServer*)param;
	
	SYNCHANDLER_MAP_ITER	it;
	while( !pIOCPServer->m_bShutdown ) {
		Sleep( 10 );
		for( it = pIOCPServer->m_mapHandlers.begin(); it != pIOCPServer->m_mapHandlers.end(); ++it ) {
			it->second->ProcessSend();
		}
	}

	pthread_exit(0);
}

NetworkServer::NetworkServer()
{
	m_bShutdown				= FALSE;
	m_hSendThread			= 0;
}

NetworkServer::~NetworkServer()
{
	if( !m_bShutdown ) {
		Shutdown();
	}
}

BOOL NetworkServer::Init( LPSYNCHANDLER_DESC lpDesc, DWORD dwNumberofIoHandlers )
{
	for( DWORD i = 0; i < dwNumberofIoHandlers; ++i ) {
		CreateSyncHandler( lpDesc + i );
	}

	pthread_create( &m_hSendThread, NULL, send_thread, (void*)this);
	return TRUE;
}

void NetworkServer::CreateSyncHandler( LPSYNCHANDLER_DESC lpDesc )
{
	NetworkSyncHandler *pSync = new NetworkSyncHandler;
	pSync->Init( this, lpDesc );
	m_mapHandlers.insert( SYNCHANDLER_MAP_PAIR( pSync->GetKey(), pSync ) );
}


void NetworkServer::Shutdown()
{
	m_bShutdown = TRUE;
	pthread_join(m_hSendThread, NULL);    

	SYNCHANDLER_MAP_ITER	it;
	NetworkSyncHandler		*pSync;

	for( it = m_mapHandlers.begin(); it != m_mapHandlers.end(); ++it ) {
		pSync = it->second;
		pSync->Shutdown();
		delete pSync;
		
	}
	m_mapHandlers.clear();
}

void NetworkServer::Update()
{
	SYNCHANDLER_MAP_ITER it;
	for( it = m_mapHandlers.begin(); it != m_mapHandlers.end(); ++it ) {
		it->second->Update();
	}
}

BOOL NetworkServer::StartListen( DWORD dwHandlerKey, const char *pIP, WORD wPort )
{
	SYNCHANDLER_MAP_ITER it = m_mapHandlers.find( dwHandlerKey );
	assert( it != m_mapHandlers.end() );
	return it->second->StartListen( pIP, wPort );
}

DWORD NetworkServer::Connect( DWORD dwHandlerKey, NetworkObject *pNetworkObject, char *pszIP, WORD wPort )
{
	if( pNetworkObject == NULL ) {
		return 0;
	}
	SYNCHANDLER_MAP_ITER it = m_mapHandlers.find( dwHandlerKey );
	assert( it != m_mapHandlers.end() );
	return it->second->Connect( pNetworkObject, pszIP, wPort );
}

BOOL NetworkServer::IsListening( DWORD dwHandlerKey )
{
	SYNCHANDLER_MAP_ITER it = m_mapHandlers.find( dwHandlerKey );
	assert( it != m_mapHandlers.end() );
	return it->second->IsListening();
}

DWORD NetworkServer::GetNumberOfConnections( DWORD dwHandlerKey )
{
	SYNCHANDLER_MAP_ITER it = m_mapHandlers.find( dwHandlerKey );
	assert( it != m_mapHandlers.end() );
	return it->second->GetNumberOfConnections();
}
