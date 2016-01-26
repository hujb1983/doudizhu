#ifndef _CommonGameSession_H_
#define _CommonGameSession_H_
#include "CommonDefine.h"
#include "CommonServerSession.h"

class CommonLoginSession : public CommonServerSession
{
public:
	CommonLoginSession();
	virtual ~CommonLoginSession();

public:
	virtual void    Clear();
	virtual void	OnRecv(BYTE *pMsg, WORD wSize);
	virtual void	OnConnect( BOOL bSuccess, DWORD dwNetworkIndex );
	virtual void    OnDisconnect();
	virtual void	OnLogString( char * pszLog);
};

#endif // _AGENTPLAYER_H_INCLUDED_
