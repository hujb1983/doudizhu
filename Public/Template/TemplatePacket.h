#ifndef _TemplatePacket_H_
#define _TemplatePacket_H_

#include <UtilityDefine.h>
#include <UtilityInclude.h>

#pragma pack(push,1)
class TemplatePacket
{
public:
    static UINT GetTickCount();     // 时间

public:
	TemplatePacket();
	~TemplatePacket();

    virtual void ToInit();                  // 初始化
    virtual void ToPrint();                 // 打印
    virtual void SetPacket(BYTE *, WORD );  // 设置包结构

public:
    UINT & GetProtocol();       // 取得和设置协议号;
    UINT & GetTokenKey();       // 安全码;
    UINT & GetValidTime();      // 取得有效时间;
    UINT & GetValidCount();     // 有效使用次数;
    UINT & GetClientKey();      // 端口号
    UINT & GetAgentKey();       // 代理服务器
	UINT & GetUserKey();        // 玩家键值

private:
    UINT  m_uiProtocol;         // 协议;
    UINT  m_uiTokenKey;         // 生成的返回锁;
    UINT  m_uiValidTime;        // 有效时间限制;
    UINT  m_uiValidCount;       // 有效访问记数;
    UINT  m_uiClientKey;        // 入口键值;
    UINT  m_uiAgentKey;         // 代理键值;
	UINT  m_uiUserKey;          // 入口键值;
	
};
#pragma pack(pop)

#endif // _TemplatePacket_H_
