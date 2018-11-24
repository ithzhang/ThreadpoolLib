/** 
* @file MyTask.h
* @brief ����ʵ��
*/

#pragma once

// �̺߳���
typedef unsigned (__stdcall *StartAddress)(void *param);

/**
* @class CMyTask 
* @brief ��ĿThreadPool������ʵ��
*/
class CMyTask
{
private:
	void *m_param;				// �̺߳�������
	StartAddress m_Callback;	// �߳�ִ�к���

protected:
	/// Ĭ����������
	~CMyTask(void) { }

public:
	/**
	* @brief ����һ������
	* @param[in] cb			�̺߳���
	* @param[in] param		�̲߳���
	* @param[in] id			�߳�������
	*/
	CMyTask(StartAddress cb, void *param) : m_param(param), m_Callback(cb) { }

	/// delete this
	inline virtual void Destroy() { delete this; }

	/// CMyTask���ص�����ִ�к���
	inline virtual void taskProc() { unsigned s = m_Callback(m_param); }
};
