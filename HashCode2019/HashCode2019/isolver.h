#pragma once
#include "reader.h"

class ISolver
{
    public:
    virtual ~ISolver() {};

    virtual void Solve() = 0;
    virtual  std::vector<Output> GetResult() = 0;
};