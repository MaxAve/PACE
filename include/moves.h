#pragma once

#include "types.h"
#include "board.h"

namespace chess
{
    namespace moves
    {
        const u64 no_h_file = 0xfefefefefefefefe; // ~0x0101010101010101
        const u64 no_a_file = 0x7f7f7f7f7f7f7f7f; // ~0x8080808080808080
        const u64 no_1_rank = 0xffffffffffffff00; // ~0x00000000000000ff
        const u64 no_8_rank = 0x00ffffffffffffff; // ~0xff00000000000000

        typedef struct
        {
            u8 from;
            u8 to;
        } Move;

        /* Returns the piece color of a piece at a given square */
        bool get_piece_color(const board::Board &b, u8 square);

        /* Returns the piece ID of a piece at a given square */
        u8 get_piece_type(const board::Board &b, u8 square);

        /**
         * @brief Returns a bitmask of all squares a piece can move to
         * 
         * @param piece_type type of piece
         * @param white_pieces_bb precomputed bitmask of all white pieces
         * @param black_pieces_bb precomputed bitmask of all black pieces
         * @param all_pieces_bb precomputed bitmask of all pieces
         * @param square location of the piece
         * @return u64 (unsigned long long)
         */
        u64 get_attack_bitboard(u8 piece_type, u64 white_pieces_bb, u64 black_pieces_bb, u64 all_pieces_bb, u8 square);
    }
}