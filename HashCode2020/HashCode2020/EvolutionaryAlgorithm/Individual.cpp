#include "Individual.h"

void CIndividual::Mutate(float mutation_prob)
{
	// check mutation for each position
	for (int i = 0; i < m_Solution.size(); ++i)
	{
		float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		if (random < mutation_prob)
		{
            m_Solution[i] = !m_Solution[i];
		}
	}
}

void CIndividual::Crossover(CIndividual* other)
{
	int first_pos = rand() % m_Solution.size();

	for (int i = first_pos; i < m_Solution.size(); ++i)
	{
		m_Solution[i] = other->m_Solution[i];
	}
}