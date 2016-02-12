#include "Handler_Module.h"

/************************************************
    FromLobbyToAgent_TablesInfo_ANC
************************************************/
void FromLobbyToAgent_TablesInfo_ANC( TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize )
{
	
}

/************************************************
    Query_TableInfo
************************************************/
#pragma pack(push,1)
class Query_TableInfo : public QueryResult
{
	_DECLARE_QUERY_POOL( Query_TableInfo );

public:
	enum {
		RESULT_COL_NUM = 7,
		PARAM_COL_NUL  = 0,
	};

	struct sRESULT {
        int  m_iError;             // 错误ID
        int  m_iRoomID;            // 房间ID
		int  m_iTableID;           // 桌子ID
		char m_szName[33];         // 房间名称
		int  m_iDoubles;           // 是否加倍
		int  m_iOnlines;           // 在线人数
		int  m_iMoney;             // 带入金额
		sRESULT() {
			memset( this, 0, sizeof(sRESULT) );
		}
	};

	ULONG uLength[RESULT_COL_NUM]; // 4
	vector<sRESULT> vctRes;

	void AllocData()
	{
		sRESULT m_RESULT;
		memset(&m_RESULT, 0, sizeof( m_RESULT) );
		vctRes.push_back( m_RESULT );
	}

	void InitData() { vctRes.clear(); }
	void dealData() { vctRes.pop_back(); }

	_BEGIN_BINDING_DATA( sRESULT, vctRes, uLength, 1, RESULT_COL_NUM)
        _BINDING_COLUMN(0, m_iError)
		_BINDING_COLUMN(1, m_iRoomID)
		_BINDING_COLUMN(2, m_iTableID)
		_BINDING_COLUMN_PTR(3, m_szName)
		_BINDING_COLUMN(4, m_iDoubles)
		_BINDING_COLUMN(5, m_iOnlines)
		_BINDING_COLUMN(6, m_iMoney)
	_END_BINDING_DATA()
};
_IMPL_QUERY_POOL(Query_TableInfo);
#pragma pack(pop)


#define DB_ROOMS_SIZE   (6)
/************************************************
    FromLobbyToDB_TableInfo
************************************************/
void FromLobbyToDB_TableInfo_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    Query_TablesInfo * pQuery = Query_TablesInfo::ALLOC();
    if ( NULL == pQuery ) {
        return (-1);     // 比较忙
    }

    char szQueryBuff[256] = {0};
    snprintf( szQueryBuff, sizeof(szQueryBuff), " call p_TableListInfo(); ");

    pQuery->SetIndex( MAKEDWORD( (WORD)Update_Protocol, (WORD)TableInfo_DBR ) );
    pQuery->SetVoidObject( pServerSession );
    pQuery->SetQuery( szQueryBuff );
    pServerSession->DBQuery( pQuery );
    return 0;
}

/************************************************
    FromDBToDB_TableInfo_DBR
************************************************/
void FromDBToDB_TableInfo_DBR(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    MSG_DBPROXY_RESULT * msg = (MSG_DBPROXY_RESULT*) pMsg;
    Query_TableInfo * pQuery = (Query_TableInfo*) msg->m_pData;
    if ( pQuery ) {
		
    }
}

/************************************************
    FromDBToLobby_RoomsInfo_ANC
************************************************/
void FromDBToLobby_TableInfo_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
	
}
