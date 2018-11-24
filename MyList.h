/** 
* @file MyList.h
* @brief �߳��б�
*/

#pragma once
#include <list>
#include "MyThread.h"

// �߳��б�
typedef std::list<CMyThread*> ThreadList;

/**
* @class CMyList 
* @brief �߳��б��װ�˶�ThreadList�Ĳ�������
*/
class CMyList
{
public:
	/// Ĭ�Ϲ��캯��
	CMyList() { }

	/// Ĭ����������
	~CMyList() { }

public:

	// ���߳��б����һ���߳�
	inline void addThread(CMyThread *t) { assert(t); m_list.push_back(t); }

	// ���߳��б��Ƴ�һ���߳�(ֻ�Ƴ�����deleteָ��)
	inline void removeThread(CMyThread *t) { assert(t); m_list.remove(t); }

	// ��ȡ�߳��б�Ĵ�С
	inline int getSize() const { return m_list.size(); }

	// �ж��߳��б��Ƿ�Ϊ��
	inline bool isEmpty() const { return m_list.empty(); }
	
	// ɾ���߳��б��е��߳�(�Ƴ�����deleteָ��)
	inline void CMyList::clear()
	{
		for(ThreadList::const_iterator iter = m_list.begin(); iter != m_list.end(); ++iter)
			(*iter)->Exit();
		m_list.clear();
	}

private:
	/// �߳��б�
	ThreadList m_list;
};
