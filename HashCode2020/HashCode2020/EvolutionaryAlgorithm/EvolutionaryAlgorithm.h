#pragma once
#include "../IAlgorithm.h"
#include <stdint.h>

class CIndividual;

typedef CIndividual** TPopulation;

namespace EPopulationInitMethod
{
	enum TYPE
	{
		Random,
        Greedy,
        Zero,
	};
}

struct SResult
{
	int mean_value;
	int best_value;
	int worst_value;
};

class CEvolutionAlgorithm : public IAlgorithm
{
public:
	CEvolutionAlgorithm(CProblem* problem);

	virtual void StartAlgorithm() override;

private:

	bool LoadParameters(const char* parms_file);

	TPopulation m_Population;

	uint32_t m_GenerationsNumber;
	uint32_t m_PopulationSize;
	float m_MutationProb;
	float m_CrossoverProb;
	uint32_t m_SelectionSize;

	bool InitPopulation(EPopulationInitMethod::TYPE init_method);

	bool RandomPopulationInit(TPopulation new_population) const;
    bool GreedyPopulationInit(TPopulation new_population) const;
    bool ZeroPopulationInit(TPopulation new_population) const;

	float Evaluate(SResult& results);

	TPopulation Select();
	void Mutate(TPopulation population);
	void Crossover(CIndividual* individual);
};
