#ifndef _UtilityCircuitQueue_H_
#define _UtilityCircuitQueue_H_

#include <UtilityDefine.h>
#include <UtilityMutex.h>

template<typename T>
class UtilityCircuitQueue
{
public:
	UtilityCircuitQueue() : m_pData( NULL ), m_nLength( 0 ), m_nSize( 0 ), m_nHead( 0 ), m_nTail( 0 )
	{
	}
	
	virtual ~UtilityCircuitQueue()
	{
		if( m_pData ) delete [] m_pData;
	}
	
//=============================================================================================================================
/**
	@param	nSize
	@param	nExtraSize
*/
//=============================================================================================================================
	void Create( int nSize, int nExtraSize = 0 )
	{
		m_cs.Lock();
		if( m_pData ) delete [] m_pData;

		m_pData			= new T[nSize + nExtraSize];
		m_nSize			= nSize;
		m_nExtraSize	= nExtraSize;
		m_cs.Unlock();
	}

//=============================================================================================================================
/**
	@remarks
*/
//=============================================================================================================================
	inline void Clear()
	{
		m_cs.Lock();

		m_nLength       = 0;
		m_nHead         = 0;
		m_nTail         = 0;

		m_cs.Unlock();
	}
	
	/// 
	inline int      GetSpace()
	{
		int iRet;

		m_cs.Lock();
		iRet = m_nSize - m_nLength;		
		m_cs.Unlock();

		return iRet;
	}

	/// 
	inline int      GetLength()
	{
		int iRet;

		m_cs.Lock();
		iRet = m_nLength;
		m_cs.Unlock();

		return iRet;
	}

	/// 
	inline int      GetBackDataCount()
	{
		int iRet;

		m_cs.Lock();
		iRet = m_nSize - m_nHead;
		m_cs.Unlock();

		return iRet;
	}

	/// 
	inline T*       GetReadPtr()
	{
		T *pRet;

		m_cs.Lock();
		pRet = m_pData + m_nHead;

		// 
		int nSplitFirstDataCount;
		if( m_nHead > m_nTail && ( nSplitFirstDataCount = m_nSize - m_nHead ) < m_nExtraSize )
		{
			memcpy( m_pData + m_nSize, m_pData, sizeof(T) * ( m_nExtraSize - nSplitFirstDataCount ) );
		}

		m_cs.Unlock();

		return pRet;
	}

	/// 
	inline T*       GetWritePtr()
	{
		T *pRet;

		m_cs.Lock();
		pRet = m_pData + m_nTail;
		m_cs.Unlock();

		return pRet;
	}
	
	/// 
	inline int GetReadableLen()
	{
		int iRet;

		m_cs.Lock();
		if( m_nHead == m_nTail )		iRet = GetLength() > 0 ? m_nSize - m_nHead: 0;
		else if( m_nHead < m_nTail )	iRet = m_nTail - m_nHead;
		else							iRet = m_nSize - m_nHead;
		m_cs.Unlock();

		return iRet;
	}
	
	/// 
	inline int GetWritableLen()
	{
		int iRet;

		m_cs.Lock();
		if( m_nHead == m_nTail )		iRet = GetLength() > 0 ? 0 : m_nSize - m_nTail;
		else if( m_nHead < m_nTail )	iRet = m_nSize - m_nTail;
		else							iRet = m_nHead - m_nTail;
		m_cs.Unlock();

		return iRet;
	}

//=============================================================================================================================
/**
	@remarks
	@param	pSrc
	@param	nSize
	@retval	BOOL
*/
//=============================================================================================================================
	inline BOOL Enqueue( T *pSrc, int nSize )
	{
		m_cs.Lock();

		if( GetSpace() < nSize )
		{
			m_cs.Unlock();
			return FALSE;
		}

		// pSrc NULL tail length.
		if( pSrc )
		{
			if( m_nHead <= m_nTail )
			{
				// 1. head tail
				int nBackSpaceCount = m_nSize - m_nTail;

				if( nBackSpaceCount >= nSize )  
				{
					// 
					memcpy( m_pData + m_nTail, pSrc, sizeof(T) * nSize );
				}
				else
				{
					// 
					memcpy( m_pData + m_nTail, pSrc, sizeof(T) * nBackSpaceCount );
					memcpy( m_pData, pSrc + nBackSpaceCount, sizeof(T) * ( nSize - nBackSpaceCount ) );
				}
			}
			else
			{
				// 2. head tail
				memcpy( m_pData + m_nTail, pSrc, sizeof(T) * nSize );
			}
		}

		m_nTail		+= nSize;
		m_nTail		%= m_nSize;
		m_nLength	+= nSize;

		m_cs.Unlock();

		return TRUE;
	}

//=============================================================================================================================
/**
	@remarks
	@param	pTar
	@param	nSize
	@retval	BOOL
*/
//=============================================================================================================================
	inline BOOL Dequeue( T *pTar, int nSize )
	{    
		m_cs.Lock();

		if( !Peek( pTar, nSize ) )
		{
			m_cs.Unlock();
			return FALSE;
		}

		m_nHead		+= nSize;
		m_nHead		%= m_nSize;
		m_nLength	-= nSize;

		m_cs.Unlock();

		return TRUE;
	}

//=============================================================================================================================
/**
	@remarks
	@param	pTar
	@param	nSize
	@retval	BOOL
*/
//=============================================================================================================================
	inline BOOL Peek( T *pTar, int nSize )
	{
		m_cs.Lock();

		if( m_nLength < nSize )
		{
			m_cs.Unlock();
			return FALSE;
		}

		// 
		if( pTar != NULL )
		{
			if( m_nHead < m_nTail )
			{
				// 1. head tail
				memcpy( pTar, m_pData + m_nHead, sizeof(T) * nSize );
			}
			else
			{
				// 2. head tail
				if( GetBackDataCount() >= nSize )
				{
					// 
					memcpy( pTar, m_pData + m_nHead, sizeof(T) * nSize );                           
				}
				else
				{
					// 
					memcpy( pTar, m_pData + m_nHead, sizeof(T) * GetBackDataCount() );
					memcpy( pTar + GetBackDataCount(), m_pData, sizeof(T) * ( nSize - GetBackDataCount() ) );
				}
			}
		}

		m_cs.Unlock();

		return TRUE;
	}

//=============================================================================================================================
/**
	@remarks
	@param	nSize
*/
//=============================================================================================================================
	inline void CopyHeadDataToExtraBuffer( int nSize )
	{
		assert( nSize <= m_nExtraSize );

		m_cs.Lock();

		// 
		memcpy( m_pData + m_nSize, m_pData, nSize );

		m_cs.Unlock();
	}

protected:
	UtilityMutex		m_cs;
	T					*m_pData;			/// 
	int					m_nLength;			/// 
	int					m_nSize;			/// 
	int					m_nHead;			/// 
	int					m_nTail;			/// 
	int					m_nExtraSize;		/// 
};

#endif










