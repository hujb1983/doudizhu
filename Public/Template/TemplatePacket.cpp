#include "TemplatePacket.h"

TemplatePacket::TemplatePacket()
{
}

TemplatePacket::~TemplatePacket()
{
}

void TemplatePacket::ToInit()   {   memset( this, 0x0, sizeof(TemplatePacket) );  }  // 清理

void TemplatePacket::SetPacket
(BYTE * byData, WORD wSize) {   memcpy( this, byData, wSize );      }  // 设置包结构

UINT & TemplatePacket::GetProtocol()        {  return (m_uiProtocol);   }       // 取得和设置协议号;
UINT & TemplatePacket::GetTokenKey()        {  return (m_uiTokenKey);   }       // 安全码;
UINT & TemplatePacket::GetValidTime()       {  return (m_uiValidTime);  }       // 取得有效时间;
UINT & TemplatePacket::GetValidCount()      {  return (m_uiValidCount); }       // 有效使用次数;
UINT & TemplatePacket::GetClientKey()       {  return (m_uiClientKey);  }       // 端口号
UINT & TemplatePacket::GetAgentKey()        {  return (m_uiAgentKey);   }       // 代理服务器
UINT & TemplatePacket::GetUserKey()         {  return (m_uiUserKey);    }       // 代理服务器

void TemplatePacket::ToPrint()
{
    DEBUG_MSG( LVL_DEBUG, "Begin");

    DEBUG_MSG( LVL_DEBUG, "| Protocol=%d | TokenKey=%d | ValidTime=%d | ValidCount=%d | PortKey=%d | AgentKey=%d |",
              m_uiProtocol, m_uiTokenKey, m_uiValidTime, m_uiValidCount, m_uiClientKey, m_uiAgentKey );

    DEBUG_MSG( LVL_DEBUG, "End\n");
}



