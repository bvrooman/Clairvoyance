#include <gtest\gtest.h>

#include "Threading\ClaireThread.h"

using namespace Claire;

TEST(Threading, GetThreadID)
{
	std::cout << "This thread ID: " << this_thread::getID() << "\n";
}

//TEST(Threading, GetThreadIDEqualsCallerThreadID)
//{
//	string idThisThread;
//	Thread thread(getThreadID, idThisThread);
//
//	std::stringstream ss;
//	ss << thread.getID();
//
//	string idThread = ss.str();
//
//	ASSERT_EQ(idThisThread, idThread);
//}