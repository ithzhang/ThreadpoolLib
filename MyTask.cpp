#include "stdafx.h"
#include "MyTask.h"

/**
* @brief ����һ������
* @param[in] cb			�̺߳���
* @param[in] param		�̲߳���
* @param[in] id			�߳�������
*/
CMyTask::CMyTask(StartAddress cb, void *param, int id): CTask(id), m_param(param), m_Callback(cb)
{
}

/// Ĭ����������
CMyTask::~CMyTask(void)
{
}

/// delete this
void CMyTask::Destroy()
{
	delete this;
}

/// CMyTask���ص�����ִ�к���
void CMyTask::taskProc()
{
	unsigned s = m_Callback(m_param);
}
