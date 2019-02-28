#include "TheBestSolver.h"
#include "solverVertical.h"

TheBestSolver::TheBestSolver(Params params, const DataReader& reader)
    : Solver(params, reader)
{
    SolverVertical solver(params, reader);
    slides = solver.GetSolution1();

    //photos = reader.m_Photos;
}

void TheBestSolver::Solve()
{
    std::sort(slides.begin(), slides.end(), [](const Slide& lhs, const Slide& rhs) { return lhs.tags.size() > rhs.tags.size(); });

    int used_photos = 0;
    int64_t total_score = 0;

    std::vector<bool> used;
    used.resize(slides.size(), false);

    int percent = -1;

    int i = 0;

    Output out;
    out.vertical = slides[i].vertical;
    out.pic_ind1 = slides[i].pic_ind1;
    out.pic_ind2 = slides[i].pic_ind2;

    while (used_photos < slides.size())
    {
        int new_percent = (used_photos * 100 / slides.size());
        if (new_percent > percent)
        {
            fprintf(stderr, "%d%%\n", new_percent);
            percent = new_percent;
        }

        int max_score = -1;
        int max_j = -1;

        for (int j = 0; j < slides.size(); ++j)
        {
            if (i == j || used[j])
                continue;

            int score_est = std::min(slides[i].tags.size(), slides[j].tags.size()) / 2;
            if (score_est > max_score)
            {
                int score = DataReader::GetScore(slides[i].tags, slides[j].tags);
                if (score > max_score)
                {
                    max_j = j;
                    max_score = score;
                }
            }
        }

        if (max_j != -1)
        {
            used[i] = true;
            i = max_j;

            total_score += max_score;

            Output out;
            out.vertical = slides[i].vertical;
            out.pic_ind1 = slides[i].pic_ind1;
            out.pic_ind2 = slides[i].pic_ind2;

            m_Solution.emplace_back(out);

            ++used_photos;
        }
        else
        {
            break;
        }
    }

    fprintf(stderr, "Total score: %lld\n", total_score);

}
