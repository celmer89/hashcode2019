#pragma once

#include "../Problem.h"

class CIndividual
{
public:

	CIndividual()
	{
		//printf("created\n");
	}

	TSolution m_Solution;

	void Mutate(float mutation_prob);
	void Crossover(CIndividual* other);

private:

};