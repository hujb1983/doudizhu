#ifndef _UtilityThreadPool_H_
#define _UtilityThreadPool_H_

//=======================================================================================================================
/// IThreadInterface 
/**
	@author
	@since
	@remarks
	@history
*/
//=======================================================================================================================

#include <vector>
using namespace std;


class UtilityThreadPool;

class UtilityThreadPool
{
public:
	UtilityThreadPool();
	~UtilityThreadPool();

	void								AddThread( 
										UtilityThread * pThread, 
										BOOL bSuspend = FALSE );
										
	inline void							SetAutoRelease( BOOL bVal ) { m_bAutoRelease = bVal; }
	void								BatchStopThread();
	void								BatchStartThread();
	void								Release();

private:
	vector<UtilityThread *>				m_pThreadList;
	BOOL								m_bAutoRelease;
};




#endif // __THREADPOOL_H__
	
	

