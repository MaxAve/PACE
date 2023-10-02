#include <moves.h>

bool get_piece_color(Board b, u8 square)
{
    for(int i = 0; i < 6; ++i)
    {
        if(b.bitboards[i] & (1ULL << square))
        {
            return BLACK;
        }
    }
    return WHITE;
}

u8 get_piece_type(Board b, u8 square)
{
    for(u8 i = 0; i < 12; ++i)
    {
        if(b.bitboards[i] & (1ULL << square))
        {
            return i;
        }
    }
    return EMPTY_SQUARE;
}

//TODO use bitboards instead of get_piece_color
u64 get_attack_bitboard(Board b, u8 square, u8 piece_type, u64 enemy_bb, u64 friendly_bb)
{
    u64 attack_bb = 0ULL;
    switch(piece_type)
    {
        // Black pawn
        case PB:
        attack_bb |= (1ULL << (square-8));
        if(square < 58 && square > 47 && !((enemy_bb | friendly_bb) & (1ULL << square-8)))
            attack_bb |= (1ULL << (square-16));
        attack_bb &= ~(enemy_bb | friendly_bb);
        attack_bb |= (((1ULL << (square-7)) | (1ULL << (square-9))) & enemy_bb);
        break;

        // White pawn
        case PW:
        attack_bb |= (1ULL << (square+8));
        if(square < 16 && square > 7 && !((enemy_bb | friendly_bb) & (1ULL << square+8)))
            attack_bb |= (1ULL << (square+16));
        attack_bb &= ~(enemy_bb | friendly_bb);
        attack_bb |= (((1ULL << (square+7)) | (1ULL << (square+9))) & enemy_bb);
        break;
    }
    return attack_bb;
}
