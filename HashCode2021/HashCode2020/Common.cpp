#include "Common.h"
#include "Intersection.h"

#include <iostream>

extern Input in;
extern vector<Intersection> Intersections;

void ReadInput(Input& in)
{
    std::cin >> in.sim_time;
    std::cin >> in.isection_count;

    int street_count = 0;
    std::cin >> street_count;
    in.streets.reserve(street_count);

    int car_count = 0;
    std::cin >> car_count;
    in.cars.reserve(car_count);

    std::cin >> in.reach_bonus;

    for (int i = 0; i < street_count; ++i)
    {
        in.streets.emplace_back();
        Street& s = in.streets.back();

        std::cin >> s.begin_id;
        std::cin >> s.end_id;
        std::cin >> s.name;
        std::cin >> s.length;
    }

    for (int i = 0; i < car_count; ++i)
    {
        in.cars.emplace_back();
        Car& c = in.cars.back();

        int path_street_count = 0;
        std::cin >> path_street_count;
        c.streets_ids.reserve(path_street_count);

        for (int j = 0; j < path_street_count; ++j)
        {
            std::string street_name;
            std::cin >> street_name;

            auto it = std::find_if(begin(in.streets), end(in.streets), [&street_name](const Street& s)
            {
                return s.name == street_name;
            });

            ++(it->num_cars_global);

            assert(it != in.streets.cend());

            int idx = it - in.streets.cbegin();

            c.streets_ids.emplace_back(idx);
        }
    }
}

void WriteOutput()
{
    static bool TEST_DATA = false;
    if (TEST_DATA)
    {
        Intersections.clear();
        {
            Intersections.emplace_back();
            Intersection& i = Intersections.back();
            i.schedule.schedule.emplace_back(0, 1);
            i.schedule.schedule.emplace_back(1, 2);
        }
        {
            Intersections.emplace_back();
            Intersection& i = Intersections.back();
            i.schedule.schedule.emplace_back(0, 1);
            i.schedule.schedule.emplace_back(1, 2);
        }
    }

    std::cout << Intersections.size() << '\n';
    for (int i = 0; i < Intersections.size(); ++i)
    {
        std::cout << i << '\n';
        const Intersection& isection = Intersections[i];

        std::cout << isection.schedule.schedule.size() << '\n';
        for (int j = 0; j < isection.schedule.schedule.size(); ++j)
        {
            const std::pair<int, int>& pair = isection.schedule.schedule[j];

            std::cout << in.streets[pair.first].name << ' ' << pair.second << '\n';
        }
    }
}