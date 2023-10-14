#include "../include/eval.h"

int chess::eval::eval_pst(const board::Board &b)
{
    int eval = 0;
    for(u8 i = 0; i < 6; ++i)
    {
        for(u8 j = 0; j < 64; ++j)
        {
            if(b.bitboards[i] & (1ULL << j))
            {
                eval -= piece_square_tables[i][j];
            }
        }
    }
    for(u8 i = 6; i < 12; ++i)
    {
        for(u8 j = 0; j < 64; ++j)
        {
            if(b.bitboards[i] & (1ULL << j))
            {
                eval += piece_square_tables[i-6][63-j];
            }
        }
    }
    return eval;
}
