#include "../include/moves.h"

bool chess::moves::get_piece_color(chess::board::Board b, u8 square)
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

u8 chess::moves::get_piece_type(chess::board::Board b, u8 square)
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

u64 chess::moves::get_attack_bitboard(chess::board::Board b, u8 square, u8 piece_type, u64 white_pieces_bb, u64 black_pieces_bb)
{
    u64 attack_bb = 0ULL;
    switch(piece_type)
    {
        // Black pawn
        case PB:
        attack_bb |= (1ULL << (square-8));
        if(square < 58 && square > 47 && !((white_pieces_bb | black_pieces_bb) & (1ULL << square-8)))
            attack_bb |= (1ULL << (square-16));
        attack_bb &= ~(white_pieces_bb | black_pieces_bb);
        attack_bb |= (((1ULL << (square-7)) | (1ULL << (square-9))) & white_pieces_bb);
        break;

        // White pawn
        case PW:
        attack_bb |= (1ULL << (square+8));
        if(square < 16 && square > 7 && !((white_pieces_bb | black_pieces_bb) & (1ULL << square+8)))
            attack_bb |= (1ULL << (square+16));
        attack_bb &= ~(white_pieces_bb | black_pieces_bb);
        attack_bb |= (((1ULL << (square+7)) | (1ULL << (square+9))) & black_pieces_bb);
        break;

        // Black knight
        case NB:
        if((square % 8) < 7)
        {
            if (square < 48) attack_bb |= (1ULL << (square + 17));
            if (square > 15) attack_bb |= (1ULL << (square - 15));
            if((square % 8) < 6)
            {
                if (square < 56) attack_bb |= (1ULL << (square + 10));
                if (square > 7) attack_bb |= (1ULL << (square - 6));
            }
        }
        if((square % 8) > 0)
        {
            if (square < 48) attack_bb |= (1ULL << (square + 15));
            if (square > 15) attack_bb |= (1ULL << (square - 17));
            if((square % 8) > 1)
            {
                if (square < 56) attack_bb |= (1ULL << (square + 6));
                if (square > 7) attack_bb |= (1ULL << (square - 10));
            }
        }
        attack_bb &= ~black_pieces_bb;
        break;

        // White knight
        case NW:
        if((square % 8) < 7)
        {
            if (square < 48) attack_bb |= (1ULL << (square + 17));
            if (square > 15) attack_bb |= (1ULL << (square - 15));
            if((square % 8) < 6)
            {
                if (square < 56) attack_bb |= (1ULL << (square + 10));
                if (square > 7) attack_bb |= (1ULL << (square - 6));
            }
        }
        if((square % 8) > 0)
        {
            if (square < 48) attack_bb |= (1ULL << (square + 15));
            if (square > 15) attack_bb |= (1ULL << (square - 17));
            if((square % 8) > 1)
            {
                if (square < 56) attack_bb |= (1ULL << (square + 6));
                if (square > 7) attack_bb |= (1ULL << (square - 10));
            }
        }
        attack_bb &= ~white_pieces_bb;
        break;
    }
    return attack_bb;
}
