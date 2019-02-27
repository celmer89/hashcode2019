#include "solver.h"

Solver::Solver(Params params, const DataReader& reader)
{
    m_Params = params;
    m_Pizza = reader.GetPizza();
}