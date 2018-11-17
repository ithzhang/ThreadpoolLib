/** 
* @file MyTask.h
* @brief 任务实例
*/

#pragma once
#include "task.h"

// 线程函数
typedef unsigned (__stdcall *StartAddress)(void *param);

/**
* @class CMyTask 
* @brief 项目ThreadPool的任务实例
*/
class CMyTask : public CTask
{
public:
	void *m_param;				// 线程函数参数
	StartAddress m_Callback;	// 线程函数
	CMyTask(StartAddress cb, void *param, int id);

protected:
	~CMyTask(void);

public:
	_inline virtual void Destroy();
	_inline virtual void taskProc();
};
