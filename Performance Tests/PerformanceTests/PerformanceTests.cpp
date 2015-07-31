#define WIN32 1

#include <celero/Celero.h>

#include "ClaireSceneNode.h"

using namespace Claire;
using namespace Claire::rendering;

int main(int argc, char** argv)
{
	celero::Run(argc, argv);
	system("PAUSE");
	return 0;
}

class MyFixture
	: public celero::TestFixture
{
public:
	MyFixture(void)
	{
	}

	using ExperimentValue = std::pair<int64_t, uint64_t>;
	using ProblemSpace = std::vector<ExperimentValue>;

	virtual ProblemSpace getExperimentValues() const override
	{
		ProblemSpace problemSpace;

		const int totalNumberOfTests = 4;

		for (int i = 0; i < totalNumberOfTests; i++)
		{
			problemSpace.push_back(
				std::make_pair(int64_t(i + 1) * 50, uint64_t(0))
				);
		}

		return problemSpace;
	}

	virtual void setUp(int64_t experimentValue) override
	{
		root = new SceneNode();
		Node* n = root;
		for (int i = 0; i < experimentValue; i++)
		{
			n->getTransform().translate(Vector3(0, 1, 0));
			n = n->createChild();
		};
	}

	virtual void tearDown(void) override
	{
		delete root;
	}

public:
	Node* root = 0;
};

BASELINE_F(MySuite, Baseline, MyFixture, 500, 1000)
{
	this->root->update();
}

//BENCHMARK_F(MySuite, Test1, MyFixture, 100, 200)
//{
//	this->root->update();
//}
