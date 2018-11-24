#include <iostream>
#include "MyThreadPool.h"
#include "MyThread.h"
#include "MyTask.h"
#include <vector>

class test
{
private:
	int s;

public:
	test(int a) { s = a; AddTask(taskProc, this); }

	void add(int a) { s += a; }

	int get() const { return s; }

	void destroy() { delete this; }

	static unsigned WINAPI taskProc(void *param)
	{
		test *p = (test *) param;
		printf("[%d]Ïß³ÌÖ´ÐÐ.\n", p->get());
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

	system("pause");

	return 0;
}
