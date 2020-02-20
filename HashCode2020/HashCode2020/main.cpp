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
#include "ScoreA.h"

unsigned long long B, L, D;
vector<unsigned long long> BOOKS;
vector<Library> LIBRARIES;

struct OutLibrary
{
	int id = 0;
	vector<unsigned long long> books;
};

vector<OutLibrary> OUT_LIBRARIES;


void WriteOutput()
{
	cout << OUT_LIBRARIES.size() << endl;

	for (unsigned long long i = 0; i < OUT_LIBRARIES.size(); ++i)
	{
		cout << OUT_LIBRARIES[i].id << " ";
		cout << OUT_LIBRARIES[i].books.size() << endl;

		for (unsigned long long j = 0; j < OUT_LIBRARIES[i].books.size(); ++j)
		{
			cout << OUT_LIBRARIES[i].books[j] << " ";
		}
		cout << endl;
	}
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

    for (int commited_libraries = 0; commited_libraries < LIBRARIES.size() && days_left > 0; ++commited_libraries)
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

        OUT_LIBRARIES.emplace_back(OutLibrary{ chosen_one, LIBRARIES[chosen_one].books });

        auto& l = LIBRARIES[chosen_one];
        l.is_commited = true;
        int book_idx = 0;
        for (int d = 0; d < (days_left - l.T) * l.M && book_idx < l.books.size(); ++d)
        {
            total_score += BOOKS[l.books[book_idx]];
            BOOKS[l.books[book_idx]] = 0;
            book_idx++;
        }

        days_left -= l.T;


        int prev_percent_completed = commited_libraries * 100 / LIBRARIES.size();
        int percent_completed = (commited_libraries + 1) * 100 / LIBRARIES.size();
        if (prev_percent_completed != percent_completed)
        {
            cerr << percent_completed << "%" << endl;
        }
    }

	WriteOutput();

    cerr << "Total score: " << total_score << endl;

	return 0;
}
