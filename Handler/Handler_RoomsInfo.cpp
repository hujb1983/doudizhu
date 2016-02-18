#include "Handler_Module.h"
#include "PacketRank.h"
#include "AgentServer.h"
#include "LobbyServer.h"

/************************************************
    Query_RoomsInfo
************************************************/
#pragma pack(push,1)
class Query_RoomsInfo : public MydbcQueryResult
{
	_DECLARE_QUERY_POOL( Query_RoomsInfo );

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
_IMPL_QUERY_POOL(Query_RoomsInfo);
#pragma pack(pop)


#define DB_ROOMS_SIZE   (6)
/************************************************
    FromLobbyToDB_TableInfo
************************************************/
void FromLobbyToDB_RoomsInfo_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    Query_RoomsInfo * pQuery = Query_RoomsInfo::ALLOC();
    if ( NULL==pQuery ) {
        return; // 比较忙
    }

    char szQueryBuff[256] = {0};
    snprintf( szQueryBuff, sizeof(szQueryBuff), " call p_TableListInfo(); ");

    pQuery->SetIndex( MAKEDWORD( (WORD)FromDBToDB_PID,(WORD)RoomsInfo_DBR) );
    pQuery->SetVoidObject( pServerSession );
    pQuery->SetQuery( szQueryBuff );
    pServerSession->DBQuery( pQuery );
}

/************************************************
    FromDBToDB_TableInfo_DBR
************************************************/
void FromDBToDB_RoomsInfo_DBR(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    MSG_DBPROXY_RESULT * msg = (MSG_DBPROXY_RESULT*) pMsg;
    Query_RoomsInfo * pQuery = (Query_RoomsInfo*) msg->m_pData;
    if ( pQuery )
    {

    }
}

/************************************************
    FromDBToLobby_TableInfo_ANC
************************************************/
void FromDBToLobby_RoomsInfo_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{

}

/************************************************
    FromLobbyToAgent_TableInfo_ANC
************************************************/
void FromLobbyToAgent_RoomsInfo_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    if ( wSize>=sizeof(RankPacket) )
    {
        RankPacket packet;
        packet.SetPacket( (BYTE*)pMsg,wSize );

        WORD nLen = packet.GetJsonSize();
        if ( nLen>0 )
        {
            packet.GetProtocol() = MAKEDWORD( (WORD)FromLobbyToAgent_PID, (WORD)RoomsInfo_ANC );
            g_pAgentServer->SendTo( packet.GetUserKey(), (BYTE*)packet.GetJsonData(), nLen );
        }
    }
}
