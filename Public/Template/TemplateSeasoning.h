#ifndef _TemplateSeasoning_H_
#define _TemplateSeasoning_H_
#include <UtilityDefine.h>

class TemplateSeasoning
{
public:
	TemplateSeasoning();
	virtual ~TemplateSeasoning();

public:
	static void Init();
	static void Release();

public:
	BYTE & GetClientSandHead();
	BYTE & GetClientRecvHead();
	BYTE & GetOpenDatabase();

    CHAR * GetDBAddress();
    CHAR * GetDBName();
	CHAR * GetDBUsername();
	CHAR * GetDBPassword();

private:
	static BYTE m_bClientSandHead;//指定与客户发送有无带头
	static BYTE m_bClientRecvHead;//指定与客户接收有无带头
	static BYTE m_bOpenDatabase;//是否打开数据库

private: //指定全局数据库参数
	static CHAR m_szDBAddress[16];
	static CHAR m_szDBName[32];
	static CHAR m_szDBUsername[32];
    static CHAR m_szDBPasswork[32];
};

#endif // _AGENTPLAYER_H_INCLUDED_
