#ifndef _TemplateUserSession_H_
#define _TemplateUserSession_H_
#include <CommonInclude.h>

class TemplateUserSession : public TemplateServerSession
{
public:
	TemplateUserSession();
	virtual ~TemplateUserSession();

public:
	virtual void    Clear();
	virtual void	OnRecv(BYTE *pMsg, WORD wSize);
	virtual void	OnConnect( BOOL bSuccess, DWORD dwNetworkIndex );
	virtual void    OnDisconnect();
	virtual void	OnLogString( char * pszLog);
};

#endif // _AGENTPLAYER_H_INCLUDED_
