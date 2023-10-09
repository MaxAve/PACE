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

// TODO this needs optimization if possible
u64 chess::moves::get_attack_bitboard(const chess::board::Board &b, u8 square, u8 piece_type, u64 white_pieces_bb, u64 black_pieces_bb, u64 all_pieces_bb)
{
    u64 attack_bb = 0ULL;
    switch(piece_type)
    {
        // Black pawn
        case PB:
        attack_bb |= (1ULL << (square-8));
        if(square < 58 && square > 47 && !(all_pieces_bb & (1ULL << square-8)))
            attack_bb |= (1ULL << (square-16));
        attack_bb &= ~all_pieces_bb;
        attack_bb |= (((1ULL << (square-7)) | (1ULL << (square-9))) & white_pieces_bb);
        break;

        // White pawn
        case PW:
        attack_bb |= (1ULL << (square+8));
        if(square < 16 && square > 7 && !(all_pieces_bb & (1ULL << square+8)))
            attack_bb |= (1ULL << (square+16));
        attack_bb &= ~all_pieces_bb;
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

        // Black bishop (from white's POV)
        case BB:
        // North-west
        if((square % 8) != 7 && square < 56) {
            for(u8 i = square+9; i < 64; i += 9) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i) || (i % 8) == 7 || i > 55)
                    break;
            }
        }
        // North-east (from white's POV)
        if((square % 8) != 0 && square < 56) {
            for(u8 i = square+7; i < 63; i += 7) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i) || (i % 8) == 0 || i > 55)
                    break;
            }
        }
        // South-east (from white's POV)
        if((square % 8) != 0 && square > 7) {
            for(u8 i = square-9; i < 63; i -= 9) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i) || (i % 8) == 0 || i < 8)
                    break;
            }
        }
        // South-west (from white's POV)
        if((square % 8) != 7 && square > 7) {
            for(u8 i = square-7; i < 63; i -= 7) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i) || (i % 8) == 7 || i < 8)
                    break;
            }
        }
        attack_bb &= ~black_pieces_bb;
        break;

        // White bishop
        case BW:
        // North-west (from white's POV)
        if((square % 8) != 7 && square < 56) {
            for(u8 i = square+9; i < 64; i += 9) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i) || (i % 8) == 7 || i > 55)
                    break;
            }
        }
        // North-east (from white's POV)
        if((square % 8) != 0 && square < 56) {
            for(u8 i = square+7; i < 63; i += 7) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i) || (i % 8) == 0 || i > 55)
                    break;
            }
        }
        // South-east (from white's POV)
        if((square % 8) != 0 && square > 7) {
            for(u8 i = square-9; i < 63; i -= 9) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i) || (i % 8) == 0 || i < 8)
                    break;
            }
        }
        // South-west (from white's POV)
        if((square % 8) != 7 && square > 7) {
            for(u8 i = square-7; i < 63; i -= 7) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i) || (i % 8) == 7 || i < 8)
                    break;
            }
        }
        attack_bb &= ~white_pieces_bb;
        break;

        // Black rook
        case RB:
        // Right (from white's POV)
        if(square > 0) {
            for(u8 i = square - 1; i >= (square - (square % 8)); --i) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i))
                    break;
                if(i == 0)
                    break;
            }
        }
        // Left (from white's POV)
        for(u8 i = square + 1; i < (square + (8 - (square % 8))); ++i) {
            attack_bb |= (1ULL << i);
            if(all_pieces_bb & (1ULL << i))
                break;
        }
        // Up (from white's POV)
        for(u8 i = square + 8; i < 64; i += 8) {
            attack_bb |= (1ULL << i);
            if(all_pieces_bb & (1ULL << i))
                break;
        }
        // Down (from white's POV)
        if(square > 7) {
            for(u8 i = square - 8; i >= 0; i -= 8) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i))
                    break;
            }
        }
        attack_bb &= ~black_pieces_bb;
        break;

        // White rook
        case RW:
        // Right (from white's POV)
        if(square > 0) {
            for(u8 i = square - 1; i >= (square - (square % 8)); --i) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i))
                    break;
                if(i == 0)
                    break;
            }
        }
        // Left (from white's POV)
        for(u8 i = square + 1; i < (square + (8 - (square % 8))); ++i) {
            attack_bb |= (1ULL << i);
            if(all_pieces_bb & (1ULL << i))
                break;
        }
        // Up (from white's POV)
        for(u8 i = square + 8; i < 64; i += 8) {
            attack_bb |= (1ULL << i);
            if(all_pieces_bb & (1ULL << i))
                break;
        }
        // Down (from white's POV)
        if(square > 7) {
            for(u8 i = square - 8; i >= 0; i -= 8) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i))
                    break;
            }
        }
        attack_bb &= ~white_pieces_bb;
        break;

        // Black queen
        case QB:
        // North-west
        if((square % 8) != 7 && square < 56) {
            for(u8 i = square+9; i < 64; i += 9) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i) || (i % 8) == 7 || i > 55)
                    break;
            }
        }
        // North-east (from white's POV)
        if((square % 8) != 0 && square < 56) {
            for(u8 i = square+7; i < 63; i += 7) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i) || (i % 8) == 0 || i > 55)
                    break;
            }
        }
        // South-east (from white's POV)
        if((square % 8) != 0 && square > 7) {
            for(u8 i = square-9; i < 63; i -= 9) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i) || (i % 8) == 0 || i < 8)
                    break;
            }
        }
        // South-west (from white's POV)
        if((square % 8) != 7 && square > 7) {
            for(u8 i = square-7; i < 63; i -= 7) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i) || (i % 8) == 7 || i < 8)
                    break;
            }
        }
        // Right (from white's POV)
        if(square > 0) {
            for(u8 i = square - 1; i >= (square - (square % 8)); --i) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i))
                    break;
                if(i == 0)
                    break;
            }
        }
        // Left (from white's POV)
        for(u8 i = square + 1; i < (square + (8 - (square % 8))); ++i) {
            attack_bb |= (1ULL << i);
            if(all_pieces_bb & (1ULL << i))
                break;
        }
        // Up (from white's POV)
        for(u8 i = square + 8; i < 64; i += 8) {
            attack_bb |= (1ULL << i);
            if(all_pieces_bb & (1ULL << i))
                break;
        }
        // Down (from white's POV)
        if(square > 7) {
            for(u8 i = square - 8; i >= 0; i -= 8) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i))
                    break;
            }
        }
        attack_bb &= ~black_pieces_bb;
        break;

        // White queen
        case QW:
        // North-west
        if((square % 8) != 7 && square < 56) {
            for(u8 i = square+9; i < 64; i += 9) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i) || (i % 8) == 7 || i > 55)
                    break;
            }
        }
        // North-east (from white's POV)
        if((square % 8) != 0 && square < 56) {
            for(u8 i = square+7; i < 63; i += 7) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i) || (i % 8) == 0 || i > 55)
                    break;
            }
        }
        // South-east (from white's POV)
        if((square % 8) != 0 && square > 7) {
            for(u8 i = square-9; i < 63; i -= 9) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i) || (i % 8) == 0 || i < 8)
                    break;
            }
        }
        // South-west (from white's POV)
        if((square % 8) != 7 && square > 7) {
            for(u8 i = square-7; i < 63; i -= 7) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i) || (i % 8) == 7 || i < 8)
                    break;
            }
        }
        // Right (from white's POV)
        if(square > 0) {
            for(u8 i = square - 1; i >= (square - (square % 8)); --i) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i))
                    break;
                if(i == 0)
                    break;
            }
        }
        // Left (from white's POV)
        for(u8 i = square + 1; i < (square + (8 - (square % 8))); ++i) {
            attack_bb |= (1ULL << i);
            if(all_pieces_bb & (1ULL << i))
                break;
        }
        // Up (from white's POV)
        for(u8 i = square + 8; i < 64; i += 8) {
            attack_bb |= (1ULL << i);
            if(all_pieces_bb & (1ULL << i))
                break;
        }
        // Down (from white's POV)
        if(square > 7) {
            for(u8 i = square - 8; i >= 0; i -= 8) {
                attack_bb |= (1ULL << i);
                if(all_pieces_bb & (1ULL << i))
                    break;
            }
        }
        attack_bb &= ~white_pieces_bb;
        break;

        // Black king
        case KB:
        attack_bb |= (1ULL << (square + 1) & chess::moves::no_h_file);
        attack_bb |= (1ULL << (square - 1) & chess::moves::no_a_file);
        if(square > 7) {
            attack_bb |= (1ULL << (square - 8));
            attack_bb |= (1ULL << (square - 9) & chess::moves::no_a_file);
            attack_bb |= (1ULL << (square - 7) & chess::moves::no_h_file);
        }
        if(square < 56) {
            attack_bb |= (1ULL << (square + 9) & chess::moves::no_h_file);
            attack_bb |= (1ULL << (square + 8));
            attack_bb |= (1ULL << (square + 7) & chess::moves::no_a_file);
        }
        attack_bb &= ~black_pieces_bb;
        break;

        // White king
        case KW:
        attack_bb |= (1ULL << (square + 1) & chess::moves::no_h_file);
        attack_bb |= (1ULL << (square - 1) & chess::moves::no_a_file);
        if(square > 7) {
            attack_bb |= (1ULL << (square - 8));
            attack_bb |= (1ULL << (square - 9) & chess::moves::no_a_file);
            attack_bb |= (1ULL << (square - 7) & chess::moves::no_h_file);
        }
        if(square < 56) {
            attack_bb |= (1ULL << (square + 9) & chess::moves::no_h_file);
            attack_bb |= (1ULL << (square + 8));
            attack_bb |= (1ULL << (square + 7) & chess::moves::no_a_file);
        }
        attack_bb &= ~white_pieces_bb;
        break;
    }
    return attack_bb;
}
