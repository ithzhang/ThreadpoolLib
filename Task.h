/** 
* @file Task.h
* @brief ������ࣨ�ӿڣ�
*/

#pragma once

/** 
* @class CTask 
* @brief ���������(�ṩ�ӿ�)
* @remark �����Ҫ���������ʱ�����ڴ棬����дDestroy
*/
class CTask
{
public:
	/// ���캯��
	CTask(int id) : m_taskID(id) { }

	/// ��������
	~CTask() { }

	/// ��ȡ�����ʶ
	inline int getID() { return m_taskID; }

	/// �����ڴ溯��
	virtual void Destroy()  { }

	/// ����ִ�к���
	virtual void taskProc() = 0;

private:
	/// �����ʶ
	int m_taskID;
};
