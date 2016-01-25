#include "NetworkInclude.h"

void* send_thread( void* param )
{
	NetworkIOCPServer *pIOCPServer = (NetworkIOCPServer*)param;
	
	SYNCHANDLER_MAP_ITER	it;
	while( !pIOCPServer->m_bShutdown ) {
		Sleep( 10 );
		for( it = pIOCPServer->m_mapHandlers.begin(); it != pIOCPServer->m_mapHandlers.end(); ++it ) {
			it->second->ProcessSend();
		}
	}

	pthread_exit(0);
}

NetworkIOCPServer::NetworkIOCPServer()
{
	m_bShutdown				= FALSE;
	m_hSendThread			= 0;
}

NetworkIOCPServer::~NetworkIOCPServer()
{
	if( !m_bShutdown ) {
		Shutdown();
	}
}

BOOL NetworkIOCPServer::Init( LPSYNCHANDLER_DESC lpDesc, DWORD dwNumberofIoHandlers )
{
	for( DWORD i = 0; i < dwNumberofIoHandlers; ++i ) {
		CreateSyncHandler( lpDesc + i );
	}

	pthread_create( &m_hSendThread, NULL, send_thread, (void*)this);
	return TRUE;
}

void NetworkIOCPServer::CreateSyncHandler( LPSYNCHANDLER_DESC lpDesc )
{
	NetworkSyncHandler *pSync = new NetworkSyncHandler;
	pSync->Init( this, lpDesc );
	m_mapHandlers.insert( SYNCHANDLER_MAP_PAIR( pSync->GetKey(), pSync ) );
}


void NetworkIOCPServer::Shutdown()
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

void NetworkIOCPServer::Update()
{
	SYNCHANDLER_MAP_ITER it;
	for( it = m_mapHandlers.begin(); it != m_mapHandlers.end(); ++it ) {
		it->second->Update();
	}
}

BOOL NetworkIOCPServer::StartListen( DWORD dwHandlerKey, const char *pIP, WORD wPort )
{
	SYNCHANDLER_MAP_ITER it = m_mapHandlers.find( dwHandlerKey );
	assert( it != m_mapHandlers.end() );
	return it->second->StartListen( pIP, wPort );
}

DWORD NetworkIOCPServer::Connect( DWORD dwHandlerKey, NetworkObject *pNetworkObject, char *pszIP, WORD wPort )
{
	if( pNetworkObject == NULL ) {
		return 0;
	}
	SYNCHANDLER_MAP_ITER it = m_mapHandlers.find( dwHandlerKey );
	assert( it != m_mapHandlers.end() );
	return it->second->Connect( pNetworkObject, pszIP, wPort );
}

BOOL NetworkIOCPServer::IsListening( DWORD dwHandlerKey )
{
	SYNCHANDLER_MAP_ITER it = m_mapHandlers.find( dwHandlerKey );
	assert( it != m_mapHandlers.end() );
	return it->second->IsListening();
}

DWORD NetworkIOCPServer::GetNumberOfConnections( DWORD dwHandlerKey )
{
	SYNCHANDLER_MAP_ITER it = m_mapHandlers.find( dwHandlerKey );
	assert( it != m_mapHandlers.end() );
	return it->second->GetNumberOfConnections();
}
