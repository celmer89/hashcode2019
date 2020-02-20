#pragma once

#include "Common.h"

double CalculateLibraryScore(int library_idx, int days)
{
    return LIBRARIES[library_idx].books.size();
}
