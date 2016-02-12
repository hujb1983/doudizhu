#include "Handler_Module.h"

/************************************************
    FromLobbyToAgent_DayRanks_ANC
************************************************/
void FromLobbyToAgent_DayRanks_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
	
}

#pragma pack(push,1)

/*  1. 日排名，从数据库中查找 */
class Query_DayRanks : public QueryResult
{
	_DECLARE_QUERY_POOL( Query_DayRank );
public:
	enum {
		RESULT_COL_NUM = 4,
		PARAM_COL_NUL  = 0,
	};

	struct sRESULT {
        int  m_iError;
		int  m_iIndex;
		char m_cName[32];
		int  m_iRate;
		sRESULT() {
			memset( this, 0, sizeof(sRESULT) );
		}
	};

	ULONG uLength[RESULT_COL_NUM]; // 4
	vector<sRESULT> vctRes;
	void AllocData() {
		sRESULT m_RESULT;
		memset(&m_RESULT, 0, sizeof( m_RESULT) );
		vctRes.push_back( m_RESULT );
	}

	void InitData() { vctRes.clear(); }
	void dealData() { vctRes.pop_back(); }

	_BEGIN_BINDING_DATA( sRESULT, vctRes, uLength, 1, RESULT_COL_NUM)
        _BINDING_COLUMN(0, m_iError)
		_BINDING_COLUMN(1, m_iIndex)
		_BINDING_COLUMN_PTR(2, m_cName)
		_BINDING_COLUMN(3, m_iRate)
	_END_BINDING_DATA()
};
_IMPL_QUERY_POOL(Query_DayRank);
#pragma pack(pop)

/************************************************
    FromDBToDB_TableInfo_DBR
************************************************/
void FromLobbyToDB_DayRanks_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    Query_DayRank * pQuery = Query_DayRank::ALLOC();
    if ( NULL == pQuery ) {
        return -1;     // 比较忙
    }

    char szQueryBuff[256] = {0};
	snprintf( szQueryBuff, sizeof(szQueryBuff), " call p_DayRank(); ");

    pQuery->SetIndex( MAKEDWORD( (WORD)Update_Protocol, (WORD)DRankInfo_DBR ) );
    pQuery->SetVoidObject( pServerSession );
    pQuery->SetQuery( szQueryBuff );
    pServerSession->DBQuery( pQuery );
    return 0;
}

/************************************************
    FromDBToLobby_DayRanks_ANC
************************************************/
void FromDBToDB_DayRanks_DBR(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    MSG_DBPROXY_RESULT * msg = (MSG_DBPROXY_RESULT*) pMsg;
    Query_DayRanks * pQuery = (Query_DayRanks*) msg->m_pData;
    if ( pQuery ) {
		
    }
}

/************************************************
    FromDBToLobby_DayRanks_ANC
************************************************/
void FromDBToLobby_DayRanks_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
	
}
