#ifndef _ProtocolServer_H_
#define _ProtocolServer_H_


//
enum eServerType_PROTOCOL
{
	FromClientToLogin_PID = 700,// 登录类型
	FromLoginToClient_PID = 700,// 与老版本类同
	
	FromClientToAgent_PID = 800,// 游戏类型
	FromAgentToClient_PID = 800,// 与老版本类同

	FromLoginToDB_PID = 1024,// Login To DB
	FromAgentToLobby_PID,//Agent To 
	FromLobbyToDB_PID,//Lobby To DB
	FromDBToLobby_PID,//DB To Lobby
	FromLobbyToAgent_PID,//Lobby To Agent
	FromDBToLogin_PID,//DB To Login
	FromDBToDB_PID,//DB To DB 
};

#endif // _ProtocolGame_H_