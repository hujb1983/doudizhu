#ifndef _UtilityCommand_H_
#define _UtilityCommand_H_

#include <vector>
using namespace std;

class BASE_COMMAND
{
public:

	BASE_COMMAND() {
        memset( CmdText, 0x0, 0xff);
	}
	virtual ~BASE_COMMAND() { }

	BYTE CmdSize;
	CHAR CmdText[0xff];
};

class UtilityCommand
{
    typedef hash_map< BYTE, BASE_COMMAND* >	MAP_COMMAND;
    typedef MAP_COMMAND::iterator			MAP_COMMAND_IT;
    typedef MAP_COMMAND::value_type		    MAP_COMMAND_VT;

public:
	UtilityCommand();
	virtual ~UtilityCommand();

	BOOL Add( BYTE _typeid, BASE_COMMAND * pCmd );
    BASE_COMMAND * Find(const BYTE _typeid);

private:
	MAP_COMMAND							m_mCommand;
	MAP_COMMAND_IT						m_itr;
};

#endif // __THREADPOOL_H__

