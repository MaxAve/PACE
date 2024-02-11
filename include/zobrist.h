#pragma once

#include <iostream>
#include "types.h"

namespace chess
{
    namespace zobrist
    {
        extern u64 zobrist_keys[12][64];
        extern u64 zobrist_keys_u8[8];

        /**
         * @brief Initializes zobrist keys used to generate Zobrist hashes
         * @warning The random nunmber generation is implemented with (rand() | (rand() << 32)) 
         * which is extremely insecure and results in unexpected behaviour at higher depths! This 
         * should be changed to a more secure implementation like std::mt19937_64 in the next update
        */
        void init_zobrist_keys();
    }
}