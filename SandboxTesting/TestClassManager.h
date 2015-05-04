#include "TestClass.h"

#include <map>

class TestClassManager
{
public:
	TestClassManager(void);
	~TestClassManager(void);

protected:
	typedef std::map<std::string, TestClassUPtr> TestClassMap;
	TestClassMap mTestClassMap;
};