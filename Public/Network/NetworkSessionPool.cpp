#include <NetworkInclude.h>

//=============================================================================================================================
/**
	@remarks
	@param	nSize
*/
//=============================================================================================================================
NetworkSessionPool::NetworkSessionPool( DWORD dwSize,
						  DWORD dwSendBufferSize,
						  DWORD dwRecvBufferSize, 
						  DWORD dwMaxPacketSize,
						  DWORD dwTimeOutTick,
						  DWORD dwIndexStart,
						  BOOL bAcceptSocket )
{
	m_pList = NULL;
	Create( dwSize, dwSendBufferSize, dwRecvBufferSize, dwMaxPacketSize, dwTimeOutTick, dwIndexStart, bAcceptSocket );
}

//=============================================================================================================================
/**
	@remarks
*/
//=============================================================================================================================
NetworkSessionPool::~NetworkSessionPool()
{
	if( m_pList ) delete m_pList;
}

//=============================================================================================================================
/**
	@remarks
	@param	dwSize
*/
//=============================================================================================================================
void NetworkSessionPool::Create( DWORD dwSize, DWORD dwSendBufferSize, DWORD dwRecvBufferSize, DWORD dwMaxPacketSize, DWORD dwTimeOutTick, DWORD dwIndexStart, BOOL bAcceptSocket )
{
	m_dwMaxSize			= dwSize;

	m_pList = new NetworkSessionList;

	NetworkSession *pSession;

	for( DWORD i = 0; i < dwSize; ++i )
	{
		pSession = new NetworkSession( dwSendBufferSize, dwRecvBufferSize, dwMaxPacketSize, dwTimeOutTick );

		pSession->SetIndex( dwIndexStart + i );

		if( bAcceptSocket )
		{
			pSession->SetAcceptSocketFlag();
		}

		m_pList->push_back( pSession );
	}
}

//=============================================================================================================================
/**
	@remarks
	@retval	Session*
*/
//=============================================================================================================================
NetworkSession* NetworkSessionPool::Alloc()
{
	m_pList->Lock();

	if( m_pList->empty() )
	{
		m_pList->Unlock();
		
		return NULL;
	}

	NetworkSession *pSession = m_pList->front();
	m_pList->pop_front();

	//printf( "New (%x) (%d)\n", this, m_pList->size() ); 

	m_pList->Unlock();

	return pSession; 
}

//=============================================================================================================================
/**
	@remarks
	@param	pSession
*/
//=============================================================================================================================
void NetworkSessionPool::Free( NetworkSession* pSession )
{
	m_pList->Lock();

	assert( m_pList->size() < m_dwMaxSize );

	m_pList->push_back( pSession );

	m_pList->Unlock();
}

//=============================================================================================================================
/**
	@remarks
	@retval	int
*/
//=============================================================================================================================
int NetworkSessionPool::GetLength()
{
	m_pList->Lock();

	int size = (int)( m_pList->size() );

	m_pList->Unlock();

	return size;
}
	
