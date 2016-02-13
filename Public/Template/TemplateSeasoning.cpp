#include "TemplateSeasoning.h"

BYTE TemplateSeasoning::m_bClientSandHead = TRUE;
BYTE TemplateSeasoning::m_bClientRecvHead = TRUE;
BYTE TemplateSeasoning::m_bOpenDatabase   = TRUE;

CHAR TemplateSeasoning::m_szDBName[32] = {0};
CHAR TemplateSeasoning::m_szDBAddress[16] = {0};
CHAR TemplateSeasoning::m_szDBUsername[32] = {0};
CHAR TemplateSeasoning::m_szDBPasswork[32] = {0};

TemplateSeasoning::TemplateSeasoning()
{
}

TemplateSeasoning::~TemplateSeasoning()
{

}

void TemplateSeasoning::Init()
{
	TemplateSeasoning::m_bClientSandHead = TRUE;
	TemplateSeasoning::m_bClientRecvHead = TRUE;
	TemplateSeasoning::m_bOpenDatabase   = TRUE;
}

void TemplateSeasoning::Release()
{

}

BYTE & TemplateSeasoning::GetClientSandHead()
{	return TemplateSeasoning::m_bClientSandHead;	}

BYTE & TemplateSeasoning::GetClientRecvHead()
{	return TemplateSeasoning::m_bClientRecvHead;	}

BYTE & TemplateSeasoning::GetOpenDatabase()
{	return TemplateSeasoning::m_bOpenDatabase;		}


CHAR * TemplateSeasoning::GetDBAddress()
{	return TemplateSeasoning::m_szDBAddress;    }

CHAR * TemplateSeasoning::GetDBName()
{	return TemplateSeasoning::m_szDBName;       }

CHAR * TemplateSeasoning::GetDBUsername()
{	return TemplateSeasoning::m_szDBUsername;   }

CHAR * TemplateSeasoning::GetDBPassword()
{	return TemplateSeasoning::m_szDBPasswork;   }

