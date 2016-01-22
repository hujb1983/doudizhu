#ifndef __MydbcQueryExecuteProcessor_H_
#define __MydbcQueryExecuteProcessor_H_

#include <UtilityDefine.h>

#define __DISABLE_COPY(className)					\
		private:									\
			className( const className &);			\
			void operator = ( const className &)

class MydbcInterface;
class MydbcDatabase;
//=======================================================================================================================
/// 
/**
	@author
	@since
	@remarks
			- WakeUp 
			- QueryExecuteProcessor 
			- IDBCInterface->Execute(query)
	@note
			- QueryExecuteProcessor 
*/
//=======================================================================================================================
class MydbcQueryExecuteProcessor :	public UtilityThread
{
public:
	MydbcQueryExecuteProcessor( MydbcDatabase & psdb, MydbcInterface * pDBCInstance );
	virtual ~MydbcQueryExecuteProcessor(void);

	virtual VOID EndThread();
	virtual DWORD run();

private:
	MydbcDatabase & m_psdb;
	MydbcInterface * m_pDBCInstance;

	__DISABLE_COPY(MydbcQueryExecuteProcessor);
};


#endif // __QUERY_EXECUTE_PROCESSOR_H__
	
