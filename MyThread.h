#pragma once
#include <windows.h>

class CTask;
class CBaseThreadPool;

/**
* @class CMyThread 线程类
*/
class CMyThread
{
public:
	CMyThread(CBaseThreadPool *threadPool);
	~CMyThread(void);

public:
	bool startThread();
	bool suspendThread();
	bool resumeThread();
	bool assignTask(CTask *pTask);
	bool startTask();
	static DWORD WINAPI threadProc(LPVOID pParam);

	/// 线程ID
	DWORD m_threadID;
	/// 线程句柄
	HANDLE m_hThread;
	/// 发起退出
	bool m_bIsExit;
	/// 线程自然退出
	bool m_bHasExit;

private:
	/// 信号
	HANDLE m_hEvent;
	/// 所执行任务
	CTask *m_pTask;
	/// 所属线程池
	CBaseThreadPool *m_pThreadPool;	
};