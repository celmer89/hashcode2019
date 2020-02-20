#pragma once

#include<iostream>
#include<vector>
#include<list>
#include<cassert>
#include <algorithm>
#include <memory>
#include <tuple>
#include <cmath>
#include <map>
#include <set>
#include <unordered_map>
#include <iostream>
#include <string>
#include <math.h>    

using namespace std;


extern unsigned long long B, L, D;

extern vector<unsigned long long> BOOKS;
extern vector<int> BOOKS_COUNT;

struct Library
{
    unsigned long long N; //number of books in library
    unsigned long long T; // singup process time
    unsigned long long M; // books per day
    vector<unsigned long long> books;

    bool is_commited = false;
    double score = 0;
};

extern vector<Library> LIBRARIES;
