#ifndef _TemplatePacket_H_
#define _TemplatePacket_H_

#include <UtilityDefine.h>
#include <UtilityInclude.h>

#pragma pack(push,1)
class TemplatePacket
{
public:
    static UINT GetTickCount();     // ʱ��

public:
	TemplatePacket();
	~TemplatePacket();

    virtual void ToInit();                  // ��ʼ��
    virtual void ToPrint();                 // ��ӡ
    virtual void SetPacket(BYTE *, WORD );  // ���ð��ṹ

public:
    UINT & GetProtocol();       // ȡ�ú�����Э���;
    UINT & GetTokenKey();       // ��ȫ��;
    UINT & GetValidTime();      // ȡ����Чʱ��;
    UINT & GetValidCount();     // ��Чʹ�ô���;
    UINT & GetPortKey();        // �˿ں�
	UINT & GetUserKey();        // ��Ҽ�ֵ
    UINT & GetAgentKey();       // ���������

private:
    UINT  m_uiProtocol;         // Э��;
    UINT  m_uiTokenKey;         // ���ɵķ�����;
    UINT  m_uiValidTime;        // ��Чʱ������;
    UINT  m_uiValidCount;       // ��Ч���ʼ���;
    UINT  m_uiPortKey;          // ��ڼ�ֵ;
    UINT  m_uiOldPortKey;       // �ɵ���ڼ�ֵ;
	
	UINT  m_uiUserKey;          // ��ڼ�ֵ;
    UINT  m_uiAgentKey;         // �����ֵ;
};
#pragma pack(pop)

#endif // _TemplatePacket_H_
