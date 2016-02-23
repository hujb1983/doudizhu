#ifndef _LobbyServer_H_
#define _LobbyServer_H_
#include <TemplateSeasoning.h>
#include <TemplateSessionFactory.h>
#include <TemplatePacketHandler.h>
#include <TemplateMainServer.h>
#include "PacketHandler.h"
#include "LobbyUpdate.h"

class LobbyServer : public TemplateMainServer
{
public:
	LobbyServer()
	{
	    m_pLobbyUpdate = NULL;
	}

	~LobbyServer()
	{
	    SAFE_DELETE( m_pLobbyUpdate );
	}

	virtual BOOL Init()
	{
		printf( "LobbyServer Init! \n");

		InitConfig( );
		InitDafaultConfig( "./ServerConfig.ini" );

		SetServerType(LOBBY_SERVER);
		LoadServerConfig( "./ServerConfig.ini" );
		LoadCompleteServerConfig();

		printf( "LobbyServer Init! \n");
		if ( !TemplateMainServer::Init() ) {
			return FALSE;
		}

		TemplateSeasoning system;
		system.GetOpenDatabase() = FALSE;

		// Initialize the PacketHandler;
        TemplatePacketHandler::Init();
		PacketHandler handler;

		// Initialize all the data;
		m_pLobbyUpdate = new LobbyUpdate;
		m_pLobbyUpdate->StartTimer();
		m_pLobbyUpdate->SendToDB();
		return TRUE;
	}

    virtual BOOL Update(DWORD dwTicket)
    {
        TemplateMainServer::Update( dwTicket );

        if ( m_pLobbyUpdate ) {
            m_pLobbyUpdate->UpdateDate( dwTicket );
        }

        return TRUE;
    }

	LobbyUpdate * GetLobbyUpdate() {
		return m_pLobbyUpdate;
	}
	
private:
    LobbyUpdate * m_pLobbyUpdate;
};

extern LobbyServer * g_pLobbyServer;

#endif

