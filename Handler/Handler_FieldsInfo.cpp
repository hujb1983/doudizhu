#include "Handler_Module.h"
#include "PacketFields.h"
#include "AgentServer.h"
#include "LobbyServer.h"
#include "DBServer.h"

/************************************************
    Query_FieldsInfo
************************************************/
#pragma pack(push,1)
class Query_FieldsInfo : public MydbcQueryResult
{
	_DECLARE_QUERY_POOL( Query_FieldsInfo );

public:
    FieldsPacket m_cPacket;

	enum {
		RESULT_COL_NUM = 4,
		PARAM_COL_NUL  = 0,
	};

	struct sRESULT {
        int  m_iError;             // 错误ID
        int  m_iRoomId;            // 房间ID
		int  m_iTableCount;         // 桌子数量
		char m_szRoomName[33];     // 房间名称
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
		_BINDING_COLUMN(1, m_iRoomId)
		_BINDING_COLUMN(2, m_iTableCount)
		_BINDING_COLUMN_PTR(3, m_szRoomName)
	_END_BINDING_DATA()
};
_IMPL_QUERY_POOL(Query_FieldsInfo);
#pragma pack(pop)


/************************************************
    FromLobbyToDB_FieldsInfo_REQ
************************************************/
void FromLobbyToDB_FieldsInfo_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
	Query_FieldsInfo * pQuery = Query_FieldsInfo::ALLOC();
    if ( NULL == pQuery ) {
        return;     // 比较忙
    }

    char szQueryBuff[256] = {0};
    snprintf( szQueryBuff, sizeof( szQueryBuff ), " call p_RoomListInfo(); " );
    pQuery->SetIndex( MAKEDWORD( (WORD)FromDBToDB_PID, (WORD)FieldsInfo_DBR ) );
    pQuery->SetVoidObject( pServerSession );
    pQuery->SetQuery( szQueryBuff );
    pServerSession->DBQuery( pQuery );
}

/************************************************
    FromDBToDB_FieldsInfo_DBR
************************************************/
void FromDBToDB_FieldsInfo_DBR(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    MSG_DBPROXY_RESULT * msg = (MSG_DBPROXY_RESULT*) pMsg;
    Query_FieldsInfo * pQuery = (Query_FieldsInfo*) msg->m_pData;
    if ( pQuery )
    {
        int iSize = pQuery->vctRes.size();
        if (iSize!=0)
        {
            FieldsPacket * packet = &pQuery->m_cPacket;
            for(int i=0; i<iSize; ++i)
            {
                if (pQuery->vctRes[i].m_iError==0)
                {
                    packet->GetFields(i).byIndex = pQuery->vctRes[i].m_iRoomId;
                    memset( packet->GetFields(i).szName, 0x0, 33);
                    strcat( packet->GetFields(i).szName, pQuery->vctRes[i].m_szRoomName );
                    packet->GetFields(i).uiCount = pQuery->vctRes[i].m_iTableCount;
                }
            }

            packet->GetProtocol() = MAKEDWORD( (WORD)FromDBToLobby_PID, (WORD)FieldsInfo_DBR );
            pServerSession->Send( (BYTE*)packet, sizeof(FieldsPacket) );
        }
    }
}

/************************************************
    FromClientToAgent_FieldsInfo_ANC
************************************************/
void FromDBToLobby_FieldsInfo_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    if ( wSize<sizeof(FieldsPacket) ) {
		return; // 发送的包数据不正确,丢失;
	}

	LobbyUpdate * pLobbyUpdate = g_pLobbyServer->GetLobbyUpdate();
    if ( pLobbyUpdate ) {
        // pLobbyUpdate->GetFields().ToClear();
        pLobbyUpdate->GetFields().SetPacket( (BYTE*)pMsg, sizeof(RankPacket) );

        FieldsPacket packet = pLobbyUpdate->GetFields();
        char * szBuff = packet.GetJsonData();

        char szMainBuff[1024] = {0};
        char szUintBuff[256] = {0};

        WORD wLen = packet.GetFieldsSize();
        sprintf( szUintBuff, "{\"Protocol\":%d, \"Count\":%d, \"Fields\":{", MAKEDWORD( (WORD)900, (WORD)632), wLen);
        strcat( szMainBuff, szUintBuff );

        for(int i=0; i<wLen; ++i)
        {
            szUintBuff[0] = '\0';
            int _idx  = packet.GetFields(i).byIndex;
            int _size = packet.GetFields(i).uiCount;
            char * _name = packet.GetFields(i).szName;

            if (i!=0) {
               strcat( szMainBuff, ",");
            }

            sprintf( szUintBuff, "{ \"Fields\":%d,\"RoomSize\":\"%s\",\"Name\":%d }",
                   _idx, _size, _name );
            strcat( szMainBuff, szUintBuff );
        }
        if (wLen>0) {
            strcat( szMainBuff, "}}" );
        }

        WORD wMainLen = strlen( szMainBuff );
        DEBUG_MSG( LVL_DEBUG, "FieldsInfo = (%s, %d)", szMainBuff, wMainLen);
        if ( wMainLen<512 ) {
            memcpy( szBuff, szMainBuff , wMainLen);
            packet.GetJsonSize() = wMainLen;
        }
    }
}

/************************************************
    FromLobbyToAgent_FieldsInfo_ANC
************************************************/
void FromLobbyToAgent_FieldsInfo_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    if ( wSize>=sizeof(FieldsPacket) )
    {
        FieldsPacket packet;
        packet.SetPacket( (BYTE*)pMsg,wSize );

        WORD nLen = packet.GetJsonSize();
        if ( nLen>0 )
        {
            // packet.GetProtocol() = MAKEDWORD( (WORD)FromLobbyToAgent_PID, (WORD)FieldsInfo_ANC );
            g_pAgentServer->SendTo( packet.GetUserKey(), (BYTE*)packet.GetJsonData(), nLen);
        }
    }
}
