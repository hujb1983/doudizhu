#include "PacketRank.h"

RankPacket::RankPacket()
{
}

RankPacket::~RankPacket()
{
}

void RankPacket::ToInit()   {   memset( this, 0x0, sizeof(this) );  }  // 清理

void RankPacket::SetPacket ( BYTE * byData, WORD wSize ){
    memcpy( this, byData, wSize );
}
BYTE * RankPacket::GetPacket ( BYTE * _data, WORD _size )   {  // 给一个指针并获得头指针;
    memcpy( _data, this, sizeof(RankPacket) );
    return _data;
}

WORD   RankPacket::GetPacketSize() {   // 取得这个包指针;
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


