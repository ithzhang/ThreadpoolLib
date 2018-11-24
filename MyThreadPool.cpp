#include "stdafx.h"
#include "MyThreadPool.h"
#include "MyTask.h"
#include<cassert>
#include<iostream>
#include <process.h>

// 全局唯一的线程池变量
CMyThreadPool g_ThreadPool(4);

#ifndef WAIT
// 以步长n毫秒在条件C下等待T秒(n是步长，必须能整除1000；条件改变时就不等待, T >= 0.01)
#define WAIT_n(C, T, n) {assert(!(1000%(n)));int s=(1000*(T))/(n);do{Sleep(n);}while((C)&&(--s));}
// 在条件C成立时等待T秒(步长10ms)
#define WAIT(C, T) WAIT_n(C, T, 10)
#endif

// 线程池线程个数动态管理
UINT WINAPI ThreadPoolMgr(LPVOID param)
{
	CMyThreadPool *p = (CMyThreadPool *)param;
	p->SetMgrThreadState(true);
	const bool& g_bExit = p->IsExit();
	int idleNum = 0, n = 0;
	do
	{
		idleNum += p->GetIdleThreadNum();
		WAIT_n(!g_bExit, POOL_STEP, 50);
		if(++n == POOL_TIMES){
			idleNum /= n;
			if (idleNum){
				int s = p->GetThreadNum() - idleNum;
				s = max(p->MinPoolSize(), s);
				p->ChangeSize(s);
			}
			n = 0; idleNum = 0;
		}
	}while(false == g_bExit);
	p->SetMgrThreadState(false);
	return 0xDEAD777;
}

/**
* @brief 构造一个容量确定的线程池
* @param[in] nDefaultSize 线程池默认容量(最小容量)
* @param[in] autoMgr 是否开启自动管理
*/
CMyThreadPool::CMyThreadPool(int nDefaultSize, bool autoMgr)
{
	m_nThreadNum = nDefaultSize;
	m_nMinSize = nDefaultSize;
	m_bIsExit = false;
	for(int i = 0; i < nDefaultSize; ++i)
	{
		CMyThread *p = new CMyThread(this);
		m_IdleThreadStack.push(p);
		p->startThread();
	}
	m_bThreadState = false;
	if (autoMgr)
	{
		HANDLE h = (HANDLE)_beginthreadex(NULL, 0, &ThreadPoolMgr, this, 0, NULL);
		CloseHandle(h);
	}
}

/// 默认析构函数
CMyThreadPool::~CMyThreadPool(void)
{
	Wait(10);
	destroyThreadPool();
}

/**
* @brief 改变线程池的大小
* @return nSize 线程池大小
*/
void CMyThreadPool::ChangeSize(int nSize)
{
	m_mutex.Lock();
	int n = m_nThreadNum;
	if (nSize > m_nThreadNum)
	{
		while (nSize > m_nThreadNum) AddThread();
		printf("[WARNING] 线程池空闲线程不足, 请考虑增加线程."
			"======> %d -> %d\n", n, m_nThreadNum);
	}
	else if (nSize < m_nThreadNum)
	{
		while (nSize < m_nThreadNum) SubtractThread();
		printf("[INFO] 线程池空闲线程较多, 请考虑释放线程."
			"======> %d -> %d\n", n, m_nThreadNum);
	}
	m_mutex.Unlock();
}

/** 
* @brief 将线程从活动队列取出，放入空闲线程栈中.在取之前判断此时任务队列是否有任务.
* 如任务队列为空时才挂起,否则从任务队列取任务继续执行.
*/
void CMyThreadPool::SwitchActiveThread(CMyThread *pThread)
{
	CMyTask *pTask = NULL;
	m_mutex.Lock();
	if(pTask = m_TaskQueue.pop())//任务队列不为空,继续取任务执行
	{
		pThread->assignTask(pTask);
		pThread->startTask();
	}
	else//任务队列为空，该线程挂起
	{
		m_ActiveThreadList.removeThread(pThread);
		m_IdleThreadStack.push(pThread);
	}
	m_mutex.Unlock();
}

/**
* @brief 添加任务
* @param[in] *t 任务(指针)
* @param[in] priority 优先级,高优先级的任务将被插入到队首.
*/
void CMyThreadPool::addTask( CMyTask *t, PRIORITY priority )
{
	if(m_bIsExit)
		return;
	CMyTask *task = NULL;
	m_mutex.Lock();
	if(priority == PRIORITY::NORMAL)
	{
		m_TaskQueue.push(t);//进入任务队列
	}
	else if(PRIORITY::HIGH)
	{
		m_TaskQueue.pushFront(t);//高优先级任务
	}

	if(!m_IdleThreadStack.isEmpty())//存在空闲线程,调用空闲线程处理任务
	{
		if(task = m_TaskQueue.pop())//取出列头任务
		{
			CMyThread *pThread = m_IdleThreadStack.pop();
			m_ActiveThreadList.addThread(pThread);
			pThread->assignTask(task);
			pThread->startTask();
		}
	}
	m_mutex.Unlock();
}

/**
* @brief 销毁线程池
* @details clear m_TaskQueue，m_ActiveThreadList，m_IdleThreadStack
*/
void CMyThreadPool::destroyThreadPool()
{
	m_mutex.Lock();
	m_bIsExit = true;
	m_TaskQueue.clear();
	m_ActiveThreadList.clear();
	m_IdleThreadStack.clear();
	m_mutex.Unlock();
	while(m_bThreadState)
		Sleep(10);
}
