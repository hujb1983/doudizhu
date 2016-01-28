#ifndef _CommonConnect_H_
#define _CommonConnect_H_
#include "CommonProtocolConnect.h"

struct MSG_ENTERSERVER_SYN : public MSG_BASE
{
	char EnterType[4];
	MSG_ENTERSERVER_SYN()
	{
		memset( this, 0, sizeof(MSG_ENTERSERVER_SYN) );
		m_byCategory = Connect_Protocol;
		m_byProtocol = ClientType_SYN;
	}
};

struct MSG_ENTERSERVER_ANC : public MSG_BASE
{
	MSG_ENTERSERVER_ANC()
	{
		memset( this, 0, sizeof(MSG_ENTERSERVER_ANC) );
		m_byCategory = Connect_Protocol;
		m_byProtocol = ClientType_ANC + 1;      // 区分登录服务器
	}
};

struct MSG_CONNECTION_SYN : public MSG_BASE
{
	BYTE ServerType;
	MSG_CONNECTION_SYN()
	{
		memset( this, 0, sizeof(MSG_CONNECTION_SYN) );
		m_byCategory = Connect_Protocol;
		m_byProtocol = ServerType_SYN;
	}
};

struct MSG_HEARTBEAT_SYN : public MSG_BASE
{
	BYTE ServerType;	   // 四种访问格式
	MSG_HEARTBEAT_SYN()
	{
		memset( this, 0, sizeof(MSG_HEARTBEAT_SYN) );
		m_byCategory = Connect_Protocol;
		m_byProtocol = Heartbeat_SYN;
	}
};

#endif // _PACKAGESTRUCTCONNECT_H_INCLUDED_