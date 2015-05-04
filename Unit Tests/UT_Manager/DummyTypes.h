#ifndef DUMMY_TYPES_H
#define DUMMY_TYPES_H

#include "ClairePrerequisites.h"

class MyBaseType
{
public:
	virtual int foo(void) CLAIRE_ABSTRACT;
};

typedef std::unique_ptr<MyBaseType> MyBaseTypeUPtr;

class MyDerivedType
	: public MyBaseType
{
public:
	MyDerivedType(void)
		: mInt(100)
	{
	}

	int foo(void) CLAIRE_OVERRIDE
	{
		return mInt;
	}

private:
	int mInt;
};

#endif