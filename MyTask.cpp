#include "MyTask.h"

CMyTask::CMyTask(int id):CTask(id)
{
}

CMyTask::~CMyTask(void)
{
}

void CMyTask::Destroy()
{
	delete this;
}

void CMyTask::taskProc()
{
	for(int i=0;i<10000;i++)
	{
		for(int j=0;j<10000;j++)
		{
			int temp=1;
			temp++;
		}
	}
}