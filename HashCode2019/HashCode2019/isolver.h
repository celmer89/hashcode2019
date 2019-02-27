#pragma once

class ISolver
{
    public:
    virtual ~ISolver() {};

    virtual void Solve() = 0;
    virtual void GetResult() = 0;
};