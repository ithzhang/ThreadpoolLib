#include "MyStack.h"
#include<cassert>
#include"MyThread.h"

CMyStack::CMyStack(void)
{
}

CMyStack::~CMyStack(void)
{
}

/**
* @brief 取出线程栈顶部的一个线程
* @return 线程指针
* @remark 栈空时返回NULL
*/
CMyThread* CMyStack::pop()
{
	m_mutext.Lock();
	if(!m_stack.empty())
	{
		CMyThread *t = m_stack.top();
		m_stack.pop();
		m_mutext.Unlock();
		return t;
	}
	m_mutext.Unlock();
	return NULL;
}

/**
* @brief 向线程栈添加一个线程
* @param[in] *t 线程指针
*/
bool CMyStack::push(CMyThread *t)
{
	assert(t);
	if(!t)
		return false;
	m_mutext.Lock();
	m_stack.push(t);
	m_mutext.Unlock();
	return true;
}

/**
* @brief 获取线程栈的大小
* @return 线程个数
*/
int CMyStack::getSize()
{
	m_mutext.Lock();
	int size = m_stack.size();
	m_mutext.Unlock();
	return size;
}

/**
* @brief 判断线程栈是否空
* @return 空时返回true
*/
bool CMyStack::isEmpty()
{
	m_mutext.Lock();
	bool ret = m_stack.empty();
	m_mutext.Unlock();
	return ret;
}

/**
* @brief 清空空闲线程栈
* @remark 将会回收线程指针的内存
*/
bool CMyStack::clear()
{
	m_mutext.Lock();
	CMyThread *pThread = NULL;
	while(!m_stack.empty())
	{
		pThread = m_stack.top();
		m_stack.pop();
		// 让线程自然退出
		pThread->m_bIsExit = true;
		pThread->resumeThread();
		// 等待线程退出
		while (!pThread->m_bHasExit)
		{
			Sleep(1);
		}
		delete pThread;
	}
	m_mutext.Unlock();
	return true;
}