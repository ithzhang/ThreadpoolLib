#include <iostream>
#include "MyThreadPool.h"
#include "MyThread.h"
#include "MyTask.h"
#include <vector>

extern CMyThreadPool g_ThreadPool;

class test
{
private:
	int s;

public:
	test(int a) { s = a; g_ThreadPool.addTask(new CMyTask(taskProc, this, a)); }

	void add(int a) { s += a; }

	int get() const { return s; }

	void destroy() { delete this; }

	static unsigned WINAPI taskProc(void *param)
	{
		test *p = (test *) param;
		printf("[%d]线程执行.\n", p->get());
		p->add(100);
		p->destroy();
		return 0;
	}
};

int main(int argc,char**argv)
{
	for(int i = 0; i < 100; i++)
	{
		test *T1 = new test(i);
	}

	// 主线程执行其他工作
	g_ThreadPool.Wait(10);

	system("pause");

	return 0;
}
