#ifndef _PacketFields_H_
#define _PacketFields_H_
#include <TemplatePacket.h>


/*************************************/
#pragma pack(push, 1)
struct ST_Field
{
    BYTE byIndex;// 房间号
    UINT uiCount;// 房间数
    CHAR szName[33];// 名称
};

class FieldsPacket : public TemplatePacket
{
public:
	FieldsPacket();
	~FieldsPacket();

    virtual void ToInit(); // 初始化
    virtual void ToPrint(); // 打印
    virtual void SetPacket(BYTE *, WORD ); // 设置包结构

public:
    BYTE * GetPacket(BYTE *, WORD); // 给一个指针并获得头指针;
    WORD   GetPacketSize(); // 取得这个包大小;

    BYTE & GetFieldsSize(); // 大小
    ST_Field & GetFields(BYTE byIndex); // 排行版

    WORD & GetJsonSize(); // 给一个指针并获得头指针;
    CHAR * GetJsonData(); // 取得这个包大小;

private:
    BYTE m_pFieldsSize; // 数据大小
    ST_Field m_pFieldsData[5]; // 排行版

    WORD m_wJsonSize; // 数据大小
    CHAR m_pJsonData[512]; // 排行版
};
#pragma pack(pop)
/*************************************/

#endif // _UserPacket_H_INCLUDED_
