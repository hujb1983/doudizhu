#ifndef _UtilityThread_H_
#define _UtilityThread_H_

#include <UtilityDefine.h>

typedef int (*fcallback_running)();

class UtilityThread
{ 
public: 
    UtilityThread(); 
    virtual ~UtilityThread(); 
 
    void Start(BOOL bSuspend = FALSE);
	virtual void EndThread() = 0;

	virtual void SuspendThread();
	virtual void ResumeThread();
	
	pthread_t GetHandle() { return m_hThread; }
	
protected:
	virtual DWORD	run() = 0;
	static void * m_fnThread(void * pt);
	
private: 
	pthread_t	m_hThread;
	BOOL		m_bSuspend;
};

#endif //  __Yond_ini_INCLUDED_
