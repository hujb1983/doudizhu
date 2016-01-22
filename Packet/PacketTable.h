#ifndef _TablePacket_H_INCLUDED_
#define _TablePacket_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>
#include "HeadPacket.h"

/*************************************/
#pragma pack(push, 1)

class TablePacket
{
public:
	TablePacket();
	~TablePacket();

    void ToInit();                  // ��ʼ��
    void ToPrint();                 // ��ӡ
    void SetPacket(BYTE *, WORD );  // ���ð��ṹ

public:
    UINT JsonData(BYTE bSeatid, char * szBuff, WORD wSize );    // Json���ݴ��
    char * ClientData(BYTE bMainSeatid, BYTE bSeatid, char * szBuff, WORD wSize );  // Client-Json���ݴ��

    BYTE * GetPacket(BYTE *, WORD);   // ��һ��ָ�벢���ͷָ��;
    WORD   GetPacketSize();           // ȡ���������С;

    UINT & GetProtocol();       // ȡ�ú�����Э���;
    UINT & GetTokenKey();       // ��ȫ��;
    UINT & GetValidTime();      // ȡ����Чʱ��;
    UINT & GetValidCount();     // ��Чʹ�ô���;

    BYTE & GetFieldId();        // ���κ�;
    BYTE & GetRoomId();         // �����;
    UINT & GetTableId();        // �����ֵ;
    WORD & GetBattleId();       // �����;

    BYTE & GetModel();          // ģʽ;
    UINT & GetBasicMoney();     // ��ͽ��;
    UINT & GetMultiple();       // ����;
    UINT & GetBrokerage();      // Ӷ��;

    UINT & GetTimeStep();       // ʱ���;
    BYTE & GetPlaySeatId();     // ��λ��;

    BYTE & GetBankerId();           // ����ID;
    BYTE & GetBasicPokerSize();     // �����ƴ�С;
    CHAR * GetBasicPokers();       // ������ֵ;

    UINT & GetUserKey(BYTE);    // �û����ֵ
    BYTE & GetPosition(BYTE);   // ְλ�����������;
    BYTE & GetReady(BYTE);      // ׼������;
    UINT & GetRate(BYTE);       // ʤ��;
    int  & GetMoney(BYTE);      // Ǯ;
    int  & GetGain(BYTE);       // ����;
    CHAR * GetName(BYTE);       // ����

    BYTE & GetOnline(BYTE);         // ����
    BYTE & GetTrusteeship(BYTE);    // �й�

    BYTE & GetPokerSize(BYTE);  // ����
    BYTE * GetPokers();         // ��

    BYTE & GetLimitedTimes();           // ������ʱ;
    BYTE & GetCalledStatus(BYTE);       // �������;
    BYTE & GetCalledType(BYTE seatid);  // ��������;

    BYTE & GetFirst();                  // ��һ�γ���;
    BYTE & GetInitcards();              // ��ʼ������;

    BYTE & GetDiscardStatus(BYTE);      // �������;
    BYTE & GetDisplayPokerSize(BYTE);   // ��������;
    CHAR * GetDisplayPokers(BYTE);      // ��Ҵ����;

    BYTE & GetThanSeatId();      // ������λ;
    BYTE & GetThanType();        // �Ƚ�����
    BYTE & GetThanValue();       // �Ƚ�ֵ
    BYTE & GetThanCount();       // �Ƚϸ���
    BYTE & GetIndexSize();       // ���Ƹ���
    BYTE & GetThanPokerSize();   // �Ƚϸ���
    CHAR * GetThanPokers();      // ���Ƹ���

    BYTE & GetSettlement();      // ����;

private:

    UINT  m_uiProtocol;         // Э��;
    UINT  m_uiTokenKey;         // ���ɵķ�����;
    UINT  m_uiValidTime;        // ��Чʱ������;
    UINT  m_uiValidCount;       // ��Ч���ʼ���;

    BYTE  m_byFieldId;          // ���κ�;
    BYTE  m_byRoomId;           // �����;
    UINT  m_uiTableId;          // ���Ӻ�;

    BYTE  m_byModel;            // �ӱ�ģʽ;
    UINT  m_uiBasicMoney;       // �������;
    UINT  m_uiMultiple;         // �ӱ�ֵ;
    UINT  m_uiBrokerage;        // Ӷ��;

    UINT  m_uiTimeStep;         // ʱ���
    BYTE  m_byPlaySeatId;       // ���������;

    BYTE  m_byBankerId;         // ��������λ��;
    BYTE  m_byBasicPokerSize;   // ������
    CHAR  m_byBasicPokers[16];  // ����

    UINT m_uiUserKey[TEAM_SIZE];    // �û����ֵ
    BYTE m_byPosition[TEAM_SIZE];   // ְλ���գ����������
    BYTE m_byReady[TEAM_SIZE];      // ׼������
    UINT m_uiRate[TEAM_SIZE];       // ʤ��
    int  m_iMoney[TEAM_SIZE];       // Ǯ
    int  m_iGain[TEAM_SIZE];        // ����
    CHAR m_szName[TEAM_SIZE][33];   // ����

    BYTE m_byOnline[TEAM_SIZE];         // ����
    BYTE m_byTrusteeship[TEAM_SIZE];    // �й�

    BYTE m_byPokerSize[TEAM_SIZE];    // ����
    BYTE m_szPokers[POKER_SIZE+1];    // ��

    BYTE m_byLimitedTimes;              // ������ʱ״̬
    BYTE m_byCalledStatus[TEAM_SIZE];   // ����״̬
    BYTE m_byCalledType[TEAM_SIZE];     // ��������

    BYTE m_byInitCards;                 // ��ʼ����
    BYTE m_byFirst;                     // ��һ�γ�����

    BYTE m_byDiscardStatus[TEAM_SIZE];  // ����״̬
    BYTE m_byDisplayPokerSize[TEAM_SIZE];    // �������λ
    CHAR m_szDisplayPokers[TEAM_SIZE][80+1]; // �������

    BYTE m_byThanSeatId;      // �Ƚϵ���λ
    BYTE m_byThanType;
    BYTE m_byThanValue;
    BYTE m_byThanCount;
    BYTE m_byIndexSize;

    BYTE m_byThanPokerSize;    // �������λ
    CHAR m_szThanPokers[80+1]; // �������

    BYTE m_bySettlement;
};

#pragma pack(pop)
/*************************************/

#endif // _UserPacket_H_INCLUDED_
