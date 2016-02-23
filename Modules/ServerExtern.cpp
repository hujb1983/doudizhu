#include "LoginServer.h"
#include "AgentServer.h"
#include "LobbyServer.h"
#include "GameServer.h"
#include "DBServer.h"

LoginServer * g_pLoginServer = NULL;
AgentServer * g_pAgentServer = NULL;
LobbyServer * g_pLobbyServer = NULL;
GameServer * g_pGameServer = NULL;
DBServer * g_pDBServer = NULL;
LobbyUpdate * g_pLobbyUpdate = NULL;
