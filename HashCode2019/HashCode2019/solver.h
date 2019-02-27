#pragma once
#include "isolver.h"
#include "reader.h"

class Solver : public ISolver
{
    public:
        Solver(Params params, const DataReader& reader);
        virtual ~Solver() {};
        virtual void Solve() {};
        virtual std::vector<Output> GetResult() {
            return m_Solution;
        }

    private:
        Params m_Params;
        std::vector<std::vector<Piece> > m_Pizza;

        std::vector<Output> m_Solution;
};