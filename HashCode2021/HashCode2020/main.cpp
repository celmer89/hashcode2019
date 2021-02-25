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

#include "Common.h"
#include "Intersection.h"


Input in;
vector<Intersection> Intersections;

void PrepareData();

int main()
{

	ReadInput(in);
	PrepareData();


	return 0;
}


void PrepareData()
{
	Intersections.resize(in.isection_count);

	for (int i = 0; i < Intersections.size(); ++i)
	{
		Intersections[i].id = i;
	}

	for (int i = 0; i < in.streets.size(); ++i)
	{
		auto& street = in.streets[i];
		auto& out_streets = Intersections[street.begin_id].out_streets;
		auto& in_streets = Intersections[street.end_id].in_streets;
		
		in_streets[i] = street;
		out_streets[i] = street;

	}





}