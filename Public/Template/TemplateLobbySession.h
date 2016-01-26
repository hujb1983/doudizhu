#ifndef _TemplateLobbySession_H_
#define _TemplateLobbySession_H_
#include <CommonInclude.h>

class TemplateLobbySession : public TemplateServerSession
{
public:
	TemplateLobbySession();
	virtual ~TemplateLobbySession();

public:
	virtual void    Clear();
	virtual void	OnRecv(BYTE *pMsg, WORD wSize);
	virtual void	OnConnect( BOOL bSuccess, DWORD dwNetworkIndex );
	virtual void    OnDisconnect();
	virtual void	OnLogString( char * pszLog);
};

#endif // _AGENTPLAYER_H_INCLUDED_
