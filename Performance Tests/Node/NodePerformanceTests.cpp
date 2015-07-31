#include "ClaireDummyNode.h"
#include "ClaireSceneNode.h"

using namespace Claire;
using namespace Claire::rendering;

void clearDataCache(void)
{
	const int size = 16 * 1024 * 1024; // Allocate 16M. Set much larger then L2
	char *c = (char *)malloc(size);
	for (int i = 0; i < 0xf; i++)
		for (int j = 0; j < size; j++)
			c[j] = i*j;
}

auto nodeTest()
{
	Node* root = new SceneNode();
	Node* n = root;
	for (int i = 0; i < 200; i++)
	{
		n->getTransform().translate(Vector3(0, 1, 0));
		n = n->createChild();
	};

	long long t;

	{
		std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

		root->update();

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		
		t = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	}

	delete root;

	return t;
}

int main()
{
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	size_t numTests = 10;
	long long t = 0;
	for (size_t i = 0; i < numTests; i++)
	{
		t += nodeTest();
		clearDataCache();
		std::cout << i + 1 << ", ";
	}
	std::cout << "\n";
	float avgT = t / (float)numTests;

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	long long testTime = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

	std::cout << "Average of " << numTests << ": "<< avgT << " milliseconds. Test took " << testTime << " seconds.\n";

	system("PAUSE");

	return 0;
}