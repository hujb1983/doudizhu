#ifndef _PacketRank_H_
#define _PacketRank_H_
#include <TemplatePacket.h>


/*************************************/
#pragma pack(push, 1)

struct ST_Rank
{
    BYTE byIndex;
    CHAR szName[33];
    UINT uiRate;
};

class RankPacket : public TemplatePacket
{
public:
	RankPacket();
	~RankPacket();

    virtual void ToInit(); // 初始化
    virtual void ToClear(); // 清理掉
    virtual void ToPrint(); // 打印
    virtual void SetPacket(BYTE *, WORD ); // 设置包结构

public:
    BYTE * GetPacket(BYTE *, WORD); // 给一个指针并获得头指针;
    WORD   GetPacketSize(); // 取得这个包大小;

public:
    BYTE & GetRankSize(); // 大小
    ST_Rank & GetRank(BYTE byIndex); // 排行版

    WORD & GetJsonSize(); // 给一个指针并获得头指针;
    CHAR * GetJsonData(); // 取得这个包大小;

private:
    BYTE m_pRankSize; // 数据大小
    ST_Rank m_sRankData[10]; // 排行版

    WORD m_wJsonSize; // 数据大小
    CHAR m_pJsonData[512]; // 排行版
};

#pragma pack(pop)
/*************************************/

#endif // _UserPacket_H_INCLUDED_
