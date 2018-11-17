#include "stdafx.h"
#include "MyTask.h"

/**
* @brief 构造一个任务
* @param[in] cb			线程函数
* @param[in] param		线程参数
* @param[in] id			线程任务编号
*/
CMyTask::CMyTask(StartAddress cb, void *param, int id): CTask(id), m_param(param), m_Callback(cb)
{
}

/// 默认析构函数
CMyTask::~CMyTask(void)
{
}

/// delete this
void CMyTask::Destroy()
{
	delete this;
}

/// CMyTask重载的任务执行函数
void CMyTask::taskProc()
{
	unsigned s = m_Callback(m_param);
}
