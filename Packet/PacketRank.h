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

    virtual void ToInit(); // ��ʼ��
    virtual void ToClear(); // �����
    virtual void ToPrint(); // ��ӡ
    virtual void SetPacket(BYTE *, WORD ); // ���ð��ṹ

public:
    BYTE * GetPacket(BYTE *, WORD); // ��һ��ָ�벢���ͷָ��;
    WORD   GetPacketSize(); // ȡ���������С;

public:
    BYTE & GetRankSize(); // ��С
    ST_Rank & GetRank(BYTE byIndex); // ���а�

    WORD & GetJsonSize(); // ��һ��ָ�벢���ͷָ��;
    CHAR * GetJsonData(); // ȡ���������С;

private:
    BYTE m_pRankSize; // ���ݴ�С
    ST_Rank m_sRankData[10]; // ���а�

    WORD m_wJsonSize; // ���ݴ�С
    CHAR m_pJsonData[512]; // ���а�
};

#pragma pack(pop)
/*************************************/

#endif // _UserPacket_H_INCLUDED_
