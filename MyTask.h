/** 
* @file MyTask.h
* @brief ����ʵ��
*/

#pragma once
#include "task.h"

// �̺߳���
typedef unsigned (__stdcall *StartAddress)(void *param);

/**
* @class CMyTask 
* @brief ��ĿThreadPool������ʵ��
*/
class CMyTask : public CTask
{
public:
	void *m_param;				// �̺߳�������
	StartAddress m_Callback;	// �̺߳���
	CMyTask(StartAddress cb, void *param, int id);

protected:
	~CMyTask(void);

public:
	_inline virtual void Destroy();
	_inline virtual void taskProc();
};
