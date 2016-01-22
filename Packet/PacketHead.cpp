#include "HeadPacket.h"

HeadPacket::HeadPacket()
{
}

HeadPacket::~HeadPacket()
{
}

void HeadPacket::ToInit()   {   memset( this, 0x0, sizeof(HeadPacket) );  }  // ����

void HeadPacket::SetPacket
(BYTE * byData, WORD wSize) {   memcpy( this, byData, wSize );      }  // ���ð��ṹ


UINT & HeadPacket::GetProtocol()        {  return (m_uiProtocol);   }       // ȡ�ú�����Э���;
UINT & HeadPacket::GetTokenKey()        {  return (m_uiTokenKey);   }       // ��ȫ��;
UINT & HeadPacket::GetValidTime()       {  return (m_uiValidTime);  }       // ȡ����Чʱ��;
UINT & HeadPacket::GetValidCount()      {  return (m_uiValidCount); }       // ��Чʹ�ô���;
UINT & HeadPacket::GetPortKey()         {  return (m_uiPortKey);    }       // �˿ں�
UINT & HeadPacket::GetAgentKey()        {  return (m_uiAgentKey);   }       // ���������

void HeadPacket::ToPrint()
{
    DEBUG_MSG( LVL_DEBUG, "Begin");

    DEBUG_MSG( LVL_DEBUG, "| Protocol=%d | TokenKey=%d | ValidTime=%d | ValidCount=%d | PortKey=%d | AgentKey=%d |",
              m_uiProtocol, m_uiTokenKey, m_uiValidTime, m_uiValidCount, m_uiPortKey, m_uiAgentKey );

    DEBUG_MSG( LVL_DEBUG, "End\n");
}



