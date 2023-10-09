#pragma once

#include "board.h"

namespace chess
{
    namespace eval
    {
        const int piece_values[] = {-100, -300, -300, -500, -900, -1000000000, 100, 300, 300, 500, 900, 1000000000};

        /* Counts up material on both sides */
        int count_material(const board::Board &b);
    }
}
