#include "Handler_Module.h"

/************************************************
    FromClientToAgent_RoomsInfo_ANC
************************************************/
void FromLobbyToAgent_RoomsInfo_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
	
}

/************************************************
    Query_RoomsInfo
************************************************/
#pragma pack(push,1)
class Query_RoomsInfo : public QueryResult
{
	_DECLARE_QUERY_POOL( Query_RoomsInfo );
public:

	enum {
		RESULT_COL_NUM = 4,
		PARAM_COL_NUL  = 0,
	};

	struct sRESULT {
        int  m_iError;             // 错误ID
        int  m_iRoomID;            // 房间ID
		int  m_iTableSize;         // 桌子数量
		char m_szRoomName[33];      // 房间名称
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
		_BINDING_COLUMN(2, m_iTableSize)
		_BINDING_COLUMN_PTR(3, m_szRoomName)
	_END_BINDING_DATA()
};
_IMPL_QUERY_POOL(Query_RoomsInfo);
#pragma pack(pop)

/************************************************
    FromLobbyToDB_RoomInfo_REQ
************************************************/
void FromLobbyToDB_RoomInfo_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
	Query_RoomsInfo * pQuery = Query_RoomsInfo::ALLOC();
    if ( NULL == pQuery ) {
        return;     // 比较忙
    }
	
    char szQueryBuff[256] = {0};
    snprintf( szQueryBuff, sizeof( szQueryBuff ), " call p_RoomListInfo(); " );
	
    pQuery->SetIndex( MAKEDWORD( (WORD)Update_Protocol, (WORD)RoomInfo_DBR ) );
    pQuery->SetVoidObject( pServerSession );
    pQuery->SetQuery( szQueryBuff );
    pServerSession->DBQuery( pQuery );
    return;
}

/************************************************
    FromDBToDB_RoomsInfo_DBR
************************************************/
void FromDBToDB_RoomsInfo_DBR(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    MSG_DBPROXY_RESULT * msg = (MSG_DBPROXY_RESULT*) pMsg;
    Query_RoomsInfo * pQuery = (Query_RoomsInfo*) msg->m_pData;
    if ( pQuery ) {

    }
}

/************************************************
    FromClientToAgent_RoomsInfo_ANC
************************************************/
void FromDBToLobby_RoomsInfo_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
	
}