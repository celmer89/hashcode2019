#pragma once
#include "isolver.h"
#include "reader.h"

class Solver : public ISolver
{
    public:
        Solver(Params params, const DataReader& reader);
        virtual ~Solver() {};
        virtual void Solve() {};
        virtual void GetResult() {};

    private:
        Params m_Params;
        std::vector<std::vector<Piece> > m_Pizza;
};