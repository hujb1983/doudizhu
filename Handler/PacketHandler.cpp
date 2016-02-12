#include "PacketHandler.h"
#include "Handler_Module.h"

PacketHandler::PacketHandler(void)
{
	Register_Client();
	Register_Login();
	Register_Agent();
	Register_Lobby();
	Register_Games();
	Register_DB();
}

PacketHandler::~PacketHandler(void)
{
	
}

BOOL PacketHandler::Register_Client()
{
	/*
	AddHandler_Client( Games_Protocol,  Called_REQ,  	 FromClientToAgent_CalledBank_REQ 	);	
	AddHandler_Client( Games_Protocol,  Discards_REQ, 	 FromClientToAgent_Discards_REQ 	);
	AddHandler_Client( Games_Protocol,  FastGame_REQ, 	 FromClientToLobby_FastGame_REQ 	);
	AddHandler_Client( Games_Protocol,  JoinTable_REQ, 	 FromClientToAgent_JoinTable_REQ 	);	
	AddHandler_Client( Update_Protocol, OnlineInfo_SYN,	 FromLobbyToAgent_Onlines_ANC 		);
	AddHandler_Client( Games_Protocol, 	QuitTable_REQ, 	 FromClientToAgent_QuitTable_REQ 	);
	AddHandler_Client( Games_Protocol, 	Reminder_REQ,	 FromClientToAgent_Reminder_REQ 	);
	AddHandler_Client( Games_Protocol, 	StartGame_REQ,	 FromClientToAgent_StartGame_REQ	);
	AddHandler_Client( Games_Protocol, 	Trusteeship_REQ, FromClientToAgent_Trusteeship_REQ 	);
	*/
}

BOOL PacketHandler::Register_Login()
{
	AddHandler_Login( Login_Protocol,	PreLogin_REQ,	FromLoginToDB_PreLogin_REQ	);
}

BOOL PacketHandler::Register_Agent()
{
	/*
	AddHandler_Agent( Games_Protocol, CreateTable_DBR,		FromAgentToGame_CreateBank_REQ		);
	AddHandler_Agent( Games_Protocol, CalledLicense_REQ, 	FromAgentToGame_CalledLicense_REQ 	);
	AddHandler_Agent( Games_Protocol, Discards_REQ, 		FromAgentToGame_Discards_REQ 		);
	AddHandler_Agent( Games_Protocol, DiscardsLicense_BRD, 	FromAgentToGame_DiscardsLicense_BRD );
	AddHandler_Agent( Games_Protocol, QuitTable_REQ, 		FromAgentToGame_QuitTable_REQ 		);
	AddHandler_Agent( Games_Protocol, Reminder_REQ, 		FromAgentToGame_Reminder_REQ 		);
	AddHandler_Agent( Games_Protocol, Settlement_REQ, 		FromAgentToGame_Settlement_REQ 		);
	AddHandler_Agent( Games_Protocol, StartGame_REQ, 		FromAgentToGame_StartGame_REQ 		);
	AddHandler_Agent( Games_Protocol, Trusteeship_REQ, 		FromAgentToGame_Trusteeship_REQ 	);
	*/
}
	
BOOL PacketHandler::Register_Lobby()
{
	/*
	AddHandler_Lobby( Games_Protocol,  JoinTable_ANC, 	FromLobbyToAgent_JoinTable_ANC 	);
	AddHandler_Lobby( Update_Protocol, WeekRanks_ANC,  	FromLobbyToAgent_WeekRank_ANC 	);
	AddHandler_Lobby( Update_Protocol, WeekRanks_SYN, 	FromLobbyToDB_WeekRanks_REQ 	);
	AddHandler_Lobby( Update_Protocol, TablesInfo_ANC, 	FromLobbyToAgent_TablesInfo_ANC );
	AddHandler_Lobby( Update_Protocol, TablesInfo_SYN, 	FromLobbyToDB_TablesInfo_REQ 	);
	AddHandler_Lobby( Update_Protocol, DayRanks_ANC, 	FromLobbyToAgent_DayRanks_ANC 	);
	AddHandler_Lobby( Update_Protocol, DayRanks_SYN, 	FromLobbyToDB_DayRanks_REQ 		);
	AddHandler_Lobby( Update_Protocol, RoomsInfo_ANC, 	FromLobbyToAgent_RoomsInfo_ANC 	);
	AddHandler_Lobby( Update_Protocol, RoomsInfo_SYN, 	FromLobbyToDB_RoomsInfo_REQ		);
	*/
}

BOOL PacketHandler::Register_Games()
{
	/*
	AddHandler_Games( Games_Protocol, Called_BRD, 			FromGameToAgent_CalledBank_BRD 		);	
	AddHandler_Games( Games_Protocol, CalledLicense_BRD, 	FromGameToAgent_CalledLicense_BRD 	);
	AddHandler_Games( Games_Protocol, CreateBank_BRD, 		FromGameToAgent_CreateBank_BRD 		);
	AddHandler_Games( Games_Protocol, Discards_BRD, 		FromGameToAgent_Discards_BRD 		);
	AddHandler_Games( Games_Protocol, DiscardsLicense_BRD, 	FromGameToAgent_DiscardsLicense_BRD );
	AddHandler_Games( Games_Protocol, InitCards_BRD, 		FromGameToAgent_InitCards_BRD 		);
	AddHandler_Games( Games_Protocol, JoinTable_BRD, 		FromGameToAgent_JoinTable_BRD 		);
	AddHandler_Games( Games_Protocol, Reminder_ANC, 		FromGameToAgent_Reminder_ANC 		);
	AddHandler_Games( Games_Protocol, Trusteeship_BRD, 		FromGameToAgent_Trusteeship_BRD 	);
	AddHandler_Games( Games_Protocol, StartGame_BRD, 		FromGameToAgent_StartGame_BRD 		);
	AddHandler_Games( Games_Protocol, QuitTable_BRD, 		FromGameToAgent_QuitTable_BRD 		);
	*/	
}

BOOL PacketHandler::Register_DB()
{
	/*
	AddHandler_DB( Login_Protocol,  PreLogin_ANC,  	FromDBToLogin_PreLogin_ANC 	 );
	AddHandler_DB( Login_Protocol,  PreLogin_DBR,  	FromDBToDB_PreLogin_DBR 	 );
	AddHandler_DB( Update_Protocol, RoomsInfo_DBR, 	FromDBToDB_RoomsInfo_DBR 	 );
	AddHandler_DB( Update_Protocol, RoomsInfo_ANC, 	FromDBToLobby_RoomsInfo_ANC  );
	AddHandler_DB( Update_Protocol, DayRanks_DBR,  	FromDBToDB_DayRanks_DBR 	 );
	AddHandler_DB( Update_Protocol, DayRanks_ANC,  	FromDBToLobby_DayRanks_ANC 	 );
	AddHandler_DB( Update_Protocol, TablesInfo_DBR, FromDBToDB_TablesInfo_DBR 	 );
	AddHandler_DB( Update_Protocol, TablesInfo_ANC, FromDBToLobby_TablesInfo_ANC );
	AddHandler_DB( Update_Protocol, WeekRanks_DBR, 	FromDBToDB_WeekRanks_DBR 	 );
	AddHandler_DB( Update_Protocol, WeekRanks_ANC, 	FromDBToLobby_WeekRanks_ANC  );
	*/
}