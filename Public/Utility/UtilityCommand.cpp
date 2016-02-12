#include <UtilityDefine.h>
#include "UtilityCommand.h"

UtilityCommand::UtilityCommand()
{

}

UtilityCommand::~UtilityCommand()
{
    BASE_COMMAND * pFunc;
    MAP_COMMAND_IT itr;
    MAP_COMMAND_IT itr_bk;

    for(itr = m_mCommand.begin(); itr != m_mCommand.end();)
    {
        pFunc = itr->second;
        if(pFunc)
        {
            delete pFunc;
            pFunc = NULL;
        }
        itr_bk = itr;
        itr++;
        m_mCommand.erase(itr_bk);
    }

    m_mCommand.clear();
}

BOOL UtilityCommand::Add( BYTE _typeid, BASE_COMMAND * _pCommand )
{
    MAP_COMMAND_IT it;
    BASE_COMMAND * pTemp = NULL;

    if(!m_mCommand.empty()) {
        it = m_mCommand.find( _typeid );
        if(it != m_mCommand.end()) {
            pTemp = it->second;
        }
    }

    if( pTemp!=NULL ) {
        return FALSE;
    }

    m_mCommand.insert ( MAP_COMMAND_VT( _typeid, _pCommand ) );
    return TRUE;
}


BASE_COMMAND * UtilityCommand::Find(const BYTE _typeid)
{
    MAP_COMMAND_IT it;
    BASE_COMMAND * pTemp = NULL;

    if( !m_mCommand.empty() )
    {
        it = m_mCommand.find( _typeid );
        if(it != m_mCommand.end())	{
            pTemp = it->second;
        }
    }

    return pTemp;
};
