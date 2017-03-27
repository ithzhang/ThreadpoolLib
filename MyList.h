#pragma once
#include <list>
#include "MyMutex.h"

class CMyThread;

/**
* @class CMyList 线程列表
* 线程列表存放了CMyThread指针
*/
class CMyList
{
public:
	CMyList(void);
	~CMyList(void);

public:
	bool addThread(CMyThread *t);
	bool removeThread(CMyThread *t);
	int getSize();
	bool isEmpty();
	bool clear();

private:
	std::list<CMyThread*> m_list;
	CMyMutex m_mutex;
};