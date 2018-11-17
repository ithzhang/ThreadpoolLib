#include "stdafx.h"
#include "MyThread.h"
#include "task.h"
#include "MyThreadPool.h"

// �˳�����
#define EXIT_CODE (0xDEAD)

/**
* @brief ���̳߳��ﹹ��һ���߳�
* @param[in] *threadPool �̳߳�ָ��
*/
CMyThread::CMyThread(CBaseThreadPool *threadPool)
{
	m_pTask = NULL;
	m_pThreadPool = threadPool;
	m_hEvent = CreateEvent(NULL, false, false, NULL);
	m_bIsExit = false;
}

/// �ر��¼����߳̾��
CMyThread::~CMyThread()
{
	CloseHandle(m_hEvent);
	CloseHandle(m_hThread);
}

/// �߳�ִ�к���
DWORD WINAPI CMyThread::threadProc(LPVOID pParam)
{
	CMyThread *pThread = (CMyThread*)pParam;
	DWORD ret = 1; // �̳߳�������ʱ����
	do // ���߳�δ�˳�ʱѭ���ȴ�ִ������
	{
		if(ret == WAIT_OBJECT_0)// 0
		{
			if(pThread->m_pTask)
			{
				pThread->m_pTask->taskProc();// ִ������
				pThread->m_pTask->Destroy();
				pThread->m_pTask = NULL;
				pThread->m_pThreadPool->SwitchActiveThread(pThread);
			}
		}
		// �ȴ�����
		ret = WaitForSingleObject(pThread->m_hEvent, INFINITE);
	}while(!pThread->m_bIsExit);
	pThread->Delete();
	pThread = NULL;

	// OpenCV3���OpenCLʹ��ʱ���߳��˳�ʱ�������⣬��throw.cpp��152���ж�
	// ����ȴ����߳�����������������ɽ����˳�
#if defined(USING_OCL) && OPENCV_VERSION > 2
	Sleep(INFINITE);
#endif

	return EXIT_CODE;
}
