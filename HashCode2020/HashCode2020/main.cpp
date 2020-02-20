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
};

vector<Library> LIBRARIES;

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



	return 0;
}
