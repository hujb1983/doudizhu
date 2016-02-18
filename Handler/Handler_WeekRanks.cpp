#include "Handler_Module.h"
#include "PacketRank.h"
#include "AgentServer.h"
#include "LobbyServer.h"

/************************************************
    Query_WeekRanks
************************************************/
#pragma pack(push,1)
class Query_WeekRanks : public MydbcQueryResult
{
	_DECLARE_QUERY_POOL( Query_WeekRanks );

public:
    RankPacket m_cPacket;

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
_IMPL_QUERY_POOL(Query_WeekRanks);
#pragma pack(pop)


/************************************************
    FromLobbyToDB_WeekRanks_REQ
************************************************/
void FromLobbyToDB_WeekRanks_REQ(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    if ( wSize<sizeof(RankPacket) ) {
		return; // 发送的包数据不正确,丢失;
	}

	RankPacket * packet = ( RankPacket*) pMsg;

    Query_WeekRanks * pQuery = Query_WeekRanks::ALLOC();
    if ( NULL == pQuery ) {
        return;     // 比较忙
    }

    char szQueryBuff[256] = {0};
	snprintf( szQueryBuff, sizeof(szQueryBuff), " call p_WeekRank(); ");

	pQuery->m_cPacket.SetPacket( (BYTE*)packet, sizeof(RankPacket) );
    pQuery->SetIndex( MAKEDWORD( (WORD)FromDBToDB_PID, (WORD)WeekRanks_DBR ) );
    pQuery->SetVoidObject( pServerSession );
    pQuery->SetQuery( szQueryBuff );
    pServerSession->DBQuery( pQuery );
}

/************************************************
    FromDBToDB_WeekRanks_DBR
************************************************/
void FromDBToDB_WeekRanks_DBR(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    MSG_DBPROXY_RESULT * msg = (MSG_DBPROXY_RESULT*) pMsg;
    Query_WeekRanks * pQuery = (Query_WeekRanks*) msg->m_pData;
    if ( pQuery )
    {
        int iSize = pQuery->vctRes.size();
        if (iSize!=0)
        {
            RankPacket * packet = &pQuery->m_cPacket;
            packet->GetRankSize() = iSize;
            for(int i=0; i<iSize; ++i)
            {
                if (pQuery->vctRes[i].m_iError==0)
                {
                    packet->GetRank(i).byIndex = pQuery->vctRes[i].m_iIndex;
                    memset( packet->GetRank(i).szName, 0x0, 33);
                    strcat( packet->GetRank(i).szName, pQuery->vctRes[i].m_cName );
                    packet->GetRank(i).uiRate = pQuery->vctRes[i].m_iRate ;
                }
            }
        }
    }
}

/************************************************
    FromDBToLobby_WeekRanks_ANC
************************************************/
void FromDBToLobby_WeekRanks_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{

}

/************************************************
    FromDBToLobby_WeekRanks_ANC
************************************************/
void FromLobbyToAgent_WeekRanks_ANC(TemplateServerSession * pServerSession, MSG_BASE * pMsg, WORD wSize)
{
    if ( wSize>=sizeof(RankPacket) )
    {
        RankPacket packet;
        packet.SetPacket( (BYTE*)pMsg,wSize );

        WORD nLen = packet.GetJsonSize();
        if ( nLen>0 ) {
            packet.GetProtocol() = MAKEDWORD( (WORD)FromLobbyToAgent_PID, (WORD)WeekRanks_ANC );
            g_pAgentServer->SendTo( packet.GetUserKey(), (BYTE*)packet.GetJsonData(), nLen);
        }
    }
}
