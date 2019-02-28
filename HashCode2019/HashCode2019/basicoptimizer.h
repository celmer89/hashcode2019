#pragma once

#include "ioptimizer.h"

class BasicOptimizer : IOptimizer
{
public:
    BasicOptimizer(DataReader* reader, SOptimizerParams& optimizer_params);

    void Optimize(std::vector<Output>& result) override;

private:
    DataReader* m_DataReaderPtr;

    int CalculateTrioScore(const std::vector<Photo>& photos, const std::vector<Output>& result, size_t index);
    void TrySwap(const std::vector<Photo>& photos, std::vector<Output>& result, size_t first_index, size_t second_index);
};