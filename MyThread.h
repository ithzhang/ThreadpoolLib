/** 
* @file MyThread.h
* @brief �ҵ��߳�
*/

#pragma once
#include <cassert>
#include <windows.h>

class CTask;
class CBaseThreadPool;

/**
* @class CMyThread 
* @brief �߳���
* @warning ֻ�ܴӶ��ϴ����߳�
*/
class CMyThread
{
public:
	CMyThread(CBaseThreadPool *threadPool);

protected:
	~CMyThread();
	/// delete this
	inline void Delete() { delete this; }

public:
	/// �����߳�
	inline void suspendThread() { ResetEvent(m_hEvent); }
	/// ����������֪ͨ�̼߳���ִ��
	inline void resumeThread() { SetEvent(m_hEvent); }
	/// ��ʼִ������
	inline void startTask() { resumeThread(); }
	/// ֪ͨ�ص������˳���Exit֮����Զ�����Delete��
	inline void Exit() { m_bIsExit = true; resumeThread(); }
	/// ������������߳���
	inline bool assignTask(CTask *pTask)
	{
		assert(pTask);
		m_pTask = pTask;
		return (NULL == pTask) ? false : true;
	}

	/// ��ʼ�߳�
	inline bool startThread()
	{
		m_hThread = CreateThread(0, 0, threadProc, this, 0, &m_threadID);
		return (INVALID_HANDLE_VALUE == m_hThread) ? false : true;
	}

	/// �̴߳�����
	static DWORD WINAPI threadProc(LPVOID pParam);

	/// �߳�ID
	DWORD m_threadID;
	/// �߳̾��
	HANDLE m_hThread;
	/// �����˳�
	bool m_bIsExit;

private:
	/// �ź�
	HANDLE m_hEvent;
	/// ��ִ������
	CTask *m_pTask;
	/// �����̳߳�
	CBaseThreadPool *m_pThreadPool;	
};
