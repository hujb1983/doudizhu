#ifndef _TemplateServerSession_H_
#define _TemplateServerSession_H_
#include <CommonInclude.h>

class TemplateServerSession : public NetworkObject
{
public:
	TemplateServerSession();
	virtual ~TemplateServerSession();

	virtual void    Init();
	virtual void	Clear();
	virtual void    Update();
	virtual void    Release();

	virtual void	OnAccept( DWORD dwNetworkIndex );
	virtual void	OnConnect( BOOL bSuccess, DWORD dwNetworkIndex );
	virtual void	OnDisconnect();
	virtual void	OnRecv(BYTE *pMsg, WORD wSize);

	virtual void	OnLogString( char * pszLog);

	void SetServerType(eSERVER_TYPE byType) { m_byServerType = byType; }
	virtual eSERVER_TYPE GetServerType() { return m_byServerType; }

	DWORD GetSessionIndex() { return m_dwSessionIndex; }
	void  SetSessionIndex( DWORD dwIdx) { m_dwSessionIndex = dwIdx; }

	void SendServerType();
	void SetAddr( char * pszIP, WORD wPort );
	BOOL TryToConnect();

	inline std::string GetConnnectIP() { return m_strConnectIP; }
	inline WORD  	   GetConnnectPort() { return m_wConnectPort; }

	inline BOOL IsConnected() { return m_bConnection; }
	inline void SetForConnect(BOOL bForConnect)	{ m_bForConnect = bForConnect; }
	inline bool IsForConnect() { return m_bForConnect; }

	// 数据库 --
    void          DBQuery ( Query * pQuery );
    virtual void  DBResult( WORD cate, WORD ptcl, MydbcQueryResult * pData ){}

public:
    eSERVER_TYPE m_byServerType;
	DWORD m_dwSessionIndex;
	std::string m_strConnectIP;
	WORD  m_wConnectPort;
	BOOL  m_bForConnect;
	DWORD m_dwLastHeartbeatTime;
	DWORD m_bConnection;
};

#endif // _AGENTPLAYER_H_INCLUDED_
