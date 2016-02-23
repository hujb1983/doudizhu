#ifndef _PacketFields_H_
#define _PacketFields_H_
#include <TemplatePacket.h>


/*************************************/
#pragma pack(push, 1)
struct ST_Field
{
    BYTE byIndex;// �����
    UINT uiCount;// ������
    CHAR szName[33];// ����
};

class FieldsPacket : public TemplatePacket
{
public:
	FieldsPacket();
	~FieldsPacket();

    virtual void ToInit(); // ��ʼ��
    virtual void ToPrint(); // ��ӡ
    virtual void SetPacket(BYTE *, WORD ); // ���ð��ṹ

public:
    BYTE * GetPacket(BYTE *, WORD); // ��һ��ָ�벢���ͷָ��;
    WORD   GetPacketSize(); // ȡ���������С;

    BYTE & GetFieldsSize(); // ��С
    ST_Field & GetFields(BYTE byIndex); // ���а�

    WORD & GetJsonSize(); // ��һ��ָ�벢���ͷָ��;
    CHAR * GetJsonData(); // ȡ���������С;

private:
    BYTE m_pFieldsSize; // ���ݴ�С
    ST_Field m_pFieldsData[5]; // ���а�

    WORD m_wJsonSize; // ���ݴ�С
    CHAR m_pJsonData[512]; // ���а�
};
#pragma pack(pop)
/*************************************/

#endif // _UserPacket_H_INCLUDED_
