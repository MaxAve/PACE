#include "../include/eval.h"

int chess::eval::count_material(const board::Board &b)
{
    int eval = 0;
    for(u8 i = 0; i < 12; ++i)
    {
        for(u8 j = 0; j < 64; ++j)
        {
            eval += (bool)(b.bitboards[i] & (1ULL << j)) * chess::eval::piece_values[i];
        }
    }
    return eval;
}
