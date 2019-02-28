#include "SolverVertical.h"
#include <algorithm>
#include <vector>
#include <map>

SolverVertical::SolverVertical(Params params, const DataReader& reader)
{
    m_Params = params;
    m_Photos = reader.m_Photos;
}


void SolverVertical::Solve() {

    std::sort(m_Photos.begin(), m_Photos.end(), [](Photo& a, Photo& b) {
        return a.tags.size() > b.tags.size();
    });


    volatile int k = 10;
}



