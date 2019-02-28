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
    std::vector<Photo> horizontals;
    std::vector<Photo> verticals;

    SortOutData(m_Photos, horizontals, verticals);

    GetSolution1(verticals);
    GetSolution2(verticals);
    GetSolution3(verticals);


}

void SolverVertical::SortOutData(const std::vector<Photo>& in, std::vector<Photo>& outHor, std::vector<Photo> &outVer)
{
    outVer.reserve(in.size() / 2);
    outVer.reserve(in.size() / 2);


    for (int i = 0; i < in.size(); ++i) {

        if (in[i].vertical) {
            outVer.push_back(in[i]);
        }
        else {
            outHor.push_back(in[i]);
        }
    }
}


vector<Slide> SolverVertical::GetSolution1(std::vector<Photo>& photos)
{
    Sort();
    vector<Slide> out;

    out.reserve(photos.size() / 2);
    for (int i = 0; i < photos.size() / 2; ++i) {

        Slide s;
        s.pic_ind1 = photos[i].idx;
        s.pic_ind2 = photos[photos.size() - i-1].idx;
        s.tags = photos[i].tags.get_union(photos[photos.size() - i-1].tags);
        s.vertical = true;

        out.push_back(s);
    }
    return out;
}


vector<Slide> SolverVertical::GetSolution2(std::vector<Photo>& photos)
{
    Sort();
    vector<Slide> out;

    out.reserve(photos.size() / 2);
    for (int i = 0; i < photos.size(); i = i +2) {

        Slide s;
        s.pic_ind1 = photos[i].idx;
        s.pic_ind2 = photos[i+1].idx;
        s.tags = photos[i].tags.get_union(photos[i+1].tags);
        s.vertical = true;

        out.push_back(s);
    }
    return out;
}

vector<Slide> SolverVertical::GetSolution3(std::vector<Photo>& photos)
{
    vector<Slide> out;

    out.reserve(photos.size() / 2);
    for (int i = 0; i < photos.size(); i = i + 2) {

        Slide s;
        s.pic_ind1 = photos[i].idx;
        s.pic_ind2 = photos[i + 1].idx;
        s.tags = photos[i].tags.get_union(photos[i + 1].tags);
        s.vertical = true;

        out.push_back(s);
    }
    return out;
}


