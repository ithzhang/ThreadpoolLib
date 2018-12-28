/** 
* @file MyStack.h
* @brief �����߳�ջ
*/

#pragma once
#include<stack>
#include "MyThread.h"

// �����߳�ջ
typedef std::stack<CMyThread*> IdleThread;

/**
* @class CMyStack 
* @brief �����߳�(ָ��)�����ջ��
*/
class CMyStack
{
public:
	/// Ĭ�Ϲ��캯��
	CMyStack() { }
	/// Ĭ����������
	~CMyStack() { }

	// ȡ���߳�ջ������һ���߳�
	inline CMyThread* pop()
	{
		CMyThread *t = NULL;
		if(!m_stack.empty())
		{
			t = m_stack.top();
			m_stack.pop();
		}
		return t;
	}

	// ���߳�ջ���һ���߳�
	inline void push(CMyThread *t) { assert(t); m_stack.push(t); }

	// ��ȡ�߳�ջ�Ĵ�С
	inline int getSize() const { return m_stack.size(); }

	// �ж��߳�ջ�Ƿ��
	inline bool isEmpty() const { return m_stack.empty(); }

	// ��տ����߳�ջ
	inline void clear()
	{
		while(!m_stack.empty())
		{
			CMyThread *pThread = m_stack.top();
			m_stack.pop();
			pThread->Exit(); // ֪ͨ�߳��˳�
		}
	}

private:
	/// �����߳�ջ
	IdleThread m_stack;
};
