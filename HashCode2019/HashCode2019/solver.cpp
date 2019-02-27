#include "solver.h"

Solver::Solver(Params params, const DataReader& reader)
{
    m_Params = params;
    m_Pizza = reader.GetPizza();



    m_Solution.push_back(Output{1});
    m_Solution.push_back(Output{ 2 });
    m_Solution.push_back(Output{ 3 });

}


