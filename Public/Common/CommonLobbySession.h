#ifndef _CommonLobbySession_H_
#define _CommonLobbySession_H_
#include "CommonDefine.h"
#include "CommonServerSession.h"

class CommonLobbySession : public CommonServerSession
{
public:
	CommonLobbySession();
	virtual ~CommonLobbySession();

public:
	virtual void    Clear();
	virtual void	OnRecv(BYTE *pMsg, WORD wSize);
	virtual void	OnConnect( BOOL bSuccess, DWORD dwNetworkIndex );
	virtual void    OnDisconnect();
	virtual void	OnLogString( char * pszLog);
};

#endif // _AGENTPLAYER_H_INCLUDED_
