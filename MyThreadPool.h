#pragma once

#include<list>
#include "MyMutex.h"
#include "MyStack.h"
#include "MyList.h"
#include"MyQueue.h"

class CMyThread;
class CTask;

/** 
* @enum PRIORITY 任务优先级 
*/
enum PRIORITY
{
	NORMAL,
	HIGH
};

/** 
* @class CBaseThreadPool 线程池基类
*/
class CBaseThreadPool
{
public:
	virtual bool SwitchActiveThread(CMyThread *ptd) = 0;
};

/**
* @class CMyThreadPool 线程池
* 线程池包含三个要素：空闲线程栈、活动线程链表、任务队列
*/
class CMyThreadPool : public CBaseThreadPool
{
public:
	CMyThreadPool(int num);
	~CMyThreadPool(void);
public:
	virtual CMyThread* PopIdleThread();
	virtual bool SwitchActiveThread(CMyThread* pThread);

public:
	/// 添加任务到线程池
	bool addTask(CTask *t,PRIORITY priority);
	/// 开始调度
	bool start();
	/// 销毁线程池
	bool destroyThreadPool();
	/// 获取活动线程个数
	int GetActiveThreadNum() { return m_ActiveThreadList.getSize(); }

private:
	/// 线程池容量
	int m_nThreadNum;
	/// 退出的标记
	bool m_bIsExit;

	/// 空闲线程栈(存放new出来的线程指针)
	CMyStack m_IdleThreadStack;
	/// 活动线程列表(存放new出来的线程指针)
	CMyList m_ActiveThreadList;
	/// 任务队列(存放new出来的任务指针)
	CMyQueue m_TaskQueue;
};