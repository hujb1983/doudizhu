#ifndef _Main_H_
#define _Main_H_
#include <UtilityDefine.h>
#include <UtilityInclude.h>
#include <TemplateCommand.h>
#include "LoginServer.h"
#include "AgentServer.h"
#include "LobbyServer.h"
#include "GameServer.h"
#include "DBServer.h"

BOOL execute_process( TemplateCommand & cmd, BYTE _typeid )
{
	if ( cmd.Find(_typeid)==NULL ) {
		return FALSE;
	}

	pid_t _pid = fork();
	if ( _pid<0 )
	{
		printf("Error in fork()! \n");
		return FALSE;
	}
	else if ( _pid==0 )
	{
		if ( cmd.Find(EM_Login) )
		{
			cmd.ServerRename("./MasterLogin");
			printf( "LoginServer start! \n");
			LoginServer * server = new LoginServer;
			server->StartServer();
			delete server;
			printf( "LoginServer stop! \n");
		}
		else if ( cmd.Find(EM_Agent) )
		{
			cmd.ServerRename("./MasterAgent");
			printf( "AgentServer start! \n");
			AgentServer * server = new AgentServer;
			server->StartServer();
			delete server;
			printf( "AgentServer stop! \n");
		}
		else if ( cmd.Find(EM_Lobby) )
		{
			cmd.ServerRename("./MasterLobby");
			printf( "LobbyServer start! \n");
			LobbyServer * server = new LobbyServer;
			server->StartServer();
			delete server;
			printf( "LobbyServer stop! \n");
		}
		else if ( cmd.Find(EM_Game) )
		{
			cmd.ServerRename("./MasterGame");
			printf( "GameServer start! \n");
			GameServer * server = new GameServer;
			server->StartServer();
			delete server;
			printf( "GameServer stop! \n");
		}
		else if ( cmd.Find(EM_DB) )
		{
			cmd.ServerRename("./MasterDB");
			printf( "DBServer start! \n");
			DBServer * server = new DBServer;
			server->StartServer();
			delete server;
			printf( "DBServer stop! \n");
		}
		return TRUE;
	}
	return FALSE;
}

#endif