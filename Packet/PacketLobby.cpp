#include "LobbyPacket.h"

LobbyPacket::LobbyPacket()
{
}

LobbyPacket::~LobbyPacket()
{
}

void LobbyPacket::ToInit()   {   memset( this, 0x0, sizeof(this) );  }  // ����
void LobbyPacket::SetPacket (BYTE * byData, WORD wSize){
    memcpy( this, byData, wSize );
}
BYTE * LobbyPacket::GetPacket(BYTE * _data, WORD _size )   {  // ��һ��ָ�벢���ͷָ��;
    memcpy( _data, this, sizeof(this) );
    return _data;
}
WORD   LobbyPacket::GetPacketSize() {   // ȡ�������ָ��;
    return sizeof(this);
}

UINT & LobbyPacket::GetProtocol()       {  return (m_uiProtocol);   }      // ȡ�ú�����Э���;
UINT & LobbyPacket::GetTokenKey()       {  return (m_uiTokenKey);   }      // ��ȫ��;
UINT & LobbyPacket::GetValidTime()      {  return (m_uiValidTime);  }      // ȡ����Чʱ��;
UINT & LobbyPacket::GetValidCount()     {  return (m_uiValidCount); }      // ��Чʹ�ô���;
UINT & LobbyPacket::GetPortkey()        {  return (m_uiPortkey);    }      // �˿ں�
UINT & LobbyPacket::GetAgentkey()       {  return (m_uiAgentkey);   }      // ���������

// ��������
UINT & LobbyPacket::GetOnlines()        {  return (m_uiOnlines);    }      // ��������������

// ���εĸ���
// ���ε�ƫ��
// ���ε�ָ��
UINT & LobbyPacket::GetFieldSize()      {  return (m_sFieldSize);   }
UINT & LobbyPacket::GetFieldOffset()    {  return (m_sFieldOffset); }
BYTE * LobbyPacket::GetFields()         {
    if ( m_pData ) {
        return (m_pData + m_sFieldOffset);
    }
    return (NULL);
}

// ����ĸ���
// �����ƫ��
// �����ָ��
UINT & LobbyPacket::GetRoomSize()       {  return (m_sRoomSize);    }
UINT & LobbyPacket::GetRoomOffset()     {  return (m_sRoomsOffset); }
BYTE * LobbyPacket::GetRooms()          {
    if ( m_pData ) {
        return (m_pData + m_sRoomsOffset);
    }
    return (NULL);
}

// �ܱ��ĸ���
// �ܱ���ƫ��
// �ܱ���ָ��
UINT & LobbyPacket::GetWeekRankSize()       {  return (m_sWeekRankSize);    }
UINT & LobbyPacket::GetWeekRankOffset()     {  return (m_sWeekRankOffset);  }
BYTE * LobbyPacket::GetWeekRanks()          {
    if ( m_pData ) {
        return (m_pData + m_sWeekRankOffset);
    }
    return (NULL);
}

// �ռ�ĸ���
// �ռ��ƫ��
// �ռ��ָ��
UINT & LobbyPacket::GetDayRankSize()       {  return (m_sDayRankSize);      }
UINT & LobbyPacket::GetDayRankOffset()     {  return (m_sDayRankOffset);    }
BYTE * LobbyPacket::GetDayRanks()          {
    if ( m_pData ) {
        return (m_pData + m_sDayRankOffset);
    }
    return (NULL);
}

// ���ݰ�
UINT & LobbyPacket::GetDataSize()           { return (m_pDataSize);         }
BYTE * LobbyPacket::GetData()               { return (m_pData);             }

// ��ӡ���в���
void LobbyPacket::ToPrint()
{

}



