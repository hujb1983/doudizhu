#ifndef _PacketLogin_H_
#define _PacketLogin_H_
#include <TemplatePacket.h>

#pragma pack(push,1)
class LoginPacket : public TemplatePacket
{
public:

	LoginPacket();
	~LoginPacket();

    virtual void ToInit();                  // 初始化
    virtual void ToPrint();                 // 打印
    virtual void SetPacket(BYTE *, WORD );  // 设置包结构

public:

	BYTE * GetPacket(BYTE *, WORD);	// 给一个指针并获得头指针;
	WORD   GetPacketSize();			// 取得这个包大小;

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

	UINT m_uiUserid;// 用户;
	UINT m_uiAccessID;// 用户;
	CHAR m_szUsername[32];// 名称;
	CHAR m_szPassword[32];// 密码;
	CHAR m_szSSHKey[32];// 键值;
	UINT m_uiGameType;// 游戏号;
    UINT m_uiLoginType;// 登陆类型;

	CHAR m_szAddress[16];// IP地址;
    UINT m_uiPort;// 端口;

};
#pragma pack(pop)

#endif // _PacketLogin_H_
