#include "reader.h"
#include <fstream>
#include <algorithm>

using namespace std;

void DataReader::Read(Params& params)
{
    std::fstream filestream;
    filestream.open(m_FileName, std::fstream::in);

    filestream >> params.N;

    m_Photos.resize(params.N);

    for (int i = 0; i < params.N; ++i)
    {
        char orientation;
        int tags_num;
        filestream >> orientation >> tags_num;

        m_Photos[i].idx = i;
        m_Photos[i].vertical = (orientation == 'V');

        for (int t = 0; t < tags_num; ++t)
        {
            std::string tag;
            filestream >> tag;

            m_Photos[i].tags.add(StringToUint64(std::move(tag)));
        }
        m_Photos[i].tags.sort();
    }

    filestream.close();
}

int DataReader::GetScore(const Slide& slide1, const Slide& slide2)
{
    int intersection = slide1.tags.intersection(slide2.tags).size();
    int cond1 = intersection;
    int cond2 = slide1.tags.size() - intersection;
    int cond3 = slide2.tags.size() - intersection;

    return std::min(cond1, std::min(cond2, cond3));
}

int DataReader::GetScore(const TagsSet & set1, const TagsSet & set2)
{
    int intersection = set1.intersection(set2).size();
    int cond1 = intersection;
    int cond2 = set1.size() - intersection;
    int cond3 = set2.size() - intersection;

    return std::min(cond1, std::min(cond2, cond3));
}

uint64_t StringToUint64(std::string&& str)
{
    uint64_t val = 0;

    assert(str.size() <= 10);
    for (size_t i = 0; i < str.size(); ++i)
    {
        uint64_t c;
        if (str[i] >= '0' && str[i] <= '9')
        {
            c = str[i] - '0';
        }
        else
        {
            assert(str[i] >= 'a' && str[i] <= 'z');
            c = 10 + str[i] - 'a';
        }
            
        assert(c <= (1 << 6));
        val |= c << (6 * i);
    }

    return val;
}
