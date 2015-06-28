#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <stdio.h>
#include <algorithm>
#include <Windows.h>

#include "TestThreadClass.h"

float operator "" _deg(long double v)
{
	return v * 2;
}

class Obj
{
public:
	Obj(float i)
		: j(i)
	{

	}

	float j;
};

Obj operator "" _obj(long double v)
{
	return Obj(v);
}

int main()
{
	float i = 2.0_deg;

	Obj j = 8.0_obj;

	std::cout << i << "\n";
	std::cout << j.j << "\n";

	system("PAUSE");
}