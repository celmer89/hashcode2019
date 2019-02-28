#pragma once
#include "isolver.h"
#include "reader.h"

class SolverVertical : public ISolver
{
    public:
        SolverVertical(Params params, const DataReader& reader);
        virtual ~SolverVertical() {};
        virtual void Solve() ;
        virtual std::vector<Output> GetResult() {
            return m_Solution;
        }

    private:
        Params m_Params;
        std::vector<std::vector<Piece> > m_Pizza;
        std::vector<Photo> m_Photos;
        std::vector<Output> m_Solution;
};