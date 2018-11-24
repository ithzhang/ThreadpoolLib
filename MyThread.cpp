#include "stdafx.h"
#include "MyThread.h"
#include "MyTask.h"
#include "MyThreadPool.h"

// �˳�����
#define EXIT_CODE (0xDEAD)

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
