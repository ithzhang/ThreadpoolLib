#include "MyThreadPool.h"
#include "MyThread.h"
#include "Task.h"
#include<cassert>
#include<iostream>

/**
* @brief 构造一个容量确定的线程池
* @param[in] num 线程池容量
*/
CMyThreadPool::CMyThreadPool(int num)
{
	m_nThreadNum = num;
	m_bIsExit = false;
	for(int i = 0; i < num; i++)
	{
		CMyThread *p = new CMyThread(this);
		m_IdleThreadStack.push(p);
		p->startThread();
	}
}

/// 默认析构函数
CMyThreadPool::~CMyThreadPool(void)
{
}

/**
* @brief 从空闲线程栈取出一个线程
* @return 栈顶空闲线程
*/
CMyThread* CMyThreadPool::PopIdleThread()
{
	CMyThread *pThread = m_IdleThreadStack.pop();
	return pThread;
}

/** 
* @brief 将线程从活动队列取出，放入空闲线程栈中.在取之前判断此时任务队列是否有任务.
* 如任务队列为空时才挂起,否则从任务队列取任务继续执行.
*/
bool CMyThreadPool::SwitchActiveThread( CMyThread *pThread)
{
	CTask *pTask = NULL;
	if(pTask = m_TaskQueue.pop())//任务队列不为空,继续取任务执行
	{
		// printf("线程【%d】执行%d\n", pThread->m_threadID, pTask->getID());

		pThread->assignTask(pTask);
		pThread->startTask();
	}
	else//任务队列为空，该线程挂起
	{
		m_ActiveThreadList.removeThread(pThread);
		m_IdleThreadStack.push(pThread);
	}
	return true;
}

/**
* @brief 添加任务
* @param[in] *t 任务(指针)
* @param[in] priority 优先级,高优先级的任务将被插入到队首.
*/
bool CMyThreadPool::addTask( CTask *t, PRIORITY priority )
{
	assert(t);
	if(!t || m_bIsExit)
		return false;	
	CTask *task = NULL;
	// printf("添加任务%d\n", t->getID());
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
		task = m_TaskQueue.pop();//取出列头任务
		if(task == NULL)
		{
			// 任务取出出错
			return 0;
		}
		CMyThread *pThread = PopIdleThread();
		// printf("线程【%d】执行%d\n", pThread->m_threadID, task->getID());
		m_ActiveThreadList.addThread(pThread);
		pThread->assignTask(task);
		pThread->startTask();
	}
	return true;
}

/**
* @brief 开始调度
*/
bool CMyThreadPool::start()
{
	return 0;
}

/**
* @brief 销毁线程池
*/
bool CMyThreadPool::destroyThreadPool()
{
	m_bIsExit = true;
	m_TaskQueue.clear();
	m_IdleThreadStack.clear();
	m_ActiveThreadList.clear();
	return true;
}