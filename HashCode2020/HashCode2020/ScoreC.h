#pragma once

#include "Common.h"

double CalculateLibraryScore(int library_idx, int days_left)
{
	float score = 0;
    float uniqueness = 0;

	auto& l = LIBRARIES[library_idx];

    if (l.T >= days_left)
        return -1;

	int book_idx = 0;
    int nonzero_books = 0;
	for (int d = 0; d < (days_left - l.T) * l.M && book_idx < l.books.size(); ++d)
	{
        int book_id = l.books[book_idx];

        if (BOOKS[book_id] > 0)
        {
            ++nonzero_books;
            uniqueness += BOOKS_COUNT[book_id];
        }

		score += BOOKS[book_id];
		book_idx++;
	}

    uniqueness /= nonzero_books;
    uniqueness = 1.0 / uniqueness;

    float a = 5.0, b = 1.0;
	return (a * score) / (b * LIBRARIES[library_idx].T * uniqueness);
}
