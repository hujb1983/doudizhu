#ifndef _CommonDefine_H_
#define _CommonDefine_H_
#include "CommonStruct.h"
#include <UtilityInclude.h>
#include <NetworkInclude.h>
#include <MydbcInclude.h>


/*****************************************
	��������
*****************************************/
#define MAX_PORT (0xFFFF)


/*****************************************
	�û����
*****************************************/
enum eUSER_TYPE
{
	UT_TEMP = 1 , 		// ��ʱ��
	UT_USER     ,       //
	UT_GAME     ,
};


/*****************************************
	���������
*****************************************/
enum eSERVER_TYPE
{
	UNKNOWN_SERVER 	 = 0	,
	
	USER_SESSION		, 		// �û���
	AGENT_SERVER		, 		// ���������
	GAME_SERVER 		,		// ��Ϸ������
	DB_SERVER           ,       // ���ݿ������
	LOGIN_SERVER 		,		// ��¼������
	WORLD_SERVER 		,		// ���������
	LOBBY_SERVER 		,		// ����������
	TEMP_SERVER 		,		// ��ʱ��
};


#endif