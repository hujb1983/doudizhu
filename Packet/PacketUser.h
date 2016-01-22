#ifndef _UserPacket_H_INCLUDED_
#define _UserPacket_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>
#include "HeadPacket.h"

/*************************************/
#pragma pack(push, 1)

class UserPacket
{
public:
    static UINT GetTickCount();     // ʱ��

public:

	UserPacket();
	~UserPacket();

    void ToInit();                  // ��ʼ��
    void ToPrint();                 // ��ӡ
    void SetPacket(BYTE *, WORD );  // ���ð��ṹ

public:

    BYTE * GetPacket(BYTE *, WORD);   // ��һ��ָ�벢���ͷָ��;
    WORD   GetPacketSize();               // ȡ���������С;

    UINT & GetProtocol();       // ȡ�ú�����Э���;
    UINT & GetTokenKey();       // ��ȫ��;
    UINT & GetValidTime();      // ȡ����Чʱ��;
    UINT & GetValidCount();     // ��Чʹ�ô���;
    UINT & GetPortKey();        // �˿ں�
    UINT & GetAgentKey();       // ���������

    UINT & GetLoginTime();      // ��¼ʱ��;
    BYTE * GetSSHKey();         // ��¼Key;
    UINT & GetUserId();         // �û���ID;
    UINT & GetUserKey();        // �û���Key;
    UINT & GetOldKey();         // �û���ǰ�õ�Key;
    CHAR * GetName();           // ȡ����Чʱ��;
    INT  & GetMoney();          // �Ƹ�;
    UINT & GetWoneds();         // Ӯ�Ĵ���;
    UINT & GetFaileds();        // ʧ�ܵĴ���;
    UINT & GetAways();          // �뿪�Ĵ���;

    BYTE & GetFieldId();        // ���κ�;
    BYTE & GetRoomId();         // �����;
    UINT & GetTableId();        // �����ֵ;
    WORD & GetBattleId();       // �����;
    BYTE & GetSeatId();         // ��λ��;

    BYTE & GetReady();          // �Ƿ�׼����;
    BYTE & GetCalled();         // �Ƿ�е���;
    BYTE & GetBanker();         // �Ƿ����;
    BYTE & GetEnd();            // �Ƿ����;

    UINT & GetCalledTimes();        // �е�������Ȩʱ��;
    UINT & GetCalledTimesLast();    // �е���������ʱ��;

    BYTE & GetCount();             // ������;
    BYTE * GetPokers();            // ���ϵ���;

    UINT & GetShowTimes();          // ������Ȩʱ��;
    UINT & GetShowTimesLast();      // ����������ʱ��;
    BYTE & GetShowMan();            // �Ƿ����;
    BYTE * GetShowPokers();         // �������;

    UINT & GetShowedSize();        // ���ƴ�С;
    CHAR * GetShowedPokers();      // �Ѿ��������;

    CHAR * GetReminderPokers();    // ������ʾ;
    BYTE & GetReminderSize();      // ���ƴ�С;

private:

    UINT  m_uiProtocol;         // Э��;
    UINT  m_uiTokenKey;         // ���ɵķ�����;
    UINT  m_uiValidTime;        // ��Чʱ������;
    UINT  m_uiValidCount;       // ��Ч���ʼ���;
    UINT  m_uiPortKey;          // ��ڼ�ֵ;
    UINT  m_uiOldPortKey;       // �ɵ���ڼ�ֵ;
    UINT  m_uiAgentKey;         // �����ֵ;

    UINT  m_uiLogin;            // ��¼ʱ��;
    BYTE  m_szSSHKey[128];      // ��½Key;
    UINT  m_uiUserId;           // ���ݿ���;
    CHAR  m_szName[33];         // ����
    INT   m_iMoney;             // ����
    UINT  m_uiWoneds;           // Ӯ�Ĵ���
	UINT  m_uiFaileds; 	        // ʧ�ܴ���
	UINT  m_uiAways; 		    // ���ܴ���

    WORD  m_wBattleId;          // ս������;
    BYTE  m_byFieldId;          // ���κ�;
    BYTE  m_byRoomId;           // �����;
    UINT  m_uiTableId;          // ���Ӻ�;
    BYTE  m_bySeatId;           // ��λ��;

    BYTE  m_byReady;            // �Ƿ�׼����;
    BYTE  m_byCalled;           // �Ƿ�е���;
    UINT  m_uiCallTimes;        // �е�����Ȩʱ��;
    UINT  m_uiCallTimesLast;    // �е�������ʱ��;
    BYTE  m_byBanker;           // �Ƿ����;
    BYTE  m_byFirst;            // �Ƿ����;

    BYTE  m_byCount;            // ������;
    BYTE  m_byPokers[20];       // ���ϵ���;

    UINT  m_uiShowTimes;         // ������Ȩʱ��;
    UINT  m_uiShowTimesLast;     // ��������ʱ��;
    BYTE  m_byShowMan;           // �Ƿ����;
    BYTE  m_byShowPokers[20];    // �������;

    UINT  m_uiShowedCount;          // �Ѿ��������;
    CHAR  m_byShowedPokers[80];     // �Ѿ��������;

    CHAR m_szReminderPokers[60];
    BYTE m_byReminderSize;
};

#pragma pack(pop)
/*************************************/

#endif // _UserPacket_H_INCLUDED_
