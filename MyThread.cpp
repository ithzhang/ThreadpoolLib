#include "MyThread.h"
#include"task.h"
#include "MyThreadPool.h"
#include<cassert>

// 退出代码
#define EXIT_CODE (0xDEAD)

CMyThread::CMyThread(CBaseThreadPool *threadPool)
{
	m_pTask = NULL;
	m_pThreadPool = threadPool;
	m_hEvent = CreateEvent(NULL, false, false, NULL);
	m_bIsExit = false;
	m_bHasExit = false;
}

CMyThread::~CMyThread(void)
{
	CloseHandle(m_hEvent);
	CloseHandle(m_hThread);
}

/// 开始线程
bool CMyThread::startThread()
{
	m_hThread = CreateThread(0, 0, threadProc, this, 0, &m_threadID);
	if(m_hThread == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	return true;
}

/// 挂起线程
bool CMyThread::suspendThread()
{
	ResetEvent(m_hEvent);
	return true;
}

/// 有任务到来，通知线程继续执行
bool CMyThread::resumeThread()
{
	SetEvent(m_hEvent);
	return true;
}

/// 线程执行函数
DWORD WINAPI CMyThread::threadProc(LPVOID pParam)
{
	CMyThread *pThread = (CMyThread*)pParam;
	DWORD ret = 1; // 线程初次启动时挂起
	do // 当线程未退出时循环等待执行任务
	{
		if(ret == WAIT_OBJECT_0)// 0
		{
			if(pThread->m_pTask)
			{
				pThread->m_pTask->taskProc();// 执行任务
				pThread->m_pTask->Destroy();
				pThread->m_pTask = NULL;
				pThread->m_pThreadPool->SwitchActiveThread(pThread);
			}
		}
		// 等待任务
		ret = WaitForSingleObject(pThread->m_hEvent, INFINITE);
	}while(!pThread->m_bIsExit);
	// 标记线程已退出
	pThread->m_bHasExit = true;
	return EXIT_CODE;
}

/// 将任务关联到线程类
bool CMyThread::assignTask(CTask *pTask)
{
	assert(pTask);
	if(!pTask)
		return false;
	m_pTask = pTask;

	return true;
}

/// 开始执行任务
bool CMyThread::startTask()
{
	resumeThread();
	return true;
}