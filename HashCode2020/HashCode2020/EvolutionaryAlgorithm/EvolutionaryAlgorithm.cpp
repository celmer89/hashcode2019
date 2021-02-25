#include "EvolutionaryAlgorithm.h"
#include "Individual.h"
#include "../Problem.h"

#include <limits>
#include <time.h>

#include <iostream>
#include <fstream>
#include <string>

#define FLOAT_MAX std::numeric_limits<float>::max()

const char* PARAMS_FILE_NAME = "ev_alg_params.prm";

CEvolutionAlgorithm::CEvolutionAlgorithm(CProblem* problem)
	: IAlgorithm(problem)
	, m_Population(nullptr)
	, m_PopulationSize(200)
	, m_CrossoverProb(0.20f)
	, m_MutationProb(0.03f)
	, m_SelectionSize(10)
	, m_GenerationsNumber(5000)
{
	srand((unsigned int)time(NULL));
}

void CEvolutionAlgorithm::StartAlgorithm()
{
	//LoadParameters(PARAMS_FILE_NAME);
	InitPopulation(EPopulationInitMethod::Zero);

	SResult* results = new SResult[m_GenerationsNumber];
	float result = Evaluate(results[0]);
    int best_value = results[0].best_value;

	for (int i = 1; i < m_GenerationsNumber; ++i)
	{
		TPopulation new_population = Select();
		Mutate(new_population);

		for (int i = 0; i < m_PopulationSize; ++i)
		{
			delete m_Population[i];
		}

		delete[] m_Population;
		m_Population = new_population;

		result = Evaluate(results[i]);
        printf("Mean Result: %.4f, Best Result: %d\n", result, int(results[i].best_value));

        if (results[i].best_value > best_value)
            best_value = results[i].best_value;
	}

    printf("Final Mean: %.4f\n", result);
    printf("Final Best: %d\n", best_value);

	//
// 	std::ofstream output_file;
// 	output_file.open("results.csv");
// 
// 	output_file << "Iteration,Worst,Mean,Best" << std::endl;
// 	for (int i = 0; i < m_GenerationsNumber; ++i)
// 	{
// 		output_file << i << "," << results[i].worst_value << "," << results[i].mean_value << "," << results[i].best_value << std::endl;
// 	}
// 
// 	output_file.close();
// 	delete[] results;
	//
}

void CEvolutionAlgorithm::Mutate(TPopulation population)
{
	for (int i = 0; i < m_PopulationSize; ++i)
	{
        population[i]->Mutate(m_MutationProb);
	}
}

void CEvolutionAlgorithm::Crossover(CIndividual* individual)
{
	float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if (random > m_CrossoverProb)
	{
		int random_other = rand() % m_PopulationSize;
		individual->Crossover(m_Population[random_other]);
	}
}

TPopulation CEvolutionAlgorithm::Select()
{
	TPopulation new_population = new CIndividual*[m_PopulationSize];
	for (int i = 0; i < m_PopulationSize; ++i)
	{
		float best_val = -FLOAT_MAX;
		int best_ind = m_PopulationSize + 1;
		for (int j = 0; j < m_SelectionSize; ++j)
		{
			int random = rand() % m_PopulationSize;
			CIndividual* ind = m_Population[random];

			float val = m_pProblem->Evaluate(ind->m_Solution);

			if (val > best_val)
			{
				best_val = val;
				best_ind = random;
			}
		}
		new_population[i] = new CIndividual();
		new_population[i]->m_Solution = m_Population[best_ind]->m_Solution;
		Crossover(new_population[i]);
	}

	return new_population;
}

float CEvolutionAlgorithm::Evaluate(SResult& results)
{
	float result = 0.f;
	float best = -FLOAT_MAX;
	float worst = FLOAT_MAX;
	for (uint32_t i = 0; i < m_PopulationSize; ++i)
	{
		float result_part = m_pProblem->Evaluate(m_Population[i]->m_Solution);
		result += result_part;
		if (result_part > best)
			best = result_part;
		if (result_part < worst)
			worst = result_part;
	}
	results.best_value = best;
	results.mean_value = result / m_PopulationSize;
	results.worst_value = worst;
	return result / m_PopulationSize;
}

bool CEvolutionAlgorithm::InitPopulation(EPopulationInitMethod::TYPE init_method)
{
	bool init_result = false;
	TPopulation new_population = new CIndividual*[m_PopulationSize];

	switch (init_method)
	{
	case EPopulationInitMethod::Random:
		init_result = RandomPopulationInit(new_population);
		break;
	case EPopulationInitMethod::Greedy:
		init_result = GreedyPopulationInit(new_population);
        break;
    case EPopulationInitMethod::Zero:
        init_result = ZeroPopulationInit(new_population);
		//default:
		// Warning!
	}

	if (!init_result)
	{
		delete[] new_population;
		new_population = nullptr;
	}
	else
	{
		m_Population = new_population;
	}

	return init_result;
}

bool CEvolutionAlgorithm::RandomPopulationInit(TPopulation new_population) const
{
	for (uint32_t i = 0; i < m_PopulationSize; ++i)
	{
		TSolution curr_data = *m_pProblem->GetSolution();
		new_population[i] = new CIndividual();



// 		while (curr_data.size() > 0)
// 		{
// 			int r_data_index = rand() % curr_data.size();
// 			SCoord data_in = curr_data[r_data_index];
// 
// 			LOG("Choosen point (%.2f, %.2f)\n", data_in.x_pos, data_in.y_pos);
// 			new_population[i]->m_Data.push_back(data_in);
// 			curr_data.erase(curr_data.begin() + r_data_index);
// 		}
	}

	return true;
}

bool CEvolutionAlgorithm::GreedyPopulationInit(TPopulation new_population) const
{
	for (uint32_t i = 0; i < m_PopulationSize; ++i)
	{
        TSolution curr_data = m_pProblem->GetGreedySolution();
        new_population[i] = new CIndividual();
        new_population[i]->m_Solution = curr_data;
	}

	return true;
}

bool CEvolutionAlgorithm::ZeroPopulationInit(TPopulation new_population) const
{
    for (uint32_t i = 0; i < m_PopulationSize; ++i)
    {
        TSolution curr_data = *m_pProblem->GetSolution();
        new_population[i] = new CIndividual();
        new_population[i]->m_Solution = curr_data;
    }

    return true;
}

bool CEvolutionAlgorithm::LoadParameters(const char* parms_file)
{
	std::ifstream data_file;
	data_file.open(parms_file);
	std::string value_name = "";

	printf("Loading parameters\n");
	if (data_file.is_open())
	{
		while (!data_file.eof())
		{
			data_file >> value_name;

			printf("Read: %s\n", value_name.c_str());

			if (value_name.compare("m_PopulationSize") == 0)
			{
				data_file >> m_PopulationSize;
				printf("Set m_PopulationSize to (%d)\n", m_PopulationSize);
			}
			else if (value_name.compare("m_GenerationsNumber") == 0)
			{
				data_file >> m_GenerationsNumber;
				printf("Set m_GenerationsNumber to (%d)\n", m_GenerationsNumber);
			}
			else if (value_name.compare("m_SelectionSize") == 0)
			{
				data_file >> m_SelectionSize;
				printf("Set m_SelectionSize to (%d)\n", m_SelectionSize);
			}
			else if (value_name.compare("m_MutationProb") == 0)
			{
				data_file >> m_MutationProb;
				printf("Set m_MutationProb to (%.4f)\n", m_MutationProb);
			}
			else if (value_name.compare("m_CrossoverProb") == 0)
			{
				data_file >> m_CrossoverProb;
				printf("Set m_CrossoverProb to (%.4f)\n", m_CrossoverProb);
			}
		}
	}
	data_file.close();

	return true;
}