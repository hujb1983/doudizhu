#include "PacketRooms.h"

RoomsPacket::RoomsPacket()
{
}

RoomsPacket::~RoomsPacket()
{
}

void RoomsPacket::ToInit()   {   memset( this, 0x0, sizeof(this) );  }  // 清理

void RoomsPacket::SetPacket ( BYTE * byData, WORD wSize ){
    memcpy( this, byData, wSize );
}
BYTE * RoomsPacket::GetPacket ( BYTE * _data, WORD _size )   {  // 给一个指针并获得头指针;
    memcpy( _data, this, sizeof(RoomsPacket) );
    return _data;
}

WORD RoomsPacket::GetPacketSize() {   // 取得这个包指针;
    return sizeof(this);
}

void RoomsPacket::ToPrint()
{
    //DEBUG_MSG( LVL_DEBUG, "| RoomsPacket(%s); |", m_pJsonData);
}

BYTE & RoomsPacket::GetRoomsSize()
{   return m_pRoomsSize; }

ST_Room & RoomsPacket::GetRooms()
{   return m_sRoomsData; }

