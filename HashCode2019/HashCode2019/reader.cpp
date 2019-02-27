#include "reader.h"
#include <fstream>

void DataReader::Read(Params& params)
{
    std::fstream filestream;
    filestream.open(m_FileName, std::fstream::in);

    filestream >> params.R >> params.C >> params.L >> params.H;

    m_Pizza.resize(params.R);
    for (int i = 0; i < params.R; ++i) {
        m_Pizza[i].resize(params.C);
    }

    for (int i = 0; i < params.R; ++i) {
        for (int j = 0; j < params.C; ++j) {
            filestream >> m_Pizza[i][j].type;
        }
    }

    filestream.close();
}