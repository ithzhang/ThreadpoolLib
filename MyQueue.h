/** 
* @file MyQueue.h
* @brief �������
*/

#pragma once
#include <deque>
#include <assert.h>

class CMyTask;

// �������
typedef std::deque<CMyTask*> TaskQueue;

/**
* @class CMyQueue 
* @brief �������������CTaskָ��
*/
class CMyQueue
{
public:
	/// Ĭ�Ϲ��캯��
	CMyQueue() { }
	/// Ĭ����������
	~CMyQueue() { }

public:

	// ȡ����������
	inline CMyTask* pop()
	{
		CMyTask *p = NULL;
		if(!m_TaskQueue.empty())
		{
			p = m_TaskQueue.front();
			m_TaskQueue.pop_front();
		}
		return p;
	}

	// ���β����һ������
	inline void push(CMyTask *t) { assert(t); m_TaskQueue.push_back(t); }

	// ��������һ������
	inline void pushFront(CMyTask *t) { assert(t); m_TaskQueue.push_front(t); }

	// �ж���������Ƿ�Ϊ��
	inline bool isEmpty() const { return m_TaskQueue.empty(); }
	
	// ����������
	inline void clear() { m_TaskQueue.clear(); }

private:
	/// �������
	TaskQueue m_TaskQueue;
};
