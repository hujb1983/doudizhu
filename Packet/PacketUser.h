#ifndef _PacketUser_H_
#define _PacketUser_H_
#include <TemplatePacket.h>

/*************************************/
#pragma pack(push, 1)
class UserPacket : public TemplatePacket
{
public:

	UserPacket();
	~UserPacket();

    virtual void ToInit();                  // ��ʼ��
    virtual void ToPrint();                 // ��ӡ
    virtual void SetPacket(BYTE *, WORD );  // ���ð��ṹ

public:

    BYTE * GetPacket(BYTE *, WORD);   // ��һ��ָ�벢���ͷָ��;
    WORD   GetPacketSize();               // ȡ���������С;

    UINT & GetLoginTime();      // ��¼ʱ��;
    BYTE * GetSSHKey();         // ��¼Key;
    UINT & GetUserId();         // �û���ID;
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

#endif // _PacketUser_H_
