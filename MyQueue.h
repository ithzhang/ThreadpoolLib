/** 
* @file MyQueue.h
* @brief 任务队列
*/

#pragma once
#include<deque>
#include"MyMutex.h"

class CTask;

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
	CTask* pop();
	bool push(CTask *t);
	bool pushFront(CTask *t);//插到队首
	bool isEmpty();
	bool clear();
private:
	/// 任务队列
	std::deque<CTask*> m_TaskQueue;
	/// 互斥锁
	CMyMutex m_mutex;
};