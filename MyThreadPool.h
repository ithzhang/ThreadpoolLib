/** 
* @file MyThreadPool.h
* @brief �ҵ��̳߳�
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
* @brief �������ȼ� 
*/
enum PRIORITY
{
	NORMAL,			/**< �������ȼ� */
	HIGH			/**< �����ȼ� */
};

/** 
* @class CBaseThreadPool 
* @brief �̳߳ػ���
*/
class CBaseThreadPool
{
public:
	/// ���麯�������Ȼ�߳�
	virtual void SwitchActiveThread(CMyThread *ptd) = 0;
};

/**
* @class CMyThreadPool 
* @brief �̳߳�
* @details �̳߳ذ�������Ҫ�أ������߳�ջ����߳������������
*/
class CMyThreadPool : public CBaseThreadPool
{
public:
	CMyThreadPool(int nDefaultSize, bool autoMgr = true);
	~CMyThreadPool(void);
	// �ı��̳߳صĴ�С
	void ChangeSize(int nSize);

private:
	/// �л���߳�
	virtual void SwitchActiveThread(CMyThread* pThread);

public:
	/// ��������̳߳�
	void addTask(CMyTask *t, PRIORITY priority = PRIORITY::NORMAL);
	/// ��ʼ����
	bool start() { return /* ��ǰ������ */ 0; }
	/// �����̳߳�
	void destroyThreadPool();
	/// ��ȡ��̸߳���
	inline int GetActiveThreadNum() { m_mutex.Lock(); int s = m_ActiveThreadList.getSize(); m_mutex.Unlock(); return s; }
	/// ��ȡ�����̸߳���
	inline int GetIdleThreadNum() { m_mutex.Lock(); int s = m_IdleThreadStack.getSize(); m_mutex.Unlock(); return s; }
	/// ��ȡ�̳߳�����
	inline int GetThreadNum() { m_mutex.Lock(); int n = m_nThreadNum; m_mutex.Unlock(); return n; }
	/// �����Ƿ�ȫ��ִ�����
	inline bool IsTaskDone() { m_mutex.Lock(); bool b = m_TaskQueue.isEmpty(); m_mutex.Unlock(); return b; }
	/// �ȴ����л�߳��������[����Ϊmm]
	inline void Wait(int mm) { while (GetActiveThreadNum()) Sleep(mm); }
	/// ���ù����̵߳�״̬��true-�����У�
	inline void SetMgrThreadState(bool s) { m_bThreadState = s; }
	/// �̳߳��Ƿ�����
	inline const bool& IsExit() const { return m_bIsExit; }
	/// ��ȡ�̳߳���С����
	inline int MinPoolSize() const { return m_nMinSize; }
private:
	/// �̳߳ص�ǰ����
	int m_nThreadNum;
	/// �̳߳���С����
	int m_nMinSize;
	/// �˳��ı��
	bool m_bIsExit;
	/// �����̵߳�״̬
	bool m_bThreadState;

	/// ������(�����������л�����ʱ)
	CMyMutex m_mutex;

	/// �����߳�ջ(���new�������߳�ָ��)
	CMyStack m_IdleThreadStack;
	/// ��߳��б�(���new�������߳�ָ��)
	CMyList m_ActiveThreadList;
	/// �������(���new����������ָ��)
	CMyQueue m_TaskQueue;

	/// ���̳߳������һ���̣߳����ص�ǰ�߳�����
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

	/// ���̳߳������һ���̣߳����ص�ǰ�߳�����
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
// ȫ��Ψһ���̳߳أ�����ʵ������Զ����� (2018-9-29 by Ԭ����)
extern CMyThreadPool g_ThreadPool;

// ���һ����ʱ������
inline void AddTask(StartAddress Callback, void * _ArgList)
{
	if (0 == g_ThreadPool.GetIdleThreadNum())
		g_ThreadPool.ChangeSize(g_ThreadPool.GetThreadNum() * 2);

	return g_ThreadPool.addTask(new CMyTask(Callback, _ArgList));
}

// ���_beginthreadex����
inline void _Beginthreadex(void * _Security, unsigned _StackSize,
						   StartAddress Callback, void * _ArgList, 
						   unsigned _InitFlag, unsigned * _ThrdAddr)
{
	return AddTask(Callback, _ArgList);
}

#ifdef _DEBUG
#define POOL_STEP 1	// ����ʱ����(s),���Թ�����ȡ��Сֵ
#define POOL_TIMES 10 // ��������,���Թ�����ȡ��Сֵ
#else
// ÿ2���Ӷ��̳߳ؽ��ж�̬����
#define POOL_STEP 6
#define POOL_TIMES 20
#endif

/************************** �̳߳���ض������ *********************************/
