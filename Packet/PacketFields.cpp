#include "PacketFields.h"

FieldsPacket::FieldsPacket()
{
}

FieldsPacket::~FieldsPacket()
{
}

void FieldsPacket::ToInit()   {   memset( this, 0x0, sizeof(this) );  }  // ����

void FieldsPacket::SetPacket ( BYTE * byData, WORD wSize ){
    memcpy( this, byData, wSize );
}
BYTE * FieldsPacket::GetPacket ( BYTE * _data, WORD _size )   {  // ��һ��ָ�벢���ͷָ��;
    memcpy( _data, this, sizeof(FieldsPacket) );
    return _data;
}

WORD FieldsPacket::GetPacketSize() {   // ȡ�������ָ��;
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

