#ifndef TEST_THREAD_CLASS_H
#define TEST_THREAD_CLASS_H

#include "TSPtr.h"

#define ABSTRACT = 0

class TestThreadClass
{
public:
	TestThreadClass(void) {}
	~TestThreadClass(void) {}

	void test(void)
	{

	}

private:
	TSPtr<int> mTSPtr;
};

#endif