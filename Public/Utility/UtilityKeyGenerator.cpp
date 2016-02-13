#include "UtilityKeyGenerator.h"
//#include <vector>
//#include <algorithm>

UtilityKeyGenerator::UtilityKeyGenerator( DWORD dwKeyStart, DWORD dwKeyEnd )
{
	Create(dwKeyStart, dwKeyEnd);

}
VOID UtilityKeyGenerator::Create( DWORD dwKeyStart, DWORD dwKeyEnd )
{
	for( DWORD i = dwKeyStart; i <= dwKeyEnd; ++i ) {
		m_dequeKey.push_back( i );
	}
}

UtilityKeyGenerator::~UtilityKeyGenerator(void)
{
	m_dequeKey.clear();
}

DWORD UtilityKeyGenerator::GetKey()
{
	DWORD key;

	if ( IsEmpty() == TRUE ) {
		return 0;
	}

	m_cs.Lock();

	key = *m_dequeKey.begin();
	m_dequeKey.pop_front();

	m_cs.Unlock();

	return key;
}

BOOL UtilityKeyGenerator::ReserveKey( DWORD key )
{
	BOOL bReserved = FALSE;

	if (IsEmpty() == TRUE) {
		return FALSE;
	}

	m_cs.Lock();

	deque<DWORD>::iterator itr = m_dequeKey.begin();
	while ( itr != m_dequeKey.end() )
	{
		if ( *itr == key )
		{
			bReserved = TRUE;
			m_dequeKey.erase(itr);
			break;
		}
	}

	return bReserved;
}


BOOL UtilityKeyGenerator::IsEmpty()
{
	return m_dequeKey.empty() == TRUE;
}

BOOL UtilityKeyGenerator::IsExistKey(DWORD dwKey)
{
	deque<DWORD>::iterator itr = m_dequeKey.begin();

	for (; itr != m_dequeKey.end(); itr++)
	{
		if (*itr == dwKey)
		{
			return TRUE;
		}
	}

	return FALSE;
}

VOID UtilityKeyGenerator::RestoreKey(DWORD key)
{
	UtilityGuard sync_cs(m_cs);
	m_dequeKey.push_front(key);
}

size_t UtilityKeyGenerator::GetSize()
{
	UtilityGuard sync_cs(m_cs);
	return m_dequeKey.size();
}



