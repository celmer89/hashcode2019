#pragma once
#include "isolver.h"
#include "reader.h"
#include <vector>

class SolverVertical : public ISolver
{
    public:
        SolverVertical(Params params, const DataReader& reader);
        virtual ~SolverVertical() {};
        virtual void Solve() ;
        void  Sort();
        void SortOutData(std::vector<Photo>& in, std::vector<Photo>& outHor, std::vector<Photo> &outVer);

        std::vector<Slide> GetSolution1(std::vector<Photo>& photos);
        std::vector<Slide> GetSolution2(std::vector<Photo>& photos);
        std::vector<Slide> GetSolution3(std::vector<Photo>& photos);

        virtual std::vector<Output> GetResult() {
            return m_Solution;
        }

    private:
        Params m_Params;
        std::vector<std::vector<Piece> > m_Pizza;
        std::vector<Photo> m_Photos;
        std::vector<Output> m_Solution;
};