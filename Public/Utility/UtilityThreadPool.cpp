#include <UtilityDefine.h>
#include "UtilityThread.h"
#include "UtilityThreadPool.h"


UtilityThreadPool::UtilityThreadPool()
	: m_bAutoRelease	( TRUE )
{
}

UtilityThreadPool::~UtilityThreadPool()
{
	Release();
}
	

void UtilityThreadPool::Release()
{
	BatchStopThread();
	
	UtilityThread * pThread = NULL;
	for ( int i = 0; i < m_pThreadList.size(); i ++ )
	{
		pThread = m_pThreadList[i];
		if( m_bAutoRelease )
			delete pThread;
	}

	m_pThreadList.clear();
}

void UtilityThreadPool::AddThread( UtilityThread * pThread, BOOL bSuspend )
{
	m_pThreadList.push_back(pThread);
	pThread->Start( bSuspend );
}

void UtilityThreadPool::BatchStopThread()
{
	UtilityThread * pThread = NULL;
	for ( int i = 0; i < m_pThreadList.size(); i ++ )
	{
		pThread = m_pThreadList[i];
		pThread->EndThread();

#if defined(WIN32) || defined( WIN64 )
		WaitForSingleObject(pThread->GetHandle(), INFINITE);
#else
		pthread_join(pThread->GetHandle(), NULL);
#endif

	}
}

void UtilityThreadPool::BatchStartThread()
{
	UtilityThread * pThread = NULL;
	for ( int i = 0; i < m_pThreadList.size(); i ++ )
	{
		pThread = m_pThreadList[i];
		pThread->ResumeThread();
	}
}

 

