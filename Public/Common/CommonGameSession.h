#ifndef _CommonGameSession_H_
#define _CommonGameSession_H_
#include "CommonDefine.h"
#include "CommonServerSession.h"

class CommonGameSession : public CommonServerSession
{
public:
	CommonGameSession();
	virtual ~CommonGameSession();

public:
	virtual void    Clear();
	virtual void	OnRecv(BYTE *pMsg, WORD wSize);
	virtual void	OnConnect( BOOL bSuccess, DWORD dwNetworkIndex );
	virtual void    OnDisconnect();
	virtual void	OnLogString( char * pszLog);
};

#endif // _AGENTPLAYER_H_INCLUDED_
