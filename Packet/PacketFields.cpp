#include "PacketFields.h"

FieldsPacket::FieldsPacket()
{
}

FieldsPacket::~FieldsPacket()
{
}

void FieldsPacket::ToInit()   {   memset( this, 0x0, sizeof(this) );  }  // 清理

void FieldsPacket::SetPacket ( BYTE * byData, WORD wSize ){
    memcpy( this, byData, wSize );
}
BYTE * FieldsPacket::GetPacket ( BYTE * _data, WORD _size )   {  // 给一个指针并获得头指针;
    memcpy( _data, this, sizeof(FieldsPacket) );
    return _data;
}

WORD FieldsPacket::GetPacketSize() {   // 取得这个包指针;
    return sizeof(this);
}

void FieldsPacket::ToPrint()
{
    //DEBUG_MSG( LVL_DEBUG, "| FieldsPacket(%s); |", m_pJsonData);
}

BYTE & FieldsPacket::GetFieldsSize()
{   return m_pFieldsSize; }

ST_Field & FieldsPacket::GetFields()
{   return m_sFieldsData; }

