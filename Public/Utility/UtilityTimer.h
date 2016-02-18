#ifndef _UtilityTimer_H_
#define _UtilityTimer_H_
#include "UtilityDefine.h"
using namespace std;

class UtilityTimer
{ 
public:
	UtilityTimer(UINT Interval = 0);
	~UtilityTimer();
	
public:	
	static DWORD GetTickCount();
	
public:	
	void Start();
	virtual BOOL Update(UINT uiTicket = 0);
	
private:
	UINT m_StartInterval;
	UINT m_uiInterval;
	
};

#endif //  __YOND_INI_INCLUDED_
