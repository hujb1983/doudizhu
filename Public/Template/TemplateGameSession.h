#ifndef _TemplateGameSession_H_
#define _TemplateGameSession_H_
#include <CommonInclude.h>

class TemplateGameSession : public TemplateServerSession
{
public:
	TemplateGameSession();
	virtual ~TemplateGameSession();

public:
	virtual void    Clear();
	virtual void	OnRecv(BYTE *pMsg, WORD wSize);
	virtual void	OnConnect( BOOL bSuccess, DWORD dwNetworkIndex );
	virtual void    OnDisconnect();
	virtual void	OnLogString( char * pszLog);
};

#endif // _AGENTPLAYER_H_INCLUDED_
