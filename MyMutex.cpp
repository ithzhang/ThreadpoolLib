#include "MyMutex.h"


CMyMutex::CMyMutex(void)
{
	InitializeCriticalSection(&m_cs);
}


CMyMutex::~CMyMutex(void)
{
}

bool CMyMutex::Lock()
{
	EnterCriticalSection(&m_cs);
	return true;
}

bool CMyMutex::Unlock()
{
	LeaveCriticalSection(&m_cs);
	return true;
}
