#ifndef _NetworkSessionPool_H_
#define _NetworkSessionPool_H_
class NetworkSessionList;

class NetworkSessionPool 
{
public:
	NetworkSessionPool( DWORD dwSize, DWORD dwSendBufferSize, DWORD dwRecvBufferSize, DWORD dwMaxPacketSize, DWORD dwTimeOutTick, DWORD dwIndexStart, BOOL bAcceptSocket );
	~NetworkSessionPool();

	NetworkSession* Alloc();
	void			Free( NetworkSession* pSession );
	int				GetLength();

private:
	void			Create( DWORD dwSize, DWORD dwSendBufferSize, DWORD dwRecvBufferSize, DWORD dwTimeOutTick, DWORD dwMaxPacketSize, DWORD dwIndexStart, BOOL bAcceptSocket );

	DWORD				m_dwMaxSize;
	NetworkSessionList *m_pList;
};

#endif
	
