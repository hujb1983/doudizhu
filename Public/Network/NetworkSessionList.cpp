#include "NetworkSessionList.h"

NetworkSessionList::NetworkSessionList() 
{
	
}

NetworkSessionList::~NetworkSessionList()
{
	Clear();
}

void NetworkSessionList::Clear()
{
	NETWORKSESSION_LIST_ITER it;
	NetworkSession *pSession; 

	this->Lock();
	while ( !this->empty() )
	{
		pSession = this->pop_front();
		if ( pSession )
			delete pSession;		
	}
	Unlock();
}
 