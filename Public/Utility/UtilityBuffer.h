#ifndef __UtilityBuffer_H__
#define __UtilityBuffer_H__

#include <UtilityDefine.h>
#pragma pack(push,1)

class UtilityBuffer
{
public:
	UtilityBuffer(void);
	UtilityBuffer(void * pBuff, WORD wLen);
	~UtilityBuffer(void);

public:
	VOID SetBuff(void * pBuff, WORD wLen);

	//д����
	int		Write(INT nData);
	int		Write(BYTE byData);
	int		Write(WORD wData);
	int		Write(DWORD dwData);
	int		Write(double dbData);
	int		Write(FLOAT fData);
	int		Write(CHAR * strData);
	int		Write(void *pData, WORD wLen);


	//������
	int		Read(INT & nData);
	int		Read(BYTE & byData);
	int		Read(WORD & wData);
	int		Read(DWORD & dwData);
	int		Read(double & dbData);
	int		Read(FLOAT & fData);
	int		Read(CHAR * strData);
	int		Read(void *pData, WORD wLen);

	//��ȡд�����ݳ���
	int		GetWriteLen() { return m_wWriteLen; }

	//��ȡ�������ݳ���
	int		GetReadLen()  { return m_wReadLen; }

	//��ȡͷ��ַ
	BYTE * GetHead()	{ return m_pHead; }

	//��ȡ��ǰ��ַ
	BYTE * GetPost()	{ return m_pBuff; }


private:
	//Buffָ��
	BYTE * m_pHead;
	BYTE * m_pBuff;

	//Buff�ܳ���
	WORD m_wTotalLen;

	//Buff������ݵĳ���
	WORD m_wWriteLen;

	//Buff��ȡ���ݵĳ���
	WORD m_wReadLen;

};


#endif

