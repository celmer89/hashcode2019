#pragma once
#include <string>
#include <vector>

struct Params
{
    int R, C, L, H;
};

struct Piece
{
    Piece() : eaten(false) {}
    bool eaten;
    char type;
};

struct Output{
    int param;
};

class DataReader
{
    public:
        explicit DataReader(std::string file_name) : m_FileName(file_name) {}
        void Read(Params& params);
        
        std::vector<std::vector<Piece> > GetPizza() const { return m_Pizza; }

    private:
        std::string m_FileName;
        std::vector<std::vector<Piece> > m_Pizza;
};