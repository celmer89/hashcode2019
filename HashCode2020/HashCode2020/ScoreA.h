#pragma once

#include "Common.h"

int CalculateLibraryScore(int library_idx, int days)
{
    return LIBRARIES[library_idx].books.size();
}
