/** 
* @file MyStack.h
* @brief 空闲线程栈
*/

#pragma once
#include<stack>
#include "MyMutex.h"

class CMyThread;

/**
* @class CMyStack 
* @brief 空闲线程(指针)存放在栈上
*/
class CMyStack
{
public:
	/// 默认构造函数
	CMyStack() { }
	/// 默认析构函数
	~CMyStack() { }

	CMyThread* pop();
	bool push(CMyThread *t);
	int getSize();
	bool isEmpty();
	bool clear();
private:
	/// 任务栈
	std::stack<CMyThread*> m_stack;
	/// 互斥锁
	CMyMutex m_mutext;
};