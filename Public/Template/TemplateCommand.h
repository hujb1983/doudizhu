#ifndef _TemplateCommand_H_
#define _TemplateCommand_H_
#include <UtilityDefine.h>
#include <UtilityInclude.h>

enum
{
    EM_ServerType   = 0 ,
    EM_Help             ,//帮助
    EM_Start            ,//开始所有服务器
    EM_Restart          ,//重启指定服务器
    EM_Stop             ,//停止所有服务器
    EM_Show             ,//显示资源
    EM_Count            ,//计算在线人数
    EM_Stat             ,//统计内存和CPU使用情况
    EM_Login            ,//Login服务器
    EM_Agent            ,//Agent服务器
    EM_Lobby            ,//Lobby服务器
    EM_Game             ,//Game服务器
    EM_DB               ,//DB服务器
};

class TemplateCommand : public UtilityCommand
{
public:
	TemplateCommand();
	virtual ~TemplateCommand();

public:
	virtual BOOL ToMain ( int agrc, char ** agrv );

public:
    void ServerRename(const char * rename);

public:
	virtual BOOL OnHelp   ( int agrc, char ** agrv );//帮助
	virtual BOOL OnStart  ( int agrc, char ** agrv );//开始所有服务器
	virtual BOOL OnRestart( int agrc, char ** agrv );//重启指定服务器
	virtual BOOL OnStop   ( int agrc, char ** agrv );//停止所有服务器
	virtual BOOL OnShow   ( int agrc, char ** agrv );//显示资源
	virtual BOOL OnCount  ( int agrc, char ** agrv );//计算在线人数
	virtual BOOL OnStat   ( int agrc, char ** agrv );//统计内存和CPU使用情况
	virtual BOOL OnServer ( int agrc, char ** agrv, char * name); //服务器名称

private:
	int m_MainAgrc;
	char ** m_MainAgrv;
};

#endif // _AGENTPLAYER_H_INCLUDED_
