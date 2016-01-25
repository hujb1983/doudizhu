#ifndef __NetworkConnector_H_
#define __NetworkConnector_H_
#include <UtilityDefine.h>
#include <NetworkDefine.h>

class NetworkSyncHandler;
class NetworkSession;
class NetworkSessionList;

class NetworkConnector
{
	friend void * connect_thread(void * param);
	
public:
	NetworkConnector(void);
	~NetworkConnector(void);
	
	void Init( NetworkSyncHandler * pSync );
	void Connect( NetworkSession * pSession);
	
	void Shutdown();
	
public:	
	NetworkSyncHandler * m_pSync;
	NetworkSessionList * m_pConnectingList;
	
	pthread_t 	m_hThread;
	BOOL 		m_bShutdown;
	sem_t 		m_semConnect;
};

#endif //  __CONNECTOR_H_INCLUDED_
