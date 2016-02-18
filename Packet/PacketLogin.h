#ifndef _PacketLogin_H_
#define _PacketLogin_H_
#include <TemplatePacket.h>

#pragma pack(push,1)
class LoginPacket : public TemplatePacket
{
public:

	LoginPacket();
	~LoginPacket();

    virtual void ToInit();                  // ��ʼ��
    virtual void ToPrint();                 // ��ӡ
    virtual void SetPacket(BYTE *, WORD );  // ���ð��ṹ

public:

	BYTE * GetPacket(BYTE *, WORD);	// ��һ��ָ�벢���ͷָ��;
	WORD   GetPacketSize();			// ȡ���������С;

	UINT & GetAccessID();
	UINT & GetUserid();
	CHAR * GetUsername();
	CHAR * GetPassword();
	CHAR * GetSSHKey();
	UINT & GetGameType();
	UINT & GetLoginType();

	CHAR * GetAddress();
	UINT & GetPort();

private:

	UINT m_uiUserid;// �û�;
	UINT m_uiAccessID;// �û�;
	CHAR m_szUsername[32];// ����;
	CHAR m_szPassword[32];// ����;
	CHAR m_szSSHKey[32];// ��ֵ;
	UINT m_uiGameType;// ��Ϸ��;
    UINT m_uiLoginType;// ��½����;

	CHAR m_szAddress[16];// IP��ַ;
    UINT m_uiPort;// �˿�;

};
#pragma pack(pop)

#endif // _PacketLogin_H_
