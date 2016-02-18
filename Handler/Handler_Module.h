#ifndef _Handler_Module_H_
#define _Handler_Module_H_
#include <TemplateServerSession.h>
#include <MydbcInclude.h>
#include <CommonProtocol.h>
#include "ProtocolGame.h"
#include "ProtocolLogin.h"
#include "ProtocolUpdate.h"

/*****************************************************
    Handler_CalledBank.cpp
*****************************************************/
void FromClientToAgent_CalledBank_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromGameToAgent_CalledBank_BRD(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromAgentToGame_CalledBank_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);

/*****************************************************
    Handler_CalledLicense.cpp
*****************************************************/
void FromGameToAgent_CalledLicense_BRD(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromAgentToGame_CalledLicense_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);

/*****************************************************
    Handler_CreateBank.cpp
*****************************************************/
void FromGameToAgent_CreateBank_BRD(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromAgentToGame_CreateBank_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);

/*****************************************************
    Handler_Discards.cpp
*****************************************************/
void FromClientToAgent_Discards_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromGameToAgent_Discards_BRD(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromAgentToGame_Discards_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);

/*****************************************************
    Handler_DiscardsLicense.cpp
*****************************************************/
void FromGameToAgent_DiscardsLicense_BRD(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromAgentToGame_DiscardsLicense_BRD(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);

/*****************************************************
    Handler_FastGame.cpp
*****************************************************/
void FromClientToLobby_FastGame_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);

/*****************************************************
    Handler_InitCards.cpp
*****************************************************/
void FromGameToAgent_InitCards_BRD(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);

/*****************************************************
    Handler_JoinTable.cpp
*****************************************************/
void FromClientToAgent_JoinTable_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromLobbyToAgent_JoinTable_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromGameToAgent_JoinTable_BRD(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);

/*****************************************************
    Handler_Login.cpp
*****************************************************/
void FromClientToAgent_Login_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromAgentToLobby_Login_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromLobbyToDB_Login_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromDBToDB_Login_DBR(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromDBToLobby_Login_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromLobbyToAgent_Login_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromDBToDB_GamePacket_DBR(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromDBToLobby_GamePacket_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromLobbyToAgent_GamePacket_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);

/*****************************************************
    Handler_Onlines.cpp
*****************************************************/
void FromLobbyToAgent_Onlines_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);

/************************************************
    Handler_WeekRank.cpp
************************************************/
void FromClientToLogin_PreLogin_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromLoginToDB_PreLogin_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromDBToDB_PreLogin_DBR(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromDBToLogin_PreLogin_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);

/*****************************************************
    Handler_QuitTable.cpp
*****************************************************/
void FromClientToAgent_QuitTable_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromGameToAgent_QuitTable_BRD(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromAgentToGame_QuitTable_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);

/*****************************************************
    Handler_Reminder.cpp
*****************************************************/
void FromClientToAgent_Reminder_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromAgentToGame_Reminder_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromGameToAgent_Reminder_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);

/*****************************************************
    Handler_Settlement.cpp
*****************************************************/
void FromAgentToGame_Settlement_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);

/*****************************************************
    Handler_StartGame.cpp
*****************************************************/
void FromClientToAgent_StartGame_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromGameToAgent_StartGame_BRD(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromAgentToGame_StartGame_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);

/*****************************************************
    Handler_Trusteeship.cpp
*****************************************************/
void FromClientToAgent_Trusteeship_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromGameToAgent_Trusteeship_BRD(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromAgentToGame_Trusteeship_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);

/************************************************
    Handler_FieldsInfo.cpp
************************************************/
void FromLobbyToAgent_FieldsInfo_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromLobbyToDB_FieldsInfo_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromDBToDB_FieldsInfo_DBR(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromDBToLobby_FieldsInfo_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);

/************************************************
    Handler_RoomsInfo.cpp
************************************************/
void FromLobbyToAgent_RoomsInfo_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromLobbyToDB_RoomsInfo_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromDBToDB_RoomsInfo_DBR(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromDBToLobby_RoomsInfo_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);

/************************************************
    Handler_DayRank.cpp
************************************************/
void FromLobbyToAgent_DayRanks_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromLobbyToDB_DayRanks_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromDBToDB_DayRanks_DBR(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromDBToLobby_DayRanks_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);

/************************************************
    Handler_WeekRank.cpp
************************************************/
void FromLobbyToAgent_WeekRanks_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromLobbyToDB_WeekRanks_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);
void FromDBToDB_WeekRanks_DBR(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize );
void FromDBToLobby_WeekRanks_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize);

#endif
