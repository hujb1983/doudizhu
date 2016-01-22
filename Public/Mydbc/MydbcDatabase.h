#ifndef _MydbcDatabase_H_
#define _MydbcDatabase_H_

#include <UtilityInclude.h>
#include <UtilityDefine.h>
#include "MydbcDatabaseDefine.h"

class MydbcQueryResult;
class MydbcInterface;

//typedef std::list<QueryResult *> QUERYRESULT_LIST;
//typedef QUERYRESULT_LIST::iterator QUERYRESULT_ITER;

class MydbcDatabase
{
	friend class						QueryExecuteProcessor;
	
public:
	MydbcDatabase(void);
	~MydbcDatabase(void);

	BOOL								Initialize( MydbcDatabaseDesc & desc );
	void								Update();
	void								Release();

	BOOL								DBQuery( MydbcQueryResult * pQuery );

	DWORD								GetBufferedQueryNum() { return m_pQueryList->GetCount(); }
private:

	inline	void						SwitchQueryResultList() {	
										UtilityLinkedList<MydbcQueryResult *> * pTmpList = m_pQueryResultPushList; m_pQueryResultPushList = m_pQueryResultPopList; m_pQueryResultPopList = pTmpList;	}

	MydbcInterface **					m_ppDBCInstance;
	UtilityThreadPool *					m_pThreadPool;
	fnCallBackMessage					m_fnErrorMessage;
	fnCallBackQueryResult				m_fnQueryResult;
	WORD								m_wQueryProcessorNum;
	BOOL								m_bEndProcess;

	UtilityCond							m_condWakeup;
	UtilityMutex						m_lockWakeup;	

	UtilityMutex *						m_pQueryCS;
	UtilityMutex *						m_pQueryResultCS;
	
	UtilityLinkedList<MydbcQueryResult *> * m_pQueryList;
	UtilityLinkedList<MydbcQueryResult *> * m_pQueryResultPushList;
	UtilityLinkedList<MydbcQueryResult *> * m_pQueryResultPopList;
	
	//QUERYRESULT_LIST *				m_pQueryResultPushList;
	//QUERYRESULT_LIST *				m_pQueryResultPopList;
	
	DWORD								m_dwDummy;
	
	friend class MydbcQueryExecuteProcessor;
};


#endif // __HYDATABASE_H_INCLUDED__
	
	
