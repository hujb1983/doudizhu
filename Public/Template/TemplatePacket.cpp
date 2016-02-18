#include "TemplatePacket.h"

TemplatePacket::TemplatePacket()
{
}

TemplatePacket::~TemplatePacket()
{
}

void TemplatePacket::ToInit()   {   memset( this, 0x0, sizeof(TemplatePacket) );  }  // ����

void TemplatePacket::SetPacket
(BYTE * byData, WORD wSize) {   memcpy( this, byData, wSize );      }  // ���ð��ṹ

UINT & TemplatePacket::GetProtocol()        {  return (m_uiProtocol);   }       // ȡ�ú�����Э���;
UINT & TemplatePacket::GetTokenKey()        {  return (m_uiTokenKey);   }       // ��ȫ��;
UINT & TemplatePacket::GetValidTime()       {  return (m_uiValidTime);  }       // ȡ����Чʱ��;
UINT & TemplatePacket::GetValidCount()      {  return (m_uiValidCount); }       // ��Чʹ�ô���;
UINT & TemplatePacket::GetClientKey()       {  return (m_uiClientKey);  }       // �˿ں�
UINT & TemplatePacket::GetAgentKey()        {  return (m_uiAgentKey);   }       // ���������
UINT & TemplatePacket::GetUserKey()         {  return (m_uiUserKey);    }       // ���������

void TemplatePacket::ToPrint()
{
    DEBUG_MSG( LVL_DEBUG, "Begin");

    DEBUG_MSG( LVL_DEBUG, "| Protocol=%d | TokenKey=%d | ValidTime=%d | ValidCount=%d | PortKey=%d | AgentKey=%d |",
              m_uiProtocol, m_uiTokenKey, m_uiValidTime, m_uiValidCount, m_uiClientKey, m_uiAgentKey );

    DEBUG_MSG( LVL_DEBUG, "End\n");
}



