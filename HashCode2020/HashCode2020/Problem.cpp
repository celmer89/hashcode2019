#include "stdafx.h"

#include "Problem.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Reader.h"

CProblem::CProblem(const SData* problem_data)
	: m_ProblemData(problem_data)
{
}

bool CProblem::Prepare()
{
	m_Solution = std::vector<int>(m_ProblemData->types_count, 0);
	return true;
}

TSolution CProblem::GetGreedySolution()
{

	int target_count = m_ProblemData->maximum_slices;
	int current_slices = 0;
	int pizza_types = m_ProblemData->types_count;

	TSolution greedy_solution(pizza_types, 0);

	for (int i = pizza_types - 1; i >= 0 && current_slices < target_count; --i)
	{
		if (m_ProblemData->slices_count[i] + current_slices <= target_count)
		{
			current_slices += m_ProblemData->slices_count[i];
			greedy_solution[i] = 1;
		}
	}

	return greedy_solution;
}

int CProblem::Evaluate(TSolution& solution)
{
	int scores = 0;

	int slices_sum = 0;
	for (int i = 0; i < solution.size(); ++i)
	{
		if (solution[i] == 1)
			slices_sum += m_ProblemData->slices_count[i];
	}

	if (slices_sum > m_ProblemData->maximum_slices)
	{
		//printf("Constraint not met, slices count > maximum limit!");
	}
	else
	{
		scores = slices_sum;
	}

	return scores;
}