/** 
* @file MyMutex.h
* @brief ������
*/

#pragma once

#include <windows.h>

/** 
* @class CMyMutex 
* @brief ��������װ��CRITICAL_SECTION����Ĳ�������
*/
class CMyMutex
{
public:
	/// InitializeCriticalSection
	CMyMutex() { InitializeCriticalSection(&m_cs); }

	/// DeleteCriticalSection
	~CMyMutex() { DeleteCriticalSection(&m_cs); }

	/// EnterCriticalSection
	inline void Lock() { EnterCriticalSection(&m_cs); }

	/// LeaveCriticalSection
	inline void Unlock() { LeaveCriticalSection(&m_cs); }

private:
	/// Ψһ���ٽ�����Ա
	CRITICAL_SECTION m_cs;
};
