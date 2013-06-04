#pragma once
#include<list>
#include "MyMutex.h"
#include "MyStack.h"
#include "MyList.h"
#include"MyQueue.h"
class CMyThread;
class CTask;
enum PRIORITY
{
	NORMAL,
	HIGH
};
class CBaseThreadPool
{
public:
	virtual bool SwitchActiveThread(CMyThread*)=0;
};
class CMyThreadPool:public CBaseThreadPool
{
public:
	CMyThreadPool(int num);
	~CMyThreadPool(void);
public:
	virtual CMyThread* PopIdleThread();
	virtual bool SwitchActiveThread(CMyThread*);
	virtual CTask*GetNewTask();
public:
	//priority为优先级。高优先级的任务将被插入到队首。
	bool addTask(CTask*t,PRIORITY priority);
	bool start();//开始调度。
	bool destroyThreadPool();
private:
	int m_nThreadNum;
	bool m_bIsExit;
	
	CMyStack m_IdleThreadStack;
	CMyList m_ActiveThreadList;
	CMyQueue m_TaskQueue;
};

