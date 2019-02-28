#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "reader.h"
#include "solver.h"
#include "basicoptimizer.h"

using namespace std;




int main(int argc, char *argv[])
{
    string file(argv[1]);
    string file_out(argv[2]);
    Params params; // R, C, L, H

    DataReader data_reader(file);
    data_reader.Read(params);

    ISolver* solver = new Solver(params, data_reader);
    solver->Solve();
    auto result = solver->GetResult();

    fstream out(file_out, std::fstream::out);
    for (auto elem : result) {
        out << elem.pic_ind1;
        if (elem.vertical)
            out << " " << elem.pic_ind2;
        out << std::endl;
    }
    out.close();

    delete solver;

    return 0;
}