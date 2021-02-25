#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <algorithm>
#include <memory>
#include <list>
#include <tuple>
#include <cmath>
#include <map>
#include <set>
#include <unordered_map>
#include <iostream>
#include <string>
#include <math.h>    
#include <vector>
#include "Common.h"

using namespace std;

struct Schedule
{
    vector<pair<int, int>> schedule;
};


struct Intersection
{
    int id;
    unordered_map<int, Street> in_streets;
    unordered_map<int, Street> out_streets;
    Schedule schedule;

    void Schedule();
};
