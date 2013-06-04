#pragma once
#include "windows.h"
class CMyMutex
{
public:
	CMyMutex(void);
	~CMyMutex(void);
public:
	bool Lock();
	bool Unlock();
private:
	CRITICAL_SECTION m_cs;
};

