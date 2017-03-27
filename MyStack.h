#pragma once
#include<stack>
#include "MyMutex.h"

class CMyThread;

/**
* @class CMyStack 空闲线程栈
* @brief 空闲线程(指针)存放在栈上
*/
class CMyStack
{
public:
	CMyStack(void);
	~CMyStack(void);
public:
	CMyThread* pop();
	bool push(CMyThread *t);
	int getSize();
	bool isEmpty();
	bool clear();
private:
	std::stack<CMyThread*> m_stack;
	CMyMutex m_mutext;
};