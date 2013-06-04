#pragma once
#include "task.h"
class CTestTask :
	public CTask
{
public:
	CTestTask(int id);
	~CTestTask(void);
public:
	virtual void taskProc();
};

