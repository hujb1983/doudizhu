#include "MydbcDatabase.h"
#include "MydbcMysql.h"
#include "MydbcQueryExecuteProcessor.h"
#include "MydbcInterface.h"
#include "MydbcQueryResult.h"

MydbcQueryExecuteProcessor::MydbcQueryExecuteProcessor( MydbcDatabase & psdb, MydbcInterface * pDBCInstance  )
	:	m_psdb ( psdb ),
		m_pDBCInstance ( pDBCInstance )
{
}

MydbcQueryExecuteProcessor::~MydbcQueryExecuteProcessor(void)
{
}

VOID MydbcQueryExecuteProcessor::EndThread()
{
}

DWORD MydbcQueryExecuteProcessor::run()
{
	MydbcQueryResult * pQuery = NULL;

	UtilityMutex & lockWake = m_psdb.m_lockWakeup;
	UtilityCond & condWake = m_psdb.m_condWakeup;

	UtilityMutex *& qcs = m_psdb.m_pQueryCS;
	UtilityMutex *& qrcs = m_psdb.m_pQueryResultCS;
	
	BOOL bEventInfiniteLoop = TRUE;
	
	while(bEventInfiniteLoop)
	{
		lockWake.Lock();
		condWake.Wait(&lockWake);
		lockWake.Unlock();


		if ( m_psdb.m_bEndProcess )
			break;	
		
		BOOL bQueryInfiniteLoop = TRUE;
		while(bQueryInfiniteLoop)
		{
			if( m_psdb.m_pQueryList->GetCount() == 0 )	break;


			qcs->Lock();
			pQuery = m_psdb.m_pQueryList->DeleteHead();
			qcs->Unlock();

			if( !pQuery )
				break;
			
			switch( pQuery->GetQueryType() )
			{
			case eGeneralQuery:
				{
					/// Execute QueryResult and push in QueryResultList
					if( !m_pDBCInstance->Execute( pQuery ) )
					{
						//!
						// nothing to do
					}
				}
				break;
			case eLargeQuery:
				{
					/// Execute QueryResult and push in QueryResultList
					if( !m_pDBCInstance->ExecuteLargeData( pQuery ) )
					{
						// !
						// nothing to do
					}
				}
				break;
			}
			
			qrcs->Lock();
			m_psdb.m_pQueryResultPushList->AddTail( pQuery );
			
			//m_psdb.m_pQueryResultPushList->push_back( pQuery );
			
			qrcs->Unlock();
			
		}
	}

	return 0;
}


