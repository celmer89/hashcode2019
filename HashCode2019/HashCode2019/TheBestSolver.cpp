#include "TheBestSolver.h"


TheBestSolver::TheBestSolver(Params params, const DataReader& reader)
    : Solver(params, reader)
{
    photos = reader.m_Photos;
}

void TheBestSolver::Solve()
{
    std::sort(photos.begin(), photos.end(), [](const Photo& lhs, const Photo& rhs) { return lhs.tags.size() > rhs.tags.size(); });

    int used_photos = 0;
    int total_score = 0;

    int i = 0;
    while (used_photos < photos.size())
    {
        int max_score = -1;
        int max_j = -1;

        for (int j = 0; j < photos.size(); ++j)
        {
            if (i == j || photos[j].used)
                continue;

            int score_est = std::min(photos[i].tags.size(), photos[j].tags.size()) / 2;
            if (score_est > max_score)
            {
                int score = DataReader::GetScore(photos[i].tags, photos[j].tags);
                if (score > max_score)
                {
                    max_j = j;
                    max_score = score;
                }
            }
        }

        if (max_j != -1)
        {
            photos[i].used = true;
            i = max_j;

            total_score += max_score;

            Output out;
            out.vertical = false;
            out.pic_ind1 = photos[i].idx;
            out.pic_ind2 = photos[max_j].idx;

            m_Solution.emplace_back(out);

            ++used_photos;
        }
        else
        {
            break;
        }
    }

}
