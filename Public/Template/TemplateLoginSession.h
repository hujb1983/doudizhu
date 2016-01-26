#ifndef _TemplateLoginSession_H_
#define _TemplateLoginSession_H_
#include <CommonInclude.h>

class TemplateLoginSession : public TemplateServerSession
{
public:
	TemplateLoginSession();
	virtual ~TemplateLoginSession();

public:
	virtual void    Clear();
	virtual void	OnRecv(BYTE *pMsg, WORD wSize);
	virtual void	OnConnect( BOOL bSuccess, DWORD dwNetworkIndex );
	virtual void    OnDisconnect();
	virtual void	OnLogString( char * pszLog);
};

#endif // _AGENTPLAYER_H_INCLUDED_
