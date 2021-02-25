#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <cassert>
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
#include <vector>

using namespace std;

struct Street
{
    std::string name;
    int begin_id = 0;
    int end_id = 0;
    int length = 0;
    int num_cars_global = 0;
};

struct Car
{
    std::vector<int> streets_ids;

    int current_idx = 0;
};

struct Input
{
    int sim_time = 0;
    int isection_count = 0;
    int reach_bonus = 0;

    std::vector<Street> streets;
    std::vector<Car> cars;
};

void ReadInput(Input& in);

void WriteOutput();
