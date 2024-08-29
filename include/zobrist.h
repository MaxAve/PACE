#pragma once

#include <iostream>
#include <ctime>
#include <random>
#include "types.h"

namespace chess
{
    namespace zobrist
    {
        extern u64 zobrist_keys[12][64];
        extern u64 zobrist_keys_u8[8];

        /**
         * @brief Initializes zobrist keys used to generate Zobrist hashes
        */
        void init_zobrist_keys();
    }
}