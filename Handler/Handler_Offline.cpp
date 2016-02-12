#include "Handler_Module.h"

/*****************************************************
    FromAgentToGame_Offline_BRD
*****************************************************/
void FromAgentToGame_Offline_BRD ( TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
    DEBUG_MSG( LVL_DEBUG, "Offline_BRD to recv: %s \n", pMsg );

    JsonMap js_map;
    if ( js_map.set_json( (char *) pMsg ) == -1 ) {
        return;
    }

    int _userkey(0);
    js_map.ReadInteger( "userkey",  _userkey );

    UserSession * pSession = NULL;
    pSession = g_AgentServer->GetUserSession( _userkey );
    if ( pSession ) {
        pSession->LeaveGame();
    }
}