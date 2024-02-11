#include "../include/zobrist.h"

u64 chess::zobrist::zobrist_keys[12][64];
u64 chess::zobrist::zobrist_keys_u8[8];

void chess::zobrist::init_zobrist_keys()
{
    srand(time(NULL));
    for(u8 i = 0; i < 12; ++i)
        for(u8 j = 0; j < 64; ++j)
            chess::zobrist::zobrist_keys[i][j] = (((u64)rand() << 32) | (u64)rand());
    for(u8 i = 0; i < 8; ++i)
        chess::zobrist::zobrist_keys_u8[i] = (((u64)rand() << 32) | (u64)rand());
}