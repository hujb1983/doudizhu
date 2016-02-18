#ifndef _PacketRooms_H_
#define _PacketRooms_H_
#include <TemplatePacket.h>


/*************************************/
#pragma pack(push, 1)
struct ST_Room
{
    UINT m_iRoomID;            // 房间ID
    UINT m_uiTableID;          // 桌子ID
    CHAR m_szName[33];         // 房间名称
    BYTE m_iDoubles;           // 是否加倍
    BYTE m_iLimitPS;           // 限制最高人数
    BYTE m_iOnlines;           // 在线人数
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

public:
    BYTE & GetRoomsSize(); // 大小
    ST_Room & GetRooms(); // 排行版

private:
    BYTE m_pRoomsSize; // 数据大小
    ST_Room m_sRoomsData; // 排行版

};
#pragma pack(pop)
/*************************************/

#endif // _UserPacket_H_INCLUDED_
