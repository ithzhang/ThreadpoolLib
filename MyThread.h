/** 
* @file MyThread.h
* @brief �ҵ��߳�
*/

#pragma once
#include <cassert>
#include <windows.h>

class CMyTask;
class CBaseThreadPool;

/**
* @class CMyThread 
* @brief �߳���
* @warning ֻ�ܴӶ��ϴ����߳�
*/
class CMyThread
{
private:
	
	bool				m_bIsExit;		/// �����˳�
	
	DWORD				m_threadID;		/// �߳�ID
	
	HANDLE				m_hThread;		/// �߳̾��
	
	HANDLE				m_hEvent;		/// �ź�
	
	CMyTask*			m_pTask;		/// ��ִ������
	
	CBaseThreadPool*	m_pThreadPool;	/// �����̳߳�

protected:
	/// �ر��¼����߳̾��
	~CMyThread() { CloseHandle(m_hEvent); CloseHandle(m_hThread); }
	/// delete this
	inline void Delete() { delete this; }

public:
	/**
	* @brief ��ָ���̳߳��ﹹ��һ���߳�
	* @param[in] *threadPool �̳߳�ָ��
	*/
	CMyThread(CBaseThreadPool *threadPool)
		: m_bIsExit(false), m_threadID(0), m_hThread(INVALID_HANDLE_VALUE)
		, m_hEvent(CreateEvent(NULL, false, false, NULL)), m_pTask(NULL)
		, m_pThreadPool(threadPool) { }

	/// �����߳�
	inline void suspendThread() { ResetEvent(m_hEvent); }
	/// ����������֪ͨ�̼߳���ִ��
	inline void resumeThread() { SetEvent(m_hEvent); }
	/// ��ʼִ������
	inline void startTask() { resumeThread(); }
	/// ֪ͨ�ص������˳���Exit֮����Զ�����Delete��
	inline void Exit() { m_bIsExit = true; resumeThread(); }
	/// ������������߳���
	inline void assignTask(CMyTask *pTask) { m_pTask = pTask; }
	/// ��ʼ�߳�
	inline void startThread()
	{
		 m_hThread = CreateThread(0, 0, threadProc, this, 0, &m_threadID);
	}
	/// �̴߳�����
	static DWORD WINAPI threadProc(LPVOID pParam);
};
