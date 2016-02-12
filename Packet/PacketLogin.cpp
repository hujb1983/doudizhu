#include "PacketLogin.h"

LoginPacket::LoginPacket()
{
	memset( this, 0x0, sizeof(LoginPacket) );
}

LoginPacket::~LoginPacket()
{
	
}

void LoginPacket::ToInit()
{
	
}

void LoginPacket::ToPrint()
{
	
}

void LoginPacket::SetPacket(BYTE * byData, WORD wSize) 
{	memcpy( this, byData, wSize ); }  // 设置包结构

BYTE * LoginPacket::GetPacket(BYTE * _data, WORD _size ) {
	memcpy(_data, this, sizeof(LoginPacket) );
	return _data; // 给一个指针并获得头指针;
}
WORD LoginPacket::GetPacketSize() { // 取得这个包指针;
	return sizeof(LoginPacket);
}

UINT & LoginPacket::GetUserid()		{  return (m_uiUserid);   	}// 用户;
CHAR * LoginPacket::GetUsername()	{  return (m_szUsername);   }// 名称;
CHAR * LoginPacket::GetPassword()	{  return (m_szPassword);   }// 密码;
CHAR * LoginPacket::GetSSHKey()		{  return (m_szSSHKey);   	}// 键值;
UINT & LoginPacket::GetGameType()	{  return (m_uiGameType);   }// 游戏号;
UINT & LoginPacket::GetLoginType()	{  return (m_uiLoginType);  }// 登陆类型;
CHAR * LoginPacket::GetAddress()	{  return (m_szAddress);  	}// IP地址;
UINT & LoginPacket::GetPort()		{  return (m_uiPort);  		}// 端口;