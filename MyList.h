/** 
* @file MyList.h
* @brief 线程列表
*/

#pragma once
#include <list>
#include "MyMutex.h"

class CMyThread;

/**
* @class CMyList 
* @brief 线程线程列表存放了CMyThread指针
*/
class CMyList
{
public:
	/// 默认构造函数
	CMyList() { }

	/// 默认析构函数
	~CMyList() { }

public:
	bool addThread(CMyThread *t);
	bool removeThread(CMyThread *t);
	int getSize();
	bool isEmpty();
	bool clear();

private:
	/// 线程列表
	std::list<CMyThread*> m_list;
	/// 互斥锁
	CMyMutex m_mutex;
};