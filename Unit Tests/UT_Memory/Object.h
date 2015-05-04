#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <iostream>

using std::string;

struct Object
{
	string name;
	int a;
	int b;
	int c;
	float d;

	Object(void)
		: name("Hello World"), a(0), b(0), c(0), d(0.0f)
	{
	}

	~Object(void) = default;

	Object(const string& n)
		: name(n), a(0), b(0), c(0), d(0.0f)
	{
	}

	void print(void)
	{
		std::cout << name << "\n";
	}
};

#endif