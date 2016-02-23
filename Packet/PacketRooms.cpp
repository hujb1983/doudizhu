#include "PacketRooms.h"

RoomsPacket::RoomsPacket()
{
}

RoomsPacket::~RoomsPacket()
{
}

void RoomsPacket::ToInit()   {   memset( this, 0x0, sizeof(this) );  }  // ����

void RoomsPacket::SetPacket ( BYTE * byData, WORD wSize ){
    memcpy( this, byData, wSize );
}
BYTE * RoomsPacket::GetPacket ( BYTE * _data, WORD _size )   {  // ��һ��ָ�벢���ͷָ��;
    memcpy( _data, this, sizeof(RoomsPacket) );
    return _data;
}

WORD RoomsPacket::GetPacketSize() {   // ȡ�������ָ��;
    return sizeof(this);
}

void RoomsPacket::ToPrint()
{
    //DEBUG_MSG( LVL_DEBUG, "| RoomsPacket(%s); |", m_pJsonData);
}


BYTE & RoomsPacket::GetFieldId()
{   return m_byFieldId; }

BYTE & RoomsPacket::GetRoomsSize()
{   return m_wRoomsSize; }

ST_Room & RoomsPacket::GetRooms( BYTE byIndex )
{   if ( byIndex<33 ) { return m_sRoomsData[byIndex]; }   }

WORD & RoomsPacket::GetJsonSize()
{   return m_wJsonSize; }

CHAR * RoomsPacket::GetJsonData()
{   return m_pJsonData; }
