#include "TemplateCommand.h"

TemplateCommand::TemplateCommand()
{
    m_MainAgrc = 0;
	m_MainAgrv = NULL;
}

TemplateCommand::~TemplateCommand()
{

}

BOOL TemplateCommand::ToMain( int argc, char ** argv )
{
    m_MainAgrc = argc;
	m_MainAgrv = argv;

	int result = 0;
	opterr = 0;

	if ( argc == 1 ) {
        return OnHelp( argc, argv );
	}

	while( (result = getopt( argc, argv, "c:hD::s")) != -1)
	{
		switch( result )
		{
			case 'c': {
				return TRUE;
            }

			case 'h': {
				return OnHelp( argc, argv );
			}

			case 's': {
				return TRUE;
            }

            case 'D': {
                if ( optarg ) {
                    return OnServer( argc, argv, optarg );
                }

                fprintf(stderr, "Sorry! This is the wrong command. \n");
                return OnHelp( argc, argv );
            }

			case '?': {
                return OnHelp( argc, argv );
            }

			default: {
				return OnHelp( argc, argv );
			}
		}
	}

	return FALSE;
}

BOOL TemplateCommand::OnHelp( int argc, char ** argv )	//帮助
{
	fprintf( stderr, "Usage: %s [-c] [-h] [-s] [-D] arg. \n", argv[0] );
	fprintf( stderr, "       -c : -c start : start. restart. stop. \n" );
	fprintf( stderr, "       -h : -h : Help. \n" );
	fprintf( stderr, "       -s : -s cpu : session. memory. cpu. \n" );
	fprintf( stderr, "       -D : -Dlogin : login. lobby. agent. game. db. \n" );
    return FALSE;
}

BOOL TemplateCommand::OnStart  ( int argc, char ** argv )	//开始所有服务器
{

}

BOOL TemplateCommand::OnRestart( int argc, char ** argv ) //重启指定服务器
{

}

BOOL TemplateCommand::OnStop   ( int argc, char ** argv ) //停止所有服务器
{

}

BOOL TemplateCommand::OnShow   ( int argc, char ** argv ) //显示资源
{

}

BOOL TemplateCommand::OnCount  ( int agrc, char ** agrv ) //计算在线人数
{

}

BOOL TemplateCommand::OnStat   ( int agrc, char ** agrv ) //统计内存和CPU使用情况
{

}

BOOL TemplateCommand::OnServer ( int agrc, char ** agrv, char * name) //统计内存和CPU使用情况
{
    BASE_COMMAND * pCmd = new BASE_COMMAND;
    pCmd->CmdText[0] = '\0';
    strcat( pCmd->CmdText, optarg );
    pCmd->CmdSize = strlen( pCmd->CmdText );
    if ( strcmp(pCmd->CmdText, "login")==0 ) {
        Add( EM_Login, pCmd );
        return TRUE;
    }
    else if ( strcmp(pCmd->CmdText, "agent")==0 ) {
        Add( EM_Agent, pCmd );
        return TRUE;
    }
    else if ( strcmp(pCmd->CmdText, "lobby")==0 ) {
        Add( EM_Lobby, pCmd );
        return TRUE;
    }
    else if ( strcmp(pCmd->CmdText, "game")==0 ) {
        Add( EM_Game, pCmd );
        return TRUE;
    }
    else if ( strcmp(pCmd->CmdText, "db")==0 )  {
        Add( EM_DB, pCmd );
        return TRUE;
    }
    return FALSE;
}

void TemplateCommand::ServerRename(const char * rename)
{
	if ( m_MainAgrv )
    {
        int sumLen = 0;
        for( int i=0; i<m_MainAgrc; ++i )
        {
            sumLen = strlen( m_MainAgrv[i] );
            memset( m_MainAgrv[i], 0x0, sumLen );
        }

        strcat(m_MainAgrv[0], rename);
	}
}
