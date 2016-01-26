#ifndef _TemplateDBSession_H_
#define _TemplateDBSession_H_
#include <CommonInclude.h>

class TemplateDBSession : public TemplateServerSession
{
public:
	TemplateDBSession();
	virtual ~TemplateDBSession();

public:
	virtual void    Clear();
	virtual void	OnRecv(BYTE *pMsg, WORD wSize);
	virtual void	OnConnect( BOOL bSuccess, DWORD dwNetworkIndex );
	virtual void    OnDisconnect();
	virtual void	OnLogString( char * pszLog);
};

#endif // _AGENTPLAYER_H_INCLUDED_
