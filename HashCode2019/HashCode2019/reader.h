#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <cassert>
#include <algorithm>

struct Params
{
    int N = 0;
};

struct Piece
{
    Piece() : eaten(false) {}
    bool eaten;
    char type;
};

class TagsSet
{
public:
    TagsSet() = default;

    void add(uint64_t tag)
    {
        assert(tags_num < MAX_TAGS);
        tags[tags_num++] = tag;
    }

    void sort()
    {
        std::sort(tags, tags + tags_num);
    }

    uint8_t size()
    { 
        return tags_num;
    }

    TagsSet intersection(const TagsSet& rhs) const
    {
        TagsSet result;
        auto end = std::set_intersection(tags, tags + tags_num, rhs.tags, rhs.tags + rhs.tags_num, result.tags);
        assert(end - result.tags < MAX_TAGS);
        result.tags_num = uint8_t(end - result.tags);
        return result;
    }

    TagsSet difference(const TagsSet& rhs) const
    {
        TagsSet result;
        auto end = std::set_difference(tags, tags + tags_num, rhs.tags, rhs.tags + rhs.tags_num, result.tags);
        assert(end - result.tags < MAX_TAGS);
        result.tags_num = uint8_t(end - result.tags);
        return result;
    }

public:
    static const int MAX_TAGS = 20;
    uint64_t tags[MAX_TAGS] = { 0 };
    uint8_t tags_num = 0;
};

struct Photo
{
    TagsSet tags;
    bool vertical = false;
};

struct Output{
    bool vertical;
    int pic_ind1;
    int pic_ind2;
};

uint64_t StringToUint64(std::string&& str);

class DataReader
{
public:
    explicit DataReader(std::string file_name) : m_FileName(file_name) {}
    void Read(Params& params);

public:
    std::string m_FileName;
    std::vector<Photo> m_Photos;
};