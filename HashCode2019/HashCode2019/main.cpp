#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int R, C, L, H;
vector<vector<char> > Pizza;


void ReadData() {

    cin >> R >> C >> L >> H;

    Pizza.resize(R);
    for (int i = 0; i < R; ++i) {
        Pizza[i].resize(C);
    }

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cin >> Pizza[i][j];
        }

    }
}


void Solve()
{

    // TO DO
}


int main()
{
    ReadData();
    Solve();

    return 0;
}