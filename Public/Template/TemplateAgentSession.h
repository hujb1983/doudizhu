#ifndef _TemplateAgentSession_H_
#define _TemplateAgentSession_H_
#include <CommonInclude.h>

class TemplateAgentSession : public TemplateServerSession
{
public:
	TemplateAgentSession();
	virtual ~TemplateAgentSession();

public:
	virtual void    Clear();
	virtual void	OnRecv(BYTE *pMsg, WORD wSize);
	virtual void	OnConnect( BOOL bSuccess, DWORD dwNetworkIndex );
	virtual void    OnDisconnect();
	virtual void	OnLogString( char * pszLog);
};

#endif // _AGENTPLAYER_H_INCLUDED_
