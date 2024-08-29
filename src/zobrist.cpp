#include "../include/zobrist.h"

u64 chess::zobrist::zobrist_keys[12][64];
u64 chess::zobrist::zobrist_keys_u8[8];

void chess::zobrist::init_zobrist_keys()
{
    std::mt19937_64 mt(time(nullptr));
    for(u8 i = 0; i < 12; ++i)
        for(u8 j = 0; j < 64; ++j)
            chess::zobrist::zobrist_keys[i][j] = mt();
    for(u8 i = 0; i < 8; ++i)
        chess::zobrist::zobrist_keys_u8[i] = mt();
}