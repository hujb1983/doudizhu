#ifndef __NetworkSessionList_H_
#define __NetworkSessionList_H_
#include <UtilityInclude.h>
#include <NetworkInclude.h>

class NetworkSessionList : public Double_List_T<NetworkSession>
{
public:
	NetworkSessionList();
	~NetworkSessionList();
	
	void Clear();
	
	inline void Lock() { m_cs.Lock(); }
	inline void Unlock() { m_cs.Unlock(); }

private:
	UtilityMutex m_cs;
};

typedef NetworkSessionList				NETWORKSESSION_LIST;
typedef NetworkSessionList::iterator	NETWORKSESSION_LIST_ITER;

#endif //  __Yond_ini_INCLUDED_
