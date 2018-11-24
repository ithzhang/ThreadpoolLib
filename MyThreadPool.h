/** 
* @file MyThreadPool.h
* @brief 我的线程池
*/

#pragma once

#include "MyStack.h"
#include "MyList.h"
#include"MyQueue.h"
#include "MyThread.h"
#include "MyMutex.h"
#include "MyTask.h"

#pragma warning(disable : 4482)

/** 
* @enum PRIORITY 
* @brief 任务优先级 
*/
enum PRIORITY
{
	NORMAL,			/**< 正常优先级 */
	HIGH			/**< 高优先级 */
};

/** 
* @class CBaseThreadPool 
* @brief 线程池基类
*/
class CBaseThreadPool
{
public:
	/// 纯虚函数：调度活动线程
	virtual void SwitchActiveThread(CMyThread *ptd) = 0;
};

/**
* @class CMyThreadPool 
* @brief 线程池
* @details 线程池包含三个要素：空闲线程栈、活动线程链表、任务队列
*/
class CMyThreadPool : public CBaseThreadPool
{
public:
	CMyThreadPool(int nDefaultSize, bool autoMgr = true);
	~CMyThreadPool(void);
	// 改变线程池的大小
	void ChangeSize(int nSize);

private:
	/// 切换活动线程
	virtual void SwitchActiveThread(CMyThread* pThread);

public:
	/// 添加任务到线程池
	void addTask(CMyTask *t, PRIORITY priority = PRIORITY::NORMAL);
	/// 开始调度
	bool start() { return /* 当前不可用 */ 0; }
	/// 销毁线程池
	void destroyThreadPool();
	/// 获取活动线程个数
	inline int GetActiveThreadNum() { m_mutex.Lock(); int s = m_ActiveThreadList.getSize(); m_mutex.Unlock(); return s; }
	/// 获取空闲线程个数
	inline int GetIdleThreadNum() { m_mutex.Lock(); int s = m_IdleThreadStack.getSize(); m_mutex.Unlock(); return s; }
	/// 获取线程池容量
	inline int GetThreadNum() { m_mutex.Lock(); int n = m_nThreadNum; m_mutex.Unlock(); return n; }
	/// 任务是否全部执行完毕
	inline bool IsTaskDone() { m_mutex.Lock(); bool b = m_TaskQueue.isEmpty(); m_mutex.Unlock(); return b; }
	/// 等待所有活动线程运行完毕[步长为mm]
	inline void Wait(int mm) { while (GetActiveThreadNum()) Sleep(mm); }
	/// 设置管理线程的状态（true-在运行）
	inline void SetMgrThreadState(bool s) { m_bThreadState = s; }
	/// 线程池是否将销毁
	inline const bool& IsExit() const { return m_bIsExit; }
	/// 获取线程池最小容量
	inline int MinPoolSize() const { return m_nMinSize; }
private:
	/// 线程池当前容量
	int m_nThreadNum;
	/// 线程池最小容量
	int m_nMinSize;
	/// 退出的标记
	bool m_bIsExit;
	/// 管理线程的状态
	bool m_bThreadState;

	/// 任务锁(增加任务与切换任务时)
	CMyMutex m_mutex;

	/// 空闲线程栈(存放new出来的线程指针)
	CMyStack m_IdleThreadStack;
	/// 活动线程列表(存放new出来的线程指针)
	CMyList m_ActiveThreadList;
	/// 任务队列(存放new出来的任务指针)
	CMyQueue m_TaskQueue;

	/// 从线程池里减少一个线程（返回当前线程数）
	inline int SubtractThread()
	{
		CMyThread *pThread = m_IdleThreadStack.pop();
		if (pThread)
		{
			pThread->Exit();
			-- m_nThreadNum;
		}
		return m_nThreadNum;
	}

	/// 向线程池里添加一个线程（返回当前线程数）
	inline int AddThread()
	{
		CMyThread *pThread = new CMyThread(this);
		m_IdleThreadStack.push(pThread);
		pThread->startThread();
		++ m_nThreadNum;
		return m_nThreadNum;
	}
};

//////////////////////////////////////////////////////////////////////////
// 全局唯一的线程池，根据实际情况自动调整 (2018-9-29 by 袁沅祥)
extern CMyThreadPool g_ThreadPool;

// 添加一个暂时性任务
inline void AddTask(StartAddress Callback, void * _ArgList)
{
	if (0 == g_ThreadPool.GetIdleThreadNum())
		g_ThreadPool.ChangeSize(g_ThreadPool.GetThreadNum() * 2);

	return g_ThreadPool.addTask(new CMyTask(Callback, _ArgList));
}

// 替代_beginthreadex函数
inline void _Beginthreadex(void * _Security, unsigned _StackSize,
						   StartAddress Callback, void * _ArgList, 
						   unsigned _InitFlag, unsigned * _ThrdAddr)
{
	return AddTask(Callback, _ArgList);
}

#ifdef _DEBUG
#define POOL_STEP 1	// 采样时间间隔(s),测试过程中取较小值
#define POOL_TIMES 10 // 采样次数,测试过程中取较小值
#else
// 每2分钟对线程池进行动态调整
#define POOL_STEP 6
#define POOL_TIMES 20
#endif

/************************** 线程池相关定义结束 *********************************/
