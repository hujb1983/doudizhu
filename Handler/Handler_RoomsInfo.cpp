#include "Handler_Module.h"
#include "PacketRooms.h"
#include "AgentServer.h"
#include "LobbyServer.h"
#include "DBServer.h"
#include <UtilityBuffer.h>


/************************************************
    Query_RoomsInfo
************************************************/
#pragma pack(push,1)
class Query_RoomsInfo : public MydbcQueryResult
{
	_DECLARE_QUERY_POOL( Query_RoomsInfo );

public:
    RoomsPacket m_cPacket;

	enum {
		RESULT_COL_NUM = 7,
		PARAM_COL_NUL  = 0,
	};

	struct sRESULT {
        int  m_iError;             // 错误ID
        int  m_iFieldId;            // 房间ID
		int  m_iRoomId;           // 桌子ID
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
		_BINDING_COLUMN(1, m_iFieldId)
		_BINDING_COLUMN(2, m_iRoomId)
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
        int iSize = pQuery->vctRes.size();
        if (iSize!=0)
        {
            int offset = sizeof(ST_Room);
            RoomsPacket * packet = &pQuery->m_cPacket;
            packet->ToInit();
        }
    }
}

/************************************************
    FromDBToLobby_TableInfo_ANC
************************************************/
void FromDBToLobby_RoomsInfo_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    if ( wSize<sizeof(RoomsPacket) ) {
		return; // 发送的包数据不正确,丢失;
	}

    RoomsPacket temp;
    temp.SetPacket( (BYTE*)pMsg, sizeof(RankPacket) );
    BYTE byField = temp.GetFieldId();

	LobbyUpdate * pLobbyUpdate = g_pLobbyServer->GetLobbyUpdate();
    if ( pLobbyUpdate )
    {
        //pLobbyUpdate->GetRooms(byField).ToClear();
        pLobbyUpdate->GetRooms(byField).SetPacket( (BYTE*)pMsg, sizeof(RankPacket) );

        RoomsPacket packet = pLobbyUpdate->GetRooms(byField);
        char * szBuff = packet.GetJsonData();

        char szMainBuff[1024] = {0};
        char szUintBuff[256] = {0};

        WORD wLen = packet.GetRoomsSize();
        sprintf( szUintBuff, "{\"Protocol\":%d, \"Count\":%d, \"Rooms\":{", MAKEDWORD( (WORD)900, (WORD)632), wLen );
        strcat( szMainBuff, szUintBuff );

        for(int i=0; i<wLen; ++i)
        {
            szUintBuff[0] = '\0';
            int _rid  = packet.GetRooms(i).m_uiRoomId;
            int _fid  = packet.GetRooms(i).m_uiFieldId;
            char * _name = packet.GetRooms(i).m_szName;
            int _doub = packet.GetRooms(i).m_byDoubles;
            int _ps  = packet.GetRooms(i).m_byOnlines;
            int _dmoney = packet.GetRooms(i).m_iMoney;

            if (i!=0) {
               strcat( szMainBuff, ",");
            }

            sprintf( szUintBuff, "{\"RoomId\":%d,\"FieldId\":\"%d\",\"Name\":%s, \"DoubleType\":%s, \"Onlines\":%d,\"DMoney\":%d}",
                   _rid, _fid, _name, _doub, _ps, _dmoney );

            strcat( szMainBuff, szUintBuff );
        }
        if (wLen>0) {
            strcat( szMainBuff, "}}" );
        }

        WORD wMainLen = strlen( szMainBuff );
        DEBUG_MSG( LVL_DEBUG, "WeekRanks = (%s, %d)", szMainBuff, wMainLen);
        if ( wMainLen<512 ) {
            memcpy( szBuff, szMainBuff , wMainLen);
            packet.GetJsonSize() = wMainLen;
        }
    }
}

/************************************************
    FromLobbyToAgent_TableInfo_ANC
************************************************/
void FromLobbyToAgent_RoomsInfo_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    if ( wSize>=sizeof(RoomsPacket) )
    {
        RoomsPacket packet;
        packet.SetPacket( (BYTE*)pMsg,wSize );

        WORD nLen = packet.GetJsonSize();
        if ( nLen>0 )
        {
            // packet.GetProtocol() = MAKEDWORD( (WORD)FromLobbyToAgent_PID, (WORD)RoomsInfo_ANC );
            g_pAgentServer->SendTo( packet.GetUserKey(), (BYTE*)packet.GetJsonData(), nLen );
        }
    }
}
