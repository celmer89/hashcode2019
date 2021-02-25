
#include "Intersection.h"


void Intersection::Schedule()
{
	vector<Street*> streets;

	for (auto& str : in_streets)
	{
		if (str.second.num_cars_global > 0)
		{
			streets.push_back(&str.second);
		}
	}

	sort(streets.begin(), streets.end(), [](const auto& a, const auto& b)
	{
		return a->num_cars_global > b->num_cars_global;
	});

	int min_num_cars = streets.back()->num_cars_global;

	for (auto& str : streets)
	{
		int timebox = str->num_cars_global / min_num_cars + 0.5f;
		schedule.schedule.push_back(make_pair(str->id, timebox));
	}
}