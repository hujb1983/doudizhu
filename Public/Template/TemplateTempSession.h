#ifndef _TemplateTempSession_H_
#define _TemplateTempSession_H_
#include <CommonInclude.h>

class TemplateTempSession : public TemplateServerSession
{
public:
	TemplateTempSession();
	virtual ~TemplateTempSession();

public:
	virtual void    Clear();
	virtual void	OnRecv(BYTE *pMsg, WORD wSize);
	virtual void	OnConnect( BOOL bSuccess, DWORD dwNetworkIndex );
	virtual void    OnDisconnect();
	virtual void	OnLogString( char * pszLog);
};

#endif // _AGENTPLAYER_H_INCLUDED_
