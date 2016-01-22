#ifndef _HeadPacket_H_INCLUDED_
#define _HeadPacket_H_INCLUDED_

#include <Utility.h>
#include <Common.h>
#include <Network.h>

/*************************************/
#pragma pack(push, 1)

class HeadPacket
{
public:
    static UINT GetTickCount();     // ʱ��

public:

	HeadPacket();
	~HeadPacket();

    void ToInit();                  // ��ʼ��
    void ToPrint();                 // ��ӡ
    void SetPacket(BYTE *, WORD );  // ���ð��ṹ

public:

    UINT & GetProtocol();       // ȡ�ú�����Э���;
    UINT & GetTokenKey();       // ��ȫ��;
    UINT & GetValidTime();      // ȡ����Чʱ��;
    UINT & GetValidCount();     // ��Чʹ�ô���;
    UINT & GetPortKey();        // �˿ں�
    UINT & GetAgentKey();       // ���������

private:

    UINT  m_uiProtocol;         // Э��;
    UINT  m_uiTokenKey;         // ���ɵķ�����;
    UINT  m_uiValidTime;        // ��Чʱ������;
    UINT  m_uiValidCount;       // ��Ч���ʼ���;
    UINT  m_uiPortKey;          // ��ڼ�ֵ;
    UINT  m_uiOldPortKey;       // �ɵ���ڼ�ֵ;
    UINT  m_uiAgentKey;         // �����ֵ;
};

#pragma pack(pop)
/*************************************/

#endif // _UserPacket_H_INCLUDED_
