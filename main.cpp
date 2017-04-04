#include <iostream>
#include "MyThreadPool.h"
#include "MyThread.h"
#include "MyTask.h"
#include <vector>

int main(int argc,char**argv)
{
	CMyTask *p = NULL;
	CMyThreadPool threadpool(10);
	for(int i = 0; i < 100; i++)
	{
 		p = new CMyTask(i);
		threadpool.addTask(p, PRIORITY::NORMAL);
	}
	p = new CMyTask(1000000);
	threadpool.addTask(p, PRIORITY::HIGH);
	
	// 主线程执行其他工作
	while (threadpool.GetActiveThreadNum())
	{
		Sleep(10);
	}
	threadpool.destroyThreadPool();

	system("pause");

	return 0;
}