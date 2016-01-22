#ifndef _MydbcMysql_H_
#define _MydbcMysql_H_

#include <UtilityDefine.h>
#include "MydbcInterface.h"

class MydbcQueryResult;

class MydbcMysql :	public MydbcInterface
{
public:
	MydbcMysql(void);
	virtual ~MydbcMysql(void);

	virtual void			Release();
	virtual BOOL			Init( 
							char * pszIPAddress, 
							char * pszDatabaseName, 
							char * pszUserName, 
							char * pszUserPassword, 
							fnCallBackMessage fnErrorMessage );
							
	virtual BOOL			Connect();
	virtual void			Disconnect();
	virtual BOOL			Execute( MydbcQueryResult * pQuery );
	virtual BOOL			ExecuteLargeData( MydbcQueryResult * pQuery );

private:
	BOOL					SQLError(const char *pszErr, MydbcQueryResult * pQuery = NULL);	
	BOOL					SetField( const char* szData, SHORT sType, ULONG* pPtr, ULONG cSize, ULONG dSize );
	void					TryConnect(void);

	MYSQL*					m_pMySql;
};


#endif // __IMYSQL_H__
	
	
	
