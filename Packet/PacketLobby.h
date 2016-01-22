#ifndef _LobbyPacket_H_INCLUDED_
#define _LobbyPacket_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>
#include "HeadPacket.h"

/*************************************/
#pragma pack(push, 1)

struct SField {
    SField() { memset(this, 0x0, sizeof(this)); }
    BYTE err;       // �Ƿ���Ч;
    BYTE id;        // id��;
    BYTE tables;    // ������;
    char name[33];  // ����;
};

struct SRoom {
    SRoom() { memset(this, 0x0, sizeof(SRoom)); }
    BYTE roomid;        // id��;
    BYTE tableid;       // ������;
    char name[33];      // ����;
    char doub;          // ����ģʽ;
    char onlines;       // ��������;
    char maxonlines;    // �����������;
    UINT money;         // �������;
};

class LobbyPacket
{
public:
	LobbyPacket();
	~LobbyPacket();

    void ToInit();                  // ��ʼ��
    void ToPrint();                 // ��ӡ
    void SetPacket(BYTE *, WORD );  // ���ð��ṹ


public:

    BYTE * GetPacket(BYTE *, WORD);   // ��һ��ָ�벢���ͷָ��;
    WORD   GetPacketSize();           // ȡ���������С;

    UINT & GetProtocol();       // ȡ�ú�����Э���;
    UINT & GetTokenKey();       // ��ȫ��;
    UINT & GetValidTime();      // ȡ����Чʱ��;
    UINT & GetValidCount();     // ��Чʹ�ô���;
    UINT & GetPortkey();        // �˿ں�
    UINT & GetAgentkey();       // ���������

    UINT & GetOnlines();        // ��������������

    UINT & GetFieldSize();        // ���θ���
    UINT & GetFieldOffset();      // ����ƫ����
    BYTE * GetFields();           // ����ָ��

    UINT & GetRoomSize();        // �������������
    UINT & GetRoomOffset();      // ����ƫ����
    BYTE * GetRooms();           // ����ָ��

    UINT & GetWeekRankSize();    // �ܱ�����
    UINT & GetWeekRankOffset();  // �ܱ�ƫ����
    BYTE * GetWeekRanks();       // �ܱ�ָ��

    UINT & GetDayRankSize();     // �ձ�����
    UINT & GetDayRankOffset();   // �ձ�ƫ����
    BYTE * GetDayRanks();        // �ձ�ָ��

    UINT & GetDataSize();        // ���ݴ�С
    BYTE * GetData();            // ��û�������

private:

    UINT  m_uiProtocol;         // Э��;
    UINT  m_uiTokenKey;         // ���ɵķ�����;
    UINT  m_uiValidTime;        // ��Чʱ������;
    UINT  m_uiValidCount;       // ��Ч���ʼ���;
    UINT  m_uiPortkey;          // ��ڼ�ֵ;
    UINT  m_uiAgentkey;         // �����ֵ;

    UINT  m_uiOnlines;         // ��������������;

    UINT  m_sFieldSize;        // ���εĸ���;
    UINT  m_sFieldOffset;      // ����ܳ���255��

    UINT  m_sRoomSize;         // ����ĸ���;
    UINT  m_sRoomsOffset;      // ����ܳ���255��

    UINT  m_sWeekRankSize;      // �����а�;
    UINT  m_sWeekRankOffset;    // �����а�ƫ��;

    UINT  m_sDayRankSize;       // �����а�;
    UINT  m_sDayRankOffset;     // �����а�ƫ��

    UINT  m_pDataSize;          // ���ݴ�С
    BYTE * m_pData;             // ָ��

};

#pragma pack(pop)
/*************************************/

#endif // _UserPacket_H_INCLUDED_
