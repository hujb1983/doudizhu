#include "Handler_Module.h"

/*******************************************************
	FromLobbyToAgent_Onlines_ANC
******************************************************/
void FromLobbyToAgent_Onlines_ANC ( ServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize ) {

    DEBUG_MSG( LVL_DEBUG, "Onlines_ANC to client: %s \n",(char *) pMsg );

    JsonMap js_map;
    if ( js_map.set_json( (char*) pMsg ) == -1 ) {
        return;
    }

    int _userkey(0), _userid(0);
    js_map.ReadInteger( "userkey", _userkey );

    if ( _userkey!=0 )
    {
        UserSession * pSession = g_AgentServer->GetUserSession( _userkey );
        if ( pSession ) {
            _userid = pSession->GetUserid();
            User_Login_Query_Relogin( _userkey , _userid );
        }
        g_AgentServer->SendToClient( _userkey, (BYTE*) pMsg, wSize );
    }
}
