#include "MyStack.h"
#include<cassert>
#include"MyThread.h"
CMyStack::CMyStack(void)
{
}
CMyStack::~CMyStack(void)
{
}
CMyThread* CMyStack::pop()
{
	m_mutext.Lock();
	if(!m_stack.empty())
	{
		CMyThread *t=m_stack.top();
		m_stack.pop();
		m_mutext.Unlock();
		return t;
	}
	m_mutext.Unlock();
	return NULL;
}
bool CMyStack::push( CMyThread* t)
{
	assert(t);
	if(!t)
		return false;
	m_mutext.Lock();
	m_stack.push(t);
	m_mutext.Unlock();
	return true;
}
int CMyStack::getSize()
{
	m_mutext.Lock();
	int size= m_stack.size();
	m_mutext.Unlock();
	return size;
}
bool CMyStack::isEmpty()
{
	m_mutext.Lock();
	bool ret= m_stack.empty();
	m_mutext.Unlock();
	return ret;
}
bool CMyStack::clear()
{
	m_mutext.Lock();
	CMyThread*pThread=NULL;
	while(!m_stack.empty())
	{
		pThread=m_stack.top();
		m_stack.pop();
		pThread->resumeThread();
		pThread->m_bIsExit=true;
		delete pThread;
	}
	m_mutext.Unlock();
	return true;
}
