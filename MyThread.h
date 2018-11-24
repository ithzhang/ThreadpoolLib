/** 
* @file MyThread.h
* @brief 我的线程
*/

#pragma once
#include <cassert>
#include <windows.h>

class CMyTask;
class CBaseThreadPool;

/**
* @class CMyThread 
* @brief 线程类
* @warning 只能从堆上创建线程
*/
class CMyThread
{
private:
	
	bool				m_bIsExit;		/// 发起退出
	
	DWORD				m_threadID;		/// 线程ID
	
	HANDLE				m_hThread;		/// 线程句柄
	
	HANDLE				m_hEvent;		/// 信号
	
	CMyTask*			m_pTask;		/// 所执行任务
	
	CBaseThreadPool*	m_pThreadPool;	/// 所属线程池

protected:
	/// 关闭事件及线程句柄
	~CMyThread() { CloseHandle(m_hEvent); CloseHandle(m_hThread); }
	/// delete this
	inline void Delete() { delete this; }

public:
	/**
	* @brief 在指定线程池里构造一个线程
	* @param[in] *threadPool 线程池指针
	*/
	CMyThread(CBaseThreadPool *threadPool)
		: m_bIsExit(false), m_threadID(0), m_hThread(INVALID_HANDLE_VALUE)
		, m_hEvent(CreateEvent(NULL, false, false, NULL)), m_pTask(NULL)
		, m_pThreadPool(threadPool) { }

	/// 挂起线程
	inline void suspendThread() { ResetEvent(m_hEvent); }
	/// 有任务到来，通知线程继续执行
	inline void resumeThread() { SetEvent(m_hEvent); }
	/// 开始执行任务
	inline void startTask() { resumeThread(); }
	/// 通知回调函数退出（Exit之后会自动调用Delete）
	inline void Exit() { m_bIsExit = true; resumeThread(); }
	/// 将任务关联到线程类
	inline void assignTask(CMyTask *pTask) { m_pTask = pTask; }
	/// 开始线程
	inline void startThread()
	{
		 m_hThread = CreateThread(0, 0, threadProc, this, 0, &m_threadID);
	}
	/// 线程处理函数
	static DWORD WINAPI threadProc(LPVOID pParam);
};
