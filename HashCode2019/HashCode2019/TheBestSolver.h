#pragma once
#include "solver.h"
#include "reader.h"

class TheBestSolver : public Solver
{
public:
    TheBestSolver(Params params, const DataReader& reader);

    void Solve() override;

    int GetScore(const TagsSet& set1, const TagsSet& set2)
    {
        int intersection = set1.intersection(set2).size();
        int cond1 = intersection;
        int cond2 = set1.size() - intersection;
        int cond3 = set2.size() - intersection;

        return std::min(cond1, std::min(cond2, cond3));
    }

public:
    std::vector<Slide> slides;
};

