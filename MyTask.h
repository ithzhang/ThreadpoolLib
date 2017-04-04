/** 
* @file MyTask.h
* @brief 任务实例
*/

#pragma once
#include "task.h"

/**
* @class CMyTask 
* @brief 项目ThreadPool的任务实例
*/
class CMyTask : public CTask
{
public:
	CMyTask(int id);
protected:
	~CMyTask(void);
public:
	_inline virtual void Destroy();
	virtual void taskProc();
};

