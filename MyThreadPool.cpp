#include "stdafx.h"
#include "MyThreadPool.h"
#include "MyTask.h"
#include<cassert>
#include<iostream>
#include <process.h>

// ȫ��Ψһ���̳߳ر���
CMyThreadPool g_ThreadPool(4);

#ifndef WAIT
// �Բ���n����������C�µȴ�T��(n�ǲ���������������1000�������ı�ʱ�Ͳ��ȴ�, T >= 0.01)
#define WAIT_n(C, T, n) {assert(!(1000%(n)));int s=(1000*(T))/(n);do{Sleep(n);}while((C)&&(--s));}
// ������C����ʱ�ȴ�T��(����10ms)
#define WAIT(C, T) WAIT_n(C, T, 10)
#endif

// �̳߳��̸߳�����̬����
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
* @brief ����һ������ȷ�����̳߳�
* @param[in] nDefaultSize �̳߳�Ĭ������(��С����)
* @param[in] autoMgr �Ƿ����Զ�����
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

/// Ĭ����������
CMyThreadPool::~CMyThreadPool(void)
{
	Wait(10);
	destroyThreadPool();
}

/**
* @brief �ı��̳߳صĴ�С
* @return nSize �̳߳ش�С
*/
void CMyThreadPool::ChangeSize(int nSize)
{
	m_mutex.Lock();
	int n = m_nThreadNum;
	if (nSize > m_nThreadNum)
	{
		while (nSize > m_nThreadNum) AddThread();
		printf("[WARNING] �̳߳ؿ����̲߳���, �뿼�������߳�."
			"======> %d -> %d\n", n, m_nThreadNum);
	}
	else if (nSize < m_nThreadNum)
	{
		while (nSize < m_nThreadNum) SubtractThread();
		printf("[INFO] �̳߳ؿ����߳̽϶�, �뿼���ͷ��߳�."
			"======> %d -> %d\n", n, m_nThreadNum);
	}
	m_mutex.Unlock();
}

/** 
* @brief ���̴߳ӻ����ȡ������������߳�ջ��.��ȡ֮ǰ�жϴ�ʱ��������Ƿ�������.
* ���������Ϊ��ʱ�Ź���,������������ȡ�������ִ��.
*/
void CMyThreadPool::SwitchActiveThread(CMyThread *pThread)
{
	CMyTask *pTask = NULL;
	m_mutex.Lock();
	if(pTask = m_TaskQueue.pop())//������в�Ϊ��,����ȡ����ִ��
	{
		pThread->assignTask(pTask);
		pThread->startTask();
	}
	else//�������Ϊ�գ����̹߳���
	{
		m_ActiveThreadList.removeThread(pThread);
		m_IdleThreadStack.push(pThread);
	}
	m_mutex.Unlock();
}

/**
* @brief �������
* @param[in] *t ����(ָ��)
* @param[in] priority ���ȼ�,�����ȼ������񽫱����뵽����.
*/
void CMyThreadPool::addTask( CMyTask *t, PRIORITY priority )
{
	if(m_bIsExit)
		return;
	CMyTask *task = NULL;
	m_mutex.Lock();
	if(priority == PRIORITY::NORMAL)
	{
		m_TaskQueue.push(t);//�����������
	}
	else if(PRIORITY::HIGH)
	{
		m_TaskQueue.pushFront(t);//�����ȼ�����
	}

	if(!m_IdleThreadStack.isEmpty())//���ڿ����߳�,���ÿ����̴߳�������
	{
		if(task = m_TaskQueue.pop())//ȡ����ͷ����
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
* @brief �����̳߳�
* @details clear m_TaskQueue��m_ActiveThreadList��m_IdleThreadStack
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
