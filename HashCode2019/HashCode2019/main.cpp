#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "reader.h"
#include "solver.h"

using namespace std;

int main(int argc, char *argv[])
{
    string file(argv[1]);
    Params params; // R, C, L, H

    DataReader data_reader(file);
    data_reader.Read(params);

    ISolver* solver = new Solver(params, data_reader);
    solver->Solve();
    solver->GetResult();
    delete solver;

    return 0;
}