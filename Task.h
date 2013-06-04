#pragma once
class CTask
{
public:
	CTask(int id);
	~CTask(void);
public:
	virtual void taskProc()=0;
	int getID();
private:
	int m_ID;
};

