#ifndef _NetworkObject_H_
#define _NetworkObject_H_
#include <NetworkDefine.h>
class NetworkSession;

class NetworkObject
{
	friend class NetworkSession;
	friend class NetworkSyncHandler;

public:
	NetworkObject();
	virtual ~NetworkObject();

	void			Disconnect( BOOL bGracefulDisconnect = TRUE );
	BOOL			Send( BYTE *pMsg, WORD wSize );
	BOOL			SendEx( DWORD dwNumberOfMessages, BYTE **ppMsg, WORD *pwSize );
	void			Redirect( NetworkObject *pNetworkObject );

//	SOCKADDR_IN*	GetSockAddr();


	//WORD 			GetPort();	// PORT
	std::string		GetIP();
	NetworkSession *GetSesstion();

	void            NotSendHeader() { m_bSendHander = FALSE; }   // default TRUE;
	BOOL 			hasSendHeader() { return m_bSendHander; }

	void            NotRecvHeader() { m_bRecvHander = FALSE; }   // default TRUE;
	BOOL 			hasRecvHeader() { return m_bRecvHander; }

protected:

	virtual void	OnAccept( DWORD dwNetworkIndex ) {}
	virtual void	OnDisconnect() {};
	virtual	void	OnRecv( BYTE *pMsg, WORD wSize ) = 0;
	virtual void	OnConnect( BOOL bSuccess, DWORD dwNetworkIndex ) {}
	virtual void	OnLogString( char *pszLog ) {}

	inline void		SetSession( NetworkSession *pSession ) { m_pSession = pSession; }

	NetworkSession *m_pSession;

	BOOL			m_bSendHander;
	BOOL			m_bRecvHander;
};

#endif


