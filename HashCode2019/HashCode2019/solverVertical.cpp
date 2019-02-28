#include "SolverVertical.h"
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

SolverVertical::SolverVertical(Params params, const DataReader& reader)
{
    m_Params = params;
    m_Photos = reader.m_Photos;
}


void  SolverVertical::Sort() {
    std::sort(m_Photos.begin(), m_Photos.end(), [](Photo& a, Photo& b) {
        return a.tags.size() > b.tags.size();
    });
}

void SolverVertical::Solve() {

    
    GetSolution1();
    GetSolution2();
    GetSolution3();
}


vector<Slide> SolverVertical::GetSolution1()
{
    Sort();
    vector<Slide> out;

    out.reserve(m_Photos.size() / 2);
    for (int i = 0; i < m_Photos.size() / 2; ++i) {

        Slide s;
        s.pic_ind1 = m_Photos[i].idx;
        s.pic_ind2 = m_Photos[m_Photos.size() - i-1].idx;
        s.tags = m_Photos[i].tags.get_union(m_Photos[m_Photos.size() - i-1].tags);
        s.vertical = true;

        out.push_back(s);
    }
    return out;
}


vector<Slide> SolverVertical::GetSolution2()
{
    Sort();
    vector<Slide> out;

    out.reserve(m_Photos.size() / 2);
    for (int i = 0; i < m_Photos.size(); i = i +2) {

        Slide s;
        s.pic_ind1 = m_Photos[i].idx;
        s.pic_ind2 = m_Photos[i+1].idx;
        s.tags = m_Photos[i].tags.get_union(m_Photos[i+1].tags);
        s.vertical = true;

        out.push_back(s);
    }
    return out;
}

vector<Slide> SolverVertical::GetSolution3()
{
    vector<Slide> out;

    out.reserve(m_Photos.size() / 2);
    for (int i = 0; i < m_Photos.size(); i = i + 2) {

        Slide s;
        s.pic_ind1 = m_Photos[i].idx;
        s.pic_ind2 = m_Photos[i + 1].idx;
        s.tags = m_Photos[i].tags.get_union(m_Photos[i + 1].tags);
        s.vertical = true;

        out.push_back(s);
    }
    return out;
}


