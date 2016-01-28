#ifndef _CommonDefine_H_
#define _CommonDefine_H_
#include "CommonStruct.h"
#include <UtilityInclude.h>
#include <NetworkInclude.h>
#include <MydbcInclude.h>


/*****************************************
	常量定义
*****************************************/
#define MAX_PORT (0xFFFF)


/*****************************************
	用户类别
*****************************************/
enum eUSER_TYPE
{
	UT_TEMP = 1 , 		// 临时性
	UT_USER     ,       //
	UT_GAME     ,
};


/*****************************************
	服务器类别
*****************************************/
enum eSERVER_TYPE
{
	UNKNOWN_SERVER 	 = 0	,
	
	USER_SESSION		, 		// 用户的
	AGENT_SERVER		, 		// 代理服务器
	GAME_SERVER 		,		// 游戏服务器
	DB_SERVER           ,       // 数据库服务器
	LOGIN_SERVER 		,		// 登录服务器
	WORLD_SERVER 		,		// 聊天服务器
	LOBBY_SERVER 		,		// 大厅服务器
	TEMP_SERVER 		,		// 临时的
};


#endif