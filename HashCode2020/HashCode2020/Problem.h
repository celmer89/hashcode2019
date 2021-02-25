#pragma once
#include <vector>

typedef std::vector<int> TSolution;

struct SData;

class CProblem
{
public:
	CProblem(const SData* problem_data);

	virtual bool Prepare();
	TSolution* GetSolution() { return &m_Solution; }
	TSolution GetGreedySolution();

	int Evaluate(TSolution& solution);

protected:

	const SData* m_ProblemData;
	TSolution m_Solution;
};
