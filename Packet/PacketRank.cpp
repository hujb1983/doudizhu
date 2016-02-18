#include "PacketRank.h"

RankPacket::RankPacket()
{
}

RankPacket::~RankPacket()
{
}

void RankPacket::ToInit()   {   memset( this, 0x0, sizeof(this) );  }  // ����

void RankPacket::SetPacket ( BYTE * byData, WORD wSize ){
    memcpy( this, byData, wSize );
}
BYTE * RankPacket::GetPacket ( BYTE * _data, WORD _size )   {  // ��һ��ָ�벢���ͷָ��;
    memcpy( _data, this, sizeof(RankPacket) );
    return _data;
}

WORD   RankPacket::GetPacketSize() {   // ȡ�������ָ��;
    return sizeof(this);
}

void RankPacket::ToPrint()
{
    DEBUG_MSG( LVL_DEBUG, "| RankPacket(%s); |", m_pJsonData);
}

BYTE & RankPacket::GetRankSize()
{   return m_pRankSize; }

ST_Rank & RankPacket::GetRank(BYTE byIndex)
{   if ( byIndex<10 ) { return m_sRankData[byIndex]; }   }

WORD & RankPacket::GetJsonSize()
{   return m_pJsonSize; }

CHAR * RankPacket::GetJsonData()
{   return m_pJsonData; }


