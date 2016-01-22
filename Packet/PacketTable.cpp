#include "TablePacket.h"

TablePacket::TablePacket()
{
}

TablePacket::~TablePacket()
{
}

void TablePacket::ToInit() {      // ����
    memset( this, 0x0, sizeof(TablePacket) );
}

void TablePacket::SetPacket
(BYTE * byData, WORD wSize) {   memcpy( this, byData, wSize );      }  // ���ð��ṹ

BYTE * TablePacket::GetPacket(BYTE * _data, WORD _size )   {  // ��һ��ָ�벢���ͷָ��;
    memcpy(_data, this, sizeof(TablePacket) );
    return _data;
}
WORD   TablePacket::GetPacketSize() {   // ȡ�������ָ��;
    return sizeof(TablePacket);
}

UINT & TablePacket::GetProtocol()        {  return (m_uiProtocol);   }       // ȡ�ú�����Э���;
UINT & TablePacket::GetTokenKey()        {  return (m_uiTokenKey);   }       // ��ȫ��;
UINT & TablePacket::GetValidTime()       {  return (m_uiValidTime);  }       // ȡ����Чʱ��;
UINT & TablePacket::GetValidCount()      {  return (m_uiValidCount); }       // ��Чʹ�ô���;

BYTE & TablePacket::GetFieldId()         {  return (m_byFieldId);    }       // ���κ�;
BYTE & TablePacket::GetRoomId()          {  return (m_byRoomId);     }       // �����;
UINT & TablePacket::GetTableId()         {  return (m_uiTableId);    }       // ���Ӻ�;

BYTE & TablePacket::GetModel()           {  return (m_byModel);      }       // �����;
UINT & TablePacket::GetBasicMoney()      {  return (m_uiBasicMoney);   }      // ���Ӻ�;
UINT & TablePacket::GetMultiple()        {  return (m_uiMultiple);   }       // ���Ӻ�;
UINT & TablePacket::GetBrokerage()       {  return (m_uiBrokerage);  }       // ��λ��;

UINT & TablePacket::GetTimeStep()        {  return (m_uiTimeStep);   }       // ʱ���;
BYTE & TablePacket::GetPlaySeatId()      {  return (m_byPlaySeatId); }       // ��λ��;

BYTE & TablePacket::GetBankerId()        {  return (m_byBankerId);      }   // ����ID;
BYTE & TablePacket::GetBasicPokerSize()  {  return (m_byBasicPokerSize);}   // �����ƴ�С;
CHAR * TablePacket::GetBasicPokers()    {  return (m_byBasicPokers);   }   // ������ֵ;

UINT & TablePacket::GetUserKey(BYTE seatid)     {  return (m_uiUserKey[seatid]);    }       // �û����ֵ
BYTE & TablePacket::GetPosition(BYTE seatid)    {  return (m_byPosition[seatid]);   }       // ְλ�����������;
BYTE & TablePacket::GetReady(BYTE seatid)       {  return (m_byReady[seatid]);      }       // ׼������;
UINT & TablePacket::GetRate(BYTE seatid)        {  return (m_uiRate[seatid]);       }       // ʤ��;
int  & TablePacket::GetMoney(BYTE seatid)       {  return (m_iMoney[seatid]);       }       // Ǯ;
int  & TablePacket::GetGain(BYTE seatid)        {  return (m_iGain[seatid]);        }       // ����;
CHAR * TablePacket::GetName(BYTE seatid)        {  return (m_szName[seatid]);       }       // ����;

BYTE & TablePacket::GetOnline(BYTE seatid)         {  return (m_byOnline[seatid]);        }   // ����
BYTE & TablePacket::GetTrusteeship(BYTE seatid)    {  return (m_byTrusteeship[seatid]);   }   // �й�

BYTE & TablePacket::GetPokerSize(BYTE seatid)   {  return (m_byPokerSize[seatid]);    }     // ����
BYTE * TablePacket::GetPokers()                 {  return (m_szPokers);               }     // ��

BYTE & TablePacket::GetLimitedTimes()               {  return (m_byLimitedTimes);             }     // ������ʱ;
BYTE & TablePacket::GetCalledStatus(BYTE seatid)    {  return (m_byCalledStatus[seatid]);     }     // �������;
BYTE & TablePacket::GetCalledType(BYTE seatid)      {  return (m_byCalledType[seatid]);       }     // �������;
BYTE & TablePacket::GetDiscardStatus(BYTE seatid)   {  return (m_byDiscardStatus[seatid]);    }     // �������;

BYTE & TablePacket::GetFirst()                      {  return (m_byFirst);                    }     // ��һ�γ���;
BYTE & TablePacket::GetInitcards()                  {  return (m_byInitCards);                }     // ��ʼ������;

BYTE & TablePacket::GetDisplayPokerSize(BYTE seatid){  return (m_byDisplayPokerSize[seatid]); }     // ����Ƶ����;
CHAR * TablePacket::GetDisplayPokers(BYTE seatid)   {  return (m_szDisplayPokers[seatid]);    }     // ��Ҵ����;

BYTE & TablePacket::GetThanSeatId()     {  return (m_byThanSeatId);       }   // �Ƚ���λ;
BYTE & TablePacket::GetThanType()       {  return (m_byThanType);       }   // �Ƚ�����;
BYTE & TablePacket::GetThanValue()      {  return (m_byThanValue);      }   // �Ƚ�ֵ;
BYTE & TablePacket::GetThanCount()      {  return (m_byThanCount);      }   // �Ƚϸ���;
BYTE & TablePacket::GetIndexSize()      {  return (m_byIndexSize);      }   // ���Ƹ���;
BYTE & TablePacket::GetThanPokerSize()  {  return (m_byThanPokerSize);  }   // �Ƚϸ���
CHAR * TablePacket::GetThanPokers()     {  return (m_szThanPokers);     }   // ���Ƹ���

BYTE & TablePacket::GetSettlement()     {  return (m_bySettlement);     }   // ����;

void TablePacket::ToPrint()
{
    DEBUG_MSG( LVL_DEBUG, "Begin");

    DEBUG_MSG( LVL_DEBUG, "| Protocol=%d | TokenKey=%d | ValidTime=%d | ValidCount=%d |",
                m_uiProtocol, m_uiTokenKey, m_uiValidTime, m_uiValidCount);

    DEBUG_MSG( LVL_DEBUG, "| FieldId=%d | RoomId=%d | TableId=%d |",
                m_byFieldId, m_byRoomId, m_uiTableId );

    DEBUG_MSG( LVL_DEBUG, "| Model=%d | Multiple=%d | Brokerage=%d | TimeStep=%d | SeatId=%d |",
                m_byModel, m_uiMultiple, m_uiBrokerage, m_uiTimeStep, m_byPlaySeatId );

    DEBUG_MSG( LVL_DEBUG, "| UserKey=%d | Position=%d | Ready=%d | Rate=%d | Money=%d | Name=%s | ",
                m_uiUserKey[0],  m_byPosition[0], m_byReady[0], m_uiRate[0], m_iMoney[0], m_szName[0] );

    DEBUG_MSG( LVL_DEBUG, "| UserKey=%d | Position=%d | Ready=%d | Rate=%d | Money=%d | Name=%s |",
                m_uiUserKey[1], m_byPosition[1], m_byReady[1], m_uiRate[1], m_iMoney[1], m_szName[1] );

    DEBUG_MSG( LVL_DEBUG, "| UserKey=%d | Position=%d | Ready=%d | Rate=%d | Money=%d | Name=%s |",
                m_uiUserKey[2], m_byPosition[2], m_byReady[2], m_uiRate[2], m_iMoney[2], m_szName[2] );

    DEBUG_MSG( LVL_DEBUG, "| CalledStatus=%d | CalledType=%d | DiscardPokers=%s |",
                m_byCalledStatus[0], m_byCalledType[0], m_szDisplayPokers[0] );

    DEBUG_MSG( LVL_DEBUG, "| CalledStatus=%d | CalledType=%d | DiscardPokers=%s |",
                m_byCalledStatus[1], m_byCalledType[1], m_szDisplayPokers[1] );

    DEBUG_MSG( LVL_DEBUG, "| CalledStatus=%d | CalledType=%d | DiscardPokers=%s |",
                m_byCalledStatus[2], m_byCalledType[2], m_szDisplayPokers[2] );

    DEBUG_MSG( LVL_DEBUG, "End\n");
}

// �ͻ��˰�
char * TablePacket::ClientData( BYTE bMainSeatid, BYTE bSeatid, char * szBuff, WORD wSize )
{
    memset(szBuff, 0x0, wSize);
    if ( GetPosition(bSeatid)!=0 ) {

        BYTE byCount = GetDisplayPokerSize(bSeatid);
        char * poker = NULL;
        if (bMainSeatid==bSeatid) {
            poker = GetDisplayPokers(bSeatid);
        }

        snprintf( szBuff, wSize, "{ \"show\":%s,"        // �Լ�
                                   "\"ready\":%s,"       // ׼��
                                   "\"name\":\"%s\","    // ����
                                   "\"rate\":%d,"        // ʤ��
                                   "\"money\":%d,"       // Ǯ
                                   "\"gain\":%d,"        // ����
                                   "\"online\":%s,"      // ״̬:
                                   "\"trusteeship\":%s," // �й�:
                                   "\"called\":%s,"      // �е���
                                   "\"calltype\":%d,"    // �е���:������0|1��
                                   "\"discard\":%s,"     // ���ƣ�
                                   "\"showcard\":%s,"    // ��ʾ���ƣ�
                                   "\"count\":%d,"
                                   "\"pokers\":[%s]"
                                 "}",
                 "true",
                 (GetReady(bSeatid)!=PK_READY)? "false":"true",
                 GetName(bSeatid),
                 GetRate(bSeatid),
                 GetMoney(bSeatid),
                 GetGain(bSeatid),
                 (GetOnline(bSeatid)!=PK_ONLINE)? "false":"true",
                 (GetTrusteeship(bSeatid)!=PK_TRUSTEESHIP)? "false":"true",
                 (GetPlaySeatId()!=bSeatid)?"false":"true",   // �еĵ���
                 GetCalledStatus(bSeatid),
                 (GetPlaySeatId()!=bSeatid)?"false":"true",   // ����
                 (GetThanSeatId()!=bSeatid)?"false":"true",   // ��ʾ����
                 byCount,   // �������Ƴ���
                 (poker)?(poker):("-1") );
    }
    else
    {
        snprintf( szBuff, wSize, "{\"show\":false,"     // ������Ҳ���
                                  "\"ready\":false,"    // �Ѿ�׼��
                                  "\"name\":\"-\","     // ����
                                  "\"rate\":0,"         // ʤ��
                                  "\"money\":0,"        // Ǯ
                                  "\"gain\":0,"         // ����
                                  "\"online\":false,"       // ״̬
                                  "\"trusteeship\":false,"  // �й�
                                  "\"called\":false,"       // �е�����
                                  "\"calltype\":0,"
                                  "\"discard\":false,"      // ������
                                  "\"showcard\":false,"     // ��ʾ����
                                  "\"count\":0,"            // ����
                                  "\"pokers\":[-1]"         // �����ַ���
                                  "}" );
    }
    return (szBuff);
}

UINT TablePacket::JsonData(BYTE bSeatid, char * szBuff, WORD wSize )    // Json���ݴ��
{
    char _protocol[32] = {0};

    szBuff[0] = '\0';
    snprintf( _protocol, sizeof(_protocol), "{\"protocol\":\"%d\",", m_uiProtocol);
    strcat( szBuff, _protocol);

    char * poker = GetThanPokers();
    if (*poker=='\0') {
        strcat(poker, "-1");
    }

    char _data[256] = {0};
    snprintf( _data, sizeof(_data), "\"data\":[{"
                                    "\"battleid\":%d,"
                                    "\"dmodel\":%s,"
                                    "\"seatid\":%d,"
                                    "\"basics\":%d,"
                                    "\"multiple\":%d,"
                                    "\"brokerage\":%d,"
                                    "\"first\":%s,"
                                    "\"banker\":%d,"
                                    "\"times\":%d,"             // ����ʱ��
                                    "\"count\":%d,"             // ��������
                                    "\"pokers\":[%s],"          // ������
                                    "\"dseatid\":%d,"           // ����Ƶ���λ
                                    "\"dcount\":%d,"            // ����ĳ���
                                    "\"dpokers\":[%s],",        // �������

             m_uiTableId, (m_byModel==0)?"false":"true", bSeatid, m_uiBasicMoney, m_uiMultiple, m_uiBrokerage,
             (GetFirst()==true)?"true":"false", GetBankerId(), GetLimitedTimes(),
             GetBasicPokerSize(), GetBasicPokers(),
             GetThanSeatId(), GetThanPokerSize(), poker );

    strcat( szBuff, _data);

    char _show[1024] = {0};
    strcat( _show, "\"seatinfo\":[" );
    {
        char * _ptr = NULL;
        char _buff[256] = {0};
        _ptr = ClientData( bSeatid, 0, _buff, sizeof(_buff) );
        strcat( _show, _ptr );
        strcat( _show, "," );
        _ptr = ClientData( bSeatid, 1, _buff, sizeof(_buff) );
        strcat( _show, _ptr );
        strcat( _show, "," );
        _ptr = ClientData( bSeatid, 2, _buff, sizeof(_buff) );
        strcat( _show, _ptr );
    }
    strcat( _show, "]" );
    strcat( szBuff, _show);
    strcat( szBuff, "}]}");

    return strlen( szBuff );
}

