#include <gtest\gtest.h>

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	int success = RUN_ALL_TESTS();
	system("PAUSE");
	return success;
}