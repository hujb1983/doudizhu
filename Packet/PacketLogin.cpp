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
{	memcpy( this, byData, wSize ); }  // ���ð��ṹ

BYTE * LoginPacket::GetPacket(BYTE * _data, WORD _size ) {
	memcpy(_data, this, sizeof(LoginPacket) );
	return _data; // ��һ��ָ�벢���ͷָ��;
}
WORD LoginPacket::GetPacketSize() { // ȡ�������ָ��;
	return sizeof(LoginPacket);
}

UINT & LoginPacket::GetUserid()		{  return (m_uiUserid);   	}// �û�;
CHAR * LoginPacket::GetUsername()	{  return (m_szUsername);   }// ����;
CHAR * LoginPacket::GetPassword()	{  return (m_szPassword);   }// ����;
CHAR * LoginPacket::GetSSHKey()		{  return (m_szSSHKey);   	}// ��ֵ;
UINT & LoginPacket::GetGameType()	{  return (m_uiGameType);   }// ��Ϸ��;
UINT & LoginPacket::GetLoginType()	{  return (m_uiLoginType);  }// ��½����;
CHAR * LoginPacket::GetAddress()	{  return (m_szAddress);  	}// IP��ַ;
UINT & LoginPacket::GetPort()		{  return (m_uiPort);  		}// �˿�;