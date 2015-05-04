#include "ClaireDummyNode.h"
using namespace Claire;
using namespace Claire::rendering;

void nodeTest()
{
	Node* root = new DummyNode();
	Node* n = root;
	for (int i = 0; i < 200; i++)
	{
		n->getTransform().translate(Vector3(0, 1, 0));
		n = n->createChild();
	};

	{
		std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

		root->update();

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::cout
			<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
			<< "\n";
	}

	delete root;
}

int main()
{
	nodeTest();

	system("PAUSE");

	return 0;
}