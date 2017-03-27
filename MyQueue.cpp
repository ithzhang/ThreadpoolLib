#include "MyQueue.h"
#include"task.h"

CMyQueue::CMyQueue(void)
{
}


CMyQueue::~CMyQueue(void)
{
}

/**
* @brief 取出队首任务
* @remark 当队列为空时pop为NULL
*/
CTask* CMyQueue::pop()
{
	CTask *p = NULL;
	m_mutex.Lock();
	if(!m_TaskQueue.empty())
	{
		p = m_TaskQueue.front();
		m_TaskQueue.pop_front();
	}
	m_mutex.Unlock();
	return p;
}

/**
* @brief 向队尾加入一个任务
* @param[in] *t 任务指针
* @remark 当指针为空时失败
*/
bool CMyQueue::push(CTask *t)
{
	if(!t)
	{
		return false;
	}
	m_mutex.Lock();
	m_TaskQueue.push_back(t);
	m_mutex.Unlock();
	return true;
}

/**
* @brief 判断任务队列是否为空
* @return 队列为空返回true
*/
bool CMyQueue::isEmpty()
{
	bool ret = false;
	m_mutex.Lock();
	ret = m_TaskQueue.empty();
	m_mutex.Unlock();
	return ret;
}

/**
* @brief 向队首添加一个任务
* @param[in] *t 任务指针
*/
bool CMyQueue::pushFront(CTask *t)
{
	if(!t)
	{
		return false;
	}
	m_mutex.Lock();
	m_TaskQueue.push_front(t);
	m_mutex.Unlock();
	return true;
}

/**
* @brief 清除任务队列
* @warning 不回收队列中的指针的内存
*/
bool CMyQueue::clear()
{
	m_mutex.Lock();
	m_TaskQueue.clear();
	m_mutex.Unlock();
	return true;
}