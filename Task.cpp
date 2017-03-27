#include "Task.h"

/// 构造函数
CTask::CTask(int id):m_taskID(id)
{
}

/// 析构函数
CTask::~CTask(void)
{
}

/// 回收内存函数
void CTask::Destroy() 
{
}

/// 获取任务标识
int CTask::getID()
{ 
	return m_taskID; 
}