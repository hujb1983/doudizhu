#ifndef _PacketRooms_H_
#define _PacketRooms_H_
#include <TemplatePacket.h>


/*************************************/
#pragma pack(push, 1)
struct ST_Room
{
    UINT m_iRoomID;            // ����ID
    UINT m_uiTableID;          // ����ID
    CHAR m_szName[33];         // ��������
    BYTE m_iDoubles;           // �Ƿ�ӱ�
    BYTE m_iLimitPS;           // �����������
    BYTE m_iOnlines;           // ��������
    int  m_iMoney;             // ������
};

class RoomsPacket : public TemplatePacket
{
public:
	RoomsPacket();
	~RoomsPacket();

    virtual void ToInit(); // ��ʼ��
    virtual void ToPrint(); // ��ӡ
    virtual void SetPacket(BYTE *, WORD ); // ���ð��ṹ

public:
    BYTE * GetPacket(BYTE *, WORD); // ��һ��ָ�벢���ͷָ��;
    WORD   GetPacketSize(); // ȡ���������С;

public:
    BYTE & GetRoomsSize(); // ��С
    ST_Room & GetRooms(); // ���а�

private:
    BYTE m_pRoomsSize; // ���ݴ�С
    ST_Room m_sRoomsData; // ���а�

};
#pragma pack(pop)
/*************************************/

#endif // _UserPacket_H_INCLUDED_
