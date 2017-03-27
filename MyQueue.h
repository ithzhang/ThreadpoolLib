#pragma once
#include<deque>
#include"MyMutex.h"

class CTask;

/**
* @class CMyQueue 任务队列
* @brief 任务队列里存放了CTask指针
*/
class CMyQueue
{
public:
	CMyQueue(void);
	~CMyQueue(void);
public:
	CTask* pop();
	bool push(CTask *t);
	bool pushFront(CTask *t);//插到队首
	bool isEmpty();
	bool clear();
private:
	std::deque<CTask*> m_TaskQueue;
	CMyMutex m_mutex;
};