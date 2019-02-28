#pragma once
#include "reader.h"

struct SOptimizerParams
{
    size_t iterations;
};

class IOptimizer
{
public:
    virtual ~IOptimizer() {}

    virtual void Optimize(std::vector<Output>& result) = 0;

protected:
    SOptimizerParams m_OptimizerParams;
};