#include "UtilityTimer.h"

UtilityTimer::UtilityTimer(UINT Interval)
{
	m_StartInterval = 0;
	m_uiInterval = Interval;
}

UtilityTimer::~UtilityTimer()
{
	
}

DWORD UtilityTimer::GetTickCount()
{
	static long long t0 = 0;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	long long t = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);

	if (t0 == 0)
		t0 = t;
	return t - t0;
}

void UtilityTimer::Start()
{
	m_StartInterval = UtilityTimer::GetTickCount();
}
	
BOOL UtilityTimer::Update(UINT uiTicket)
{
	if (uiTicket==0) {
		uiTicket = UtilityTimer::GetTickCount();
	}
	
	UINT nowTimes = m_StartInterval + m_uiInterval;
	if ( nowTimes < uiTicket) {
		return FALSE;
	}
	return TRUE;
}
	
