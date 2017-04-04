#include "MyTask.h"

/**
* @brief 构造一个任务
* @param[in] id 任务编号
*/
CMyTask::CMyTask(int id):CTask(id)
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
	for(int i=0;i<10000;i++)
	{
		for(int j=0;j<10000;j++)
		{
			int temp=1;
			temp++;
		}
	}
}