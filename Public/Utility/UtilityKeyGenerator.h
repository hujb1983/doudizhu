#ifndef _UtilityKeyGenerator_H_
#define _UtilityKeyGenerator_H_

#include <UtilityDefine.h>
#include <UtilityMutex.h>
using namespace std;

class UtilityKeyGenerator
{
private:
    UtilityCond				m_cd;
	UtilityMutex			m_cs;
	deque<DWORD>			m_dequeKey;
	DWORD 					m_dwKeyStart;
	DWORD					m_dwKeyEnd;

public:
	UtilityKeyGenerator() {}
	UtilityKeyGenerator(DWORD dwKeyStart, DWORD dwKeyEnd);
	~UtilityKeyGenerator(void);

	VOID					Create( DWORD dwKeyStart, DWORD dwKeyEnd );
	DWORD					GetKey();
	BOOL					ReserveKey(DWORD key);
	VOID					RestoreKey(DWORD key);
	BOOL					IsEmpty();
	BOOL					IsExistKey(DWORD dwKey);
	size_t					GetSize();
};

#endif // _OBJKEYGENERATOR_H_INCLUDED_
