#pragma once

#include "Common.h"

double CalculateLibraryScore(int library_idx, int days)
{
    float score = 0;
    auto& l = LIBRARIES[library_idx];

    int book_idx = 0;
    for (int d = 0; d < (days - l.T) * l.M && book_idx < l.books.size(); ++d)
    {
        score += BOOKS[l.books[book_idx]];
        book_idx++;
    }

    return score;
}
