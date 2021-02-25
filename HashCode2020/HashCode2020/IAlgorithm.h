#pragma once

class CProblem;

class IAlgorithm
{

public:
	IAlgorithm(CProblem* problem)
		: m_pProblem(problem)
	{}

	virtual void StartAlgorithm() = 0;

protected:
	CProblem* m_pProblem;
};
