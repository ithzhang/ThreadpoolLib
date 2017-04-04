#include "MyList.h"
#include <cassert>
#include"MyThread.h"

/**
* @brief 向线程列表添加一个线程
* @param[in] *t 线程指针
* @return 成功返回true，t为空时返回false
* @retval bool
*/
bool CMyList::addThread(CMyThread *t)
{
	assert(t);
	if(!t)
		return false;
	m_mutex.Lock();
	m_list.push_back(t);
	m_mutex.Unlock();
	return true;
}

/**
* @brief 向线程列表移除一个线程(只移除，不delete)
* @param[in] *t 线程指针
* @return 成功返回true，t为空时返回false
* @retval bool
*/
bool CMyList::removeThread(CMyThread *t)
{
	assert(t);
	if(!t)
		return false;
	m_mutex.Lock();
	m_list.remove(t);
	m_mutex.Unlock();
	return true;
}

/**
* @brief 获取线程列表的大小
* @return 线程个数
* @retval int
*/
int CMyList::getSize()
{
	m_mutex.Lock();
	int size = m_list.size();
	m_mutex.Unlock();
	return size;
}

/**
* @brief 判断线程列表是否为空
* @return 列表为空时返回true
* @retval bool
*/
bool CMyList::isEmpty()
{
	m_mutex.Lock();
	bool ret = m_list.empty();
	m_mutex.Unlock();
	return ret;
}

/**
* @brief 删除线程列表中的线程(delete指针)
* @return true
* @retval bool
*/
bool CMyList::clear()
{
	m_mutex.Lock();
	std::list<CMyThread*>::iterator iter = m_list.begin();
	for(; iter != m_list.end(); iter++)
	{
		delete (*iter);
	}
	m_list.clear();
	m_mutex.Unlock();
	return true;
}