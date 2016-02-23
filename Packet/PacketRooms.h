#ifndef _PacketRooms_H_
#define _PacketRooms_H_
#include <TemplatePacket.h>


/*************************************/
#pragma pack(push, 1)
struct ST_Room
{
    UINT m_uiFieldId;            // ����ID
    UINT m_uiRoomId;          // ����ID
    CHAR m_szName[33];         // ��������
    BYTE m_byDoubles;           // �Ƿ�ӱ�
    BYTE m_byLimitPS;           // �����������
    BYTE m_byOnlines;           // ��������
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

    BYTE & GetFieldId(); // ��������
    BYTE & GetRoomsSize(); // ��С
    ST_Room & GetRooms( BYTE index ); // ���а�

    WORD & GetJsonSize(); // ��һ��ָ�벢���ͷָ��;
    CHAR * GetJsonData(); // ȡ���������С;

private:
    BYTE m_byFieldId; // ����ID

    BYTE m_wRoomsSize; // ���ݴ�С
    ST_Room m_sRoomsData[32]; // ���а�

    WORD m_wJsonSize; // ���ݴ�С
    CHAR m_pJsonData[512]; // ���а�
};
#pragma pack(pop)
/*************************************/

#endif // _UserPacket_H_INCLUDED_
