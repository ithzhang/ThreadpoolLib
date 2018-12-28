/** 
* @file MyTask.h
* @brief 任务实例
*/

#pragma once

// 线程函数
typedef unsigned (__stdcall *StartAddress)(void *param);

/**
* @class CMyTask 
* @brief 项目ThreadPool的任务实例
*/
class CMyTask
{
private:
	void *m_param;				// 线程函数参数
	StartAddress m_Callback;	// 线程执行函数

protected:
	/// 默认析构函数
	~CMyTask(void) { }

public:
	/**
	* @brief 构造一个任务
	* @param[in] cb			线程函数
	* @param[in] param		线程参数
	* @param[in] id			线程任务编号
	*/
	CMyTask(StartAddress cb, void *param) : m_param(param), m_Callback(cb) { }

	/// delete this
	inline virtual void Destroy() { delete this; }

	/// CMyTask重载的任务执行函数
	inline virtual void taskProc() { unsigned s = m_Callback(m_param); }
};
