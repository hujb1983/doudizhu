#include "UserPacket.h"

UserPacket::UserPacket()
{
}

UserPacket::~UserPacket()
{
}

UINT UserPacket::GetTickCount() {  // ʱ��
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec;
}

void UserPacket::ToInit()   {   memset( this, 0x0, sizeof(UserPacket) );  }  // ����

void UserPacket::SetPacket
(BYTE * byData, WORD wSize) {   memcpy( this, byData, wSize );      }  // ���ð��ṹ

BYTE * UserPacket::GetPacket(BYTE * _data, WORD _size )   {  // ��һ��ָ�벢���ͷָ��;
    memcpy(_data, this, sizeof(UserPacket) );
    return _data;
}
WORD   UserPacket::GetPacketSize() {   // ȡ�������ָ��;
    return sizeof(UserPacket);
}

UINT & UserPacket::GetProtocol()        {  return (m_uiProtocol);   }       // ȡ�ú�����Э���;
UINT & UserPacket::GetTokenKey()        {  return (m_uiTokenKey);   }       // ��ȫ��;
UINT & UserPacket::GetValidTime()       {  return (m_uiValidTime);  }       // ȡ����Чʱ��;
UINT & UserPacket::GetValidCount()      {  return (m_uiValidCount); }       // ��Чʹ�ô���;
UINT & UserPacket::GetPortKey()         {  return (m_uiPortKey);    }       // �˿ں�
UINT & UserPacket::GetAgentKey()        {  return (m_uiAgentKey);   }       // ���������

UINT & UserPacket::GetLoginTime()       {  return (m_uiLogin);      }       // ��¼ʱ��;
BYTE * UserPacket::GetSSHKey()          {  return (m_szSSHKey);     }      // ��¼Key;
UINT & UserPacket::GetUserId()          {  return (m_uiUserId);     }       // �û���Id;
UINT & UserPacket::GetUserKey()         {  return (m_uiPortKey);    }       // �û���Id;
UINT & UserPacket::GetOldKey()          {  return (m_uiOldPortKey); }       // �û���ǰ�õ�Key;
CHAR * UserPacket::GetName()            {  return (m_szName);       }       // ȡ����Чʱ��;
INT  & UserPacket::GetMoney()           {  return (m_iMoney);       }       // �Ƹ�;
UINT & UserPacket::GetWoneds()          {  return (m_uiWoneds);     }       // Ӯ�Ĵ���;
UINT & UserPacket::GetFaileds()         {  return (m_uiFaileds);    }       // ʧ�ܵĴ���;
UINT & UserPacket::GetAways()           {  return (m_uiAways);      }       // �뿪�Ĵ���;

WORD & UserPacket::GetBattleId()        {  return (m_wBattleId);    }       // ս������;
BYTE & UserPacket::GetFieldId()         {  return (m_byFieldId);    }       // ���κ�;
BYTE & UserPacket::GetRoomId()          {  return (m_byRoomId);     }       // �����;
UINT & UserPacket::GetTableId()         {  return (m_uiTableId);    }       // ���Ӻ�;
BYTE & UserPacket::GetSeatId()          {  return (m_bySeatId);     }       // ��λ��;

BYTE & UserPacket::GetReady()           {  return (m_byReady);          }       // �Ƿ�׼����;
BYTE & UserPacket::GetCalled()          {  return (m_byCalled);         }       // �Ƿ�е���;
UINT & UserPacket::GetCalledTimes()     {  return (m_uiCallTimes);      }       // �е�������Ȩʱ��;
UINT & UserPacket::GetCalledTimesLast() {  return (m_uiCallTimesLast);  }       // �е���������ʱ��;
BYTE & UserPacket::GetBanker()          {  return (m_byBanker);         }       // �Ƿ����;

BYTE & UserPacket::GetCount()           {  return (m_byCount);      }           // ������;
BYTE * UserPacket::GetPokers()          {  return (m_byPokers);     }           // ���ϵ���;

UINT & UserPacket::GetShowTimes()       {  return (m_uiShowTimes);      }       // ����ʱ��;
UINT & UserPacket::GetShowTimesLast()   {  return (m_uiShowTimesLast);  }       // ����ʱ��;
BYTE & UserPacket::GetShowMan()         {  return (m_byShowMan);        }       // ������;
BYTE * UserPacket::GetShowPokers()      {  return (m_byShowPokers);     }       // �������;

UINT & UserPacket::GetShowedSize()      {  return (m_uiShowedCount);   }        // �Ƿ����;
CHAR * UserPacket::GetShowedPokers()    {  return (m_byShowedPokers);  }        // �Ѿ��������;

CHAR * UserPacket::GetReminderPokers()  {  return (m_szReminderPokers); }        // ������ʾ;
BYTE & UserPacket::GetReminderSize()    {  return (m_byReminderSize);   }        // ���ƴ�С;

void UserPacket::ToPrint()
{
    DEBUG_MSG( LVL_DEBUG, "Begin");

    DEBUG_MSG( LVL_DEBUG, "| Protocol=%d | TokenKey=%d | ValidTime=%d | ValidCount=%d | PortKey=%d | AgentKey=%d |",
              m_uiProtocol, m_uiTokenKey, m_uiValidTime, m_uiValidCount, m_uiPortKey, m_uiAgentKey );

    DEBUG_MSG( LVL_DEBUG, "| LoginTime=%d |", m_uiLogin);

    DEBUG_MSG( LVL_DEBUG, "| UserId=%d | Name=%s | Money=%d | Woneds=%d | Faileds=%d | Aways=%d |",
              m_uiUserId, m_szName, m_iMoney, m_uiWoneds, m_uiFaileds, m_uiAways );

    DEBUG_MSG( LVL_DEBUG, "| BattleId=%d | FieldId=%d | RoomId=%d | TableId=%d |  SeatId=%d |",
              m_wBattleId, m_byFieldId, m_byRoomId, m_uiTableId, m_bySeatId );

    DEBUG_MSG( LVL_DEBUG, "| Ready=%d | Called=%d | Banker=%d |",
              m_byReady, m_byCalled, m_byBanker );

    DEBUG_MSG( LVL_DEBUG, "| ReminderSize=%d | ReminderPokers=%s |",
               m_byReminderSize, m_szReminderPokers );

    DEBUG_MSG( LVL_DEBUG, "End\n");
}



