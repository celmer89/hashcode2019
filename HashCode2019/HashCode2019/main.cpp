#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream> 

using namespace std;

struct Piece
{
    Piece() : eaten(false) {}
    bool eaten;
    char type;
};

struct Slice
{
    int x1, x2;
    int y1, y2;
};

int R, C, L, H;
vector<vector<Piece> > Pizza;

void ReadData(string file) {

    fstream filestream;
    filestream.open(file, std::fstream::in);

    filestream >> R >> C >> L >> H;

    Pizza.resize(R);
    for (int i = 0; i < R; ++i) {
        Pizza[i].resize(C);
    }

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            filestream >> Pizza[i][j].type;
        }

    }

    filestream.close();
}


void Solve()
{


    // TO DO
}


int main(int argc, char *argv[])
{
    string file(argv[1]);
    ReadData(file);
    Solve();

    return 0;
}