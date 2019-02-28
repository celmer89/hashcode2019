#include "basicoptimizer.h"
#include "reader.h"
#include <ctime>
#include <iostream>

using namespace std;

BasicOptimizer::BasicOptimizer(DataReader* reader, SOptimizerParams& optimizer_params)
{
    m_DataReaderPtr = reader;
    m_OptimizerParams = optimizer_params;
    srand(time(NULL));
}

size_t GetRandomInt(size_t min, size_t max) // [min, max)
{
    return min + rand() % ((max + 1) - min);
}

int BasicOptimizer::CalculateTrioScore(const std::vector<Photo>& photos, const std::vector<Output>& result, size_t index)
{
    int score = 0;
    if (index > 0)
    {
        score += m_DataReaderPtr->GetScore(photos[result[index].pic_ind1].tags, photos[result[index - 1].pic_ind1].tags);
    }
    if (index < result.size() - 1)
    {
        score += m_DataReaderPtr->GetScore(photos[result[index].pic_ind1].tags, photos[result[index + 1].pic_ind1].tags);
    }
    return score;
}

void BasicOptimizer::TrySwap(const std::vector<Photo>& photos, std::vector<Output>& result, size_t first_index, size_t second_index, bool& succ)
{
    // for now try to change only first image
    int current_score = CalculateTrioScore(photos, result, first_index) + CalculateTrioScore(photos, result, second_index);

    int native_first_pic1 = result[first_index].pic_ind1;
    int native_second_pic1 = result[second_index].pic_ind1;

    // try to swap
    result[first_index].pic_ind1 = native_second_pic1;
    result[second_index].pic_ind1 = native_first_pic1;
    int new_score = CalculateTrioScore(photos, result, first_index) + CalculateTrioScore(photos, result, second_index);

    // revert swap
    if (new_score > current_score)
    {
        // accept swap
        succ = true;
    }
    else
    {
        result[first_index].pic_ind1 = native_first_pic1;
        result[second_index].pic_ind1 = native_second_pic1;
    }
}

void BasicOptimizer::Optimize(std::vector<Output>& result)
{
    std::vector<Photo> photos = m_DataReaderPtr->m_Photos;

    bool succ = false;
    int succ_size = 0;
    for (size_t i = 0; i < m_OptimizerParams.iterations; ++i)
    {
        succ = false;
        size_t first_index = GetRandomInt(0, result.size() - 1);
        size_t second_index = first_index + 1;
        //size_t second_index = GetRandomInt(first_index + 1, result.size());

        TrySwap(photos, result, first_index, second_index, succ);

        if (succ)
            succ_size++;
    }
    std::cout << "Result: " << succ_size << std::endl;
}