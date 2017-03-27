#pragma once

#include <windows.h>

/** 
* @class CMyMutex 互斥锁
* @brief 封装了CRITICAL_SECTION对象的操作方法
*/
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