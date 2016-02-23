#ifndef _PacketRooms_H_
#define _PacketRooms_H_
#include <TemplatePacket.h>


/*************************************/
#pragma pack(push, 1)
struct ST_Room
{
    UINT m_uiFieldId;            // 房间ID
    UINT m_uiRoomId;          // 桌子ID
    CHAR m_szName[33];         // 房间名称
    BYTE m_byDoubles;           // 是否加倍
    BYTE m_byLimitPS;           // 限制最高人数
    BYTE m_byOnlines;           // 在线人数
    int  m_iMoney;             // 带入金额
};

class RoomsPacket : public TemplatePacket
{
public:
	RoomsPacket();
	~RoomsPacket();

    virtual void ToInit(); // 初始化
    virtual void ToPrint(); // 打印
    virtual void SetPacket(BYTE *, WORD ); // 设置包结构

public:
    BYTE * GetPacket(BYTE *, WORD); // 给一个指针并获得头指针;
    WORD   GetPacketSize(); // 取得这个包大小;

    BYTE & GetFieldId(); // 所属场次
    BYTE & GetRoomsSize(); // 大小
    ST_Room & GetRooms( BYTE index ); // 排行版

    WORD & GetJsonSize(); // 给一个指针并获得头指针;
    CHAR * GetJsonData(); // 取得这个包大小;

private:
    BYTE m_byFieldId; // 场次ID

    BYTE m_wRoomsSize; // 数据大小
    ST_Room m_sRoomsData[32]; // 排行版

    WORD m_wJsonSize; // 数据大小
    CHAR m_pJsonData[512]; // 排行版
};
#pragma pack(pop)
/*************************************/

#endif // _UserPacket_H_INCLUDED_
