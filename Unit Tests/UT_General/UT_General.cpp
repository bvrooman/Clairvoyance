#include <stdio.h>
#include <stdlib.h>

#include <gtest\gtest.h>

#include "Threading\ClaireThread.h"

using namespace Claire;

class Base1
{
public:
	int i;

	Base1()
		: i(1)
	{}
};

class Base2
{
public:
	int j;

	Base2()
		: j(2)
	{}
};

class TestObj
	: public Base1
	, public Base2
{
	int k;
	//int m;
	//int a;
	//int wtf;
	TestObj()
		: Base1()
		//, Base2()
		//, k(3), a(3), wtf(1212)
	{}
};

TEST(TESTTHIG, YOLO)
{
	std::cout << sizeof(TestObj) << "\n";
}