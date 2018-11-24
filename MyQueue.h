/** 
* @file MyQueue.h
* @brief 任务队列
*/

#pragma once
#include <deque>
#include <assert.h>

class CMyTask;

// 任务队列
typedef std::deque<CMyTask*> TaskQueue;

/**
* @class CMyQueue 
* @brief 任务队列里存放了CTask指针
*/
class CMyQueue
{
public:
	/// 默认构造函数
	CMyQueue() { }
	/// 默认析构函数
	~CMyQueue() { }

public:

	// 取出队首任务
	inline CMyTask* pop()
	{
		CMyTask *p = NULL;
		if(!m_TaskQueue.empty())
		{
			p = m_TaskQueue.front();
			m_TaskQueue.pop_front();
		}
		return p;
	}

	// 向队尾加入一个任务
	inline void push(CMyTask *t) { assert(t); m_TaskQueue.push_back(t); }

	// 向队首添加一个任务
	inline void pushFront(CMyTask *t) { assert(t); m_TaskQueue.push_front(t); }

	// 判断任务队列是否为空
	inline bool isEmpty() const { return m_TaskQueue.empty(); }
	
	// 清空任务队列
	inline void clear() { m_TaskQueue.clear(); }

private:
	/// 任务队列
	TaskQueue m_TaskQueue;
};
