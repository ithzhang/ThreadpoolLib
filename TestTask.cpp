#include "TestTask.h"
CTestTask::CTestTask(int id)
	:CTask(id)
{
}
CTestTask::~CTestTask(void)
{
}
void CTestTask::taskProc()
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
