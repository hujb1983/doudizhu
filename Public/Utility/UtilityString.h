#ifndef _UtilityString_H_
#define _UtilityString_H_

#include <UtilityDefine.h>
#include <iostream>
using namespace std;

class UtilityString
{
public:
	// 默认构造函数
	UtilityString();
	// C字符串初始化
	UtilityString( const char * str );
	// 拷贝构造函数
	UtilityString( const UtilityString & str );

	// 析构函数
	~UtilityString();

	// 输入输出
	friend istream & operator >> ( istream & in,  UtilityString & str );
	friend ostream & operator << ( ostream & out, UtilityString & str );
	
	// +
	friend UtilityString operator + ( const UtilityString & s1, const UtilityString & s2 );
	
	// 比较
	friend bool operator == ( const UtilityString & s1, const UtilityString & s2 );
	friend bool operator != ( const UtilityString & s1, const UtilityString & s2 );
	friend bool operator <  ( const UtilityString & s1, const UtilityString & s2 );
	friend bool operator <= ( const UtilityString & s1, const UtilityString & s2 );
	friend bool operator >  ( const UtilityString & s1, const UtilityString & s2 );
	friend bool operator >= ( const UtilityString & s1, const UtilityString & s2 );

	// 下标操作符
	char & operator [] ( const int index );
	const char & operator [] ( const int index ) const;
	// =
	UtilityString & operator = ( const UtilityString & str );
	// +=
	UtilityString & operator += ( const UtilityString & str );

	// 是否为空
	bool empty();
	// 获取长度
	int length();
	//
	const char * c_str();

	// 子串
	UtilityString substr(  int pos, int n );
	// 添加
	UtilityString & append( const UtilityString & str );
	// 插入
	UtilityString & insert( int pos, const UtilityString & str );
	// 替换
	UtilityString & assign( const UtilityString & str, int pos, int len );
	// 删除
	UtilityString & erase( int pos, int len );

	// 忽略大小写比较2个字符串大小
	int CompareNoCase( const char * s1 );

	// 取得分组队列
    int GetByteArray(BYTE * buff, int uiSize, char div=',');
    int GetIntArray(int * buff, int uiSize, char div=',');

    // 设置分组队列
    int SetByteArray(BYTE * buff, int uiSize, char div=',');

private:
	char * m_pData;
	int m_nLength;
};


#endif // _UtilityString_H_INCLUDED_
