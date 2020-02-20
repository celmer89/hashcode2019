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


unsigned long long B, L, D;

vector<unsigned long long> BOOKS;

struct Library
{
	unsigned long long N; //number of books in library
	unsigned long long T; // singup process time
	unsigned long long M; // books per day
	vector<unsigned long long> books;

    bool is_commited = false;
    int score = 0;
};

vector<Library> LIBRARIES;


int CalculateLibraryScore(int library_idx, int days)
{
    return 0;
}

int main()
{
	cin >> B >> L >> D;

	// BOOKS
	BOOKS.reserve(B);

	for (unsigned long long i = 0; i < B; ++i)
	{
		unsigned long long book;
		cin >> book;
		BOOKS.push_back(book);
	}


	//LIBRARIES
	LIBRARIES.reserve(L);

	for (unsigned long long i = 0; i < L; ++i)
	{
		Library library; 
		cin >> library.N >> library.T >> library.M;


		library.books.reserve(library.N);


		for (unsigned long long j = 0; j < library.N; ++j)
		{
			unsigned long long book;
			cin >> book;
			library.books.push_back(book);
		}


		LIBRARIES.push_back(std::move(library));
	}


    vector<int> remaining_libraries;
    int days_left = D;
    unsigned long long total_score = 0;

    for (int commited_libraries = 0; commited_libraries < LIBRARIES.size(); ++commited_libraries)
    {
        // Sort books in each library.
        for (int lib = 0; lib < LIBRARIES.size(); ++lib)
        {
            if (!LIBRARIES[lib].is_commited)
            {
                auto& books = LIBRARIES[lib].books;
                std::sort(books.begin(), books.end(), [&](auto lhs, auto rhs) { return BOOKS[lhs] > BOOKS[rhs]; });
            }
        }

        // Calculate score for each library.
        remaining_libraries.clear();
        remaining_libraries.reserve(LIBRARIES.size() - commited_libraries);

        for (int lib = 0; lib < LIBRARIES.size(); ++lib)
        {
            if (!LIBRARIES[lib].is_commited)
            {
                LIBRARIES[lib].score = CalculateLibraryScore(lib, days_left);
                remaining_libraries.emplace_back(lib);
            }
        }

        // Choose library with the highest score.
        int chosen_one = *std::max_element(remaining_libraries.begin(), remaining_libraries.end(), [&](int lhs, int rhs) { return LIBRARIES[lhs].score < LIBRARIES[rhs].score; });



    }


	return 0;
}
