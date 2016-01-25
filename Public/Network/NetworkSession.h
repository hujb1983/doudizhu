#ifndef _NetworkSession_H_
#define _NetworkSession_H_
#include <NetworkDefine.h>

class NetworkSyncHandler;
class NetworkObject;

class NetworkSession : public LinkD_T<NetworkSession>
{
	friend void * io_thread( void * param);
	friend class NetworkSessionPool;	
	
public:
	NetworkSession(DWORD dwSendBufferSize, DWORD dwRecvBufferSize, DWORD dwMaxPacketSize, DWORD dwTimeOut);
	virtual ~NetworkSession();
	
	void 			Init();
	BOOL			Send( BYTE * pMsg, WORD wSize);
	BOOL			SendEx( DWORD dwNumberOfMessages, BYTE ** pMsg, WORD *pwSize);
	BOOL    		OnSend();
	BOOL    		DoSend( NetworkSyncHandler * pSync );
	BOOL    		DoRecv();
	BOOL    		PreSend( NetworkSyncHandler * pSync );
	SOCKET 			CreateSocket();
	BOOL			ProcessRecvdPacket( DWORD dwMaxPacketSize);
	void			BindNetworkObject( NetworkObject * pObjs);
	void 			UnbindNetworkObject();
	void 			OnAccept();
	void 			OnConnect( BOOL bSuccess );
	void 			OnLogString( char * pszLog, ...);
	
	inline void 	SetSocket ( SOCKET socket ) { m_socket = socket; }
	inline void 	SetSockAddr ( SOCKADDR_IN & sockaddr) { m_sockaddr = sockaddr; }
	//inline void 	CloseSocket() { SocketOpt::CloseSocket(m_socket); m_socket = INVALID_SOCKET; }
	void CloseSocket();	

	inline 
	NetworkObject * GetNetworkObject() { return m_pNetworkObject; }
	inline 
	NetworkSendBuffer * GetSendBuffer() { return m_pSendBuffer; }
	inline 
	NetworkRecvBuffer * GetRecvBuffer() { return m_pRecvBuffer; }
	
	inline SOCKET	GetSocket() {return m_socket; }
	inline 
	SOCKADDR_IN   *	GetSockAddr() {return &m_sockaddr; }
	
	inline
	std::string   	GetIP()	{	return inet_ntoa( m_sockaddr.sin_addr); }
	
	inline DWORD	GetIdleTick() const {	return m_dwTimeOut? m_dwLastSyncTick + m_dwTimeOut : 0; }
	inline BOOL     IsOnIdle()	{	return m_dwTimeOut? m_dwLastSyncTick + m_dwTimeOut < NetworkSession::GetTickCount() : FALSE; }
	inline DWORD	GetIndex()	{	return m_dwIndex; }
	inline BOOL 	IsAcceptSocket()	{	return m_bAcceptSocket; }

	inline BOOL 	SetAcceptSocketFlag()	{	m_bAcceptSocket = TRUE; }
	void			Remove()	{ __sync_fetch_and_or(&m_bRemove, 1); }
	inline void		ResetKillFlag()	{ __sync_fetch_and_add(&m_bRemove, 0); }

	inline BOOL		ShouldBeRemoved() {	return m_bRemove; }
	void 			Disconnect( BOOL bGracefulDisconnect );
	inline BOOL		HasDisconnectOrdered() {	return m_bDisconnectOrdered;	}
	
	UINT64 m_dwTotalRecvBytes;
	UINT64 m_dwTotalSendBytes;
	
	static DWORD GetTickCount();
	
private:
	void 			SetIndex (DWORD index) {	m_dwIndex = index; }
	inline void 	ResetTimeOut()	{	m_dwLastSyncTick = NetworkSession::GetTickCount();	}
	
	NetworkObject 	  * m_pNetworkObject;
	NetworkSendBuffer * m_pSendBuffer;
	NetworkRecvBuffer * m_pRecvBuffer;
	
	SOCKET			m_socket;
	SOCKADDR_IN		m_sockaddr;
	
	DWORD			m_dwLastSyncTick;
	volatile int 	m_bRemove;
	DWORD			m_dwTimeOut;
	DWORD			m_dwIndex;
	BOOL			m_bAcceptSocket;
	BOOL			m_bDisconnectOrdered;
	
	//
	int 			m_iCategory;
	int 			m_iProtocol;
	int 			m_iSize;

protected:
	UtilityMutex 	m_lockRecv;
	UtilityMutex 	m_lockSend;
	BOOL 			m_bCanSend;
};

#endif
	
 
