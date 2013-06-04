#pragma once
#include "windows.h"
class CTask;
class CBaseThreadPool;
class CMyThread
{
public:
	CMyThread(CBaseThreadPool*threadPool);
	~CMyThread(void);
public:
	bool startThread();
	bool suspendThread();
	bool resumeThread();
	bool assignTask(CTask*pTask);
	bool startTask();
	static DWORD WINAPI threadProc(LPVOID pParam);
	DWORD m_threadID;
	HANDLE m_hThread;
	bool m_bIsExit;
private:
	
	HANDLE m_hEvent;
	CTask*m_pTask;
	CBaseThreadPool*m_pThreadPool;	
};
