#pragma once

/** 
* @class CTask 任务纯虚基类(提供接口)
* @remark 如果需要在任务完成时回收内存，需重写Destroy
*/
class CTask
{
public:
	/// 构造函数
	CTask(int id);
	/// 析构函数
	~CTask(void);
	/// 回收内存函数
	virtual void Destroy();
	/// 任务执行函数
	virtual void taskProc() = 0;
	/// 获取任务标识
	int getID();
private:
	/// 任务标识
	int m_taskID;
};