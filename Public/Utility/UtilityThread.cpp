#include "UtilityThread.h"

void * UtilityThread::m_fnThread( void * pt )
{
	UtilityThread * pThis = (UtilityThread *)pt;
	DWORD rt = pThis->run();
	pthread_exit(0);
}

UtilityThread::UtilityThread()
:	m_hThread ( 0 ) 
,	m_bSuspend ( 0 )
{
}

UtilityThread::~UtilityThread()
{
}

void UtilityThread::Start( BOOL bSuspend )
{
	assert( 0 == m_hThread );
	if( 0 == m_hThread )
	{
		m_bSuspend = bSuspend;
		pthread_create( &m_hThread, NULL, m_fnThread, (void*)this);
	}
}

void UtilityThread::SuspendThread()
{
	m_bSuspend = true;         
}

void UtilityThread::ResumeThread()
{
	m_bSuspend = false;         
}

