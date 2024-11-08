#pragma once

#include "types.h"
#include "zobrist.h"
#include <iostream>
#include <unordered_map>

#define WHITE_TURN         0b00010000
#define WHITE_SHORT_CASTLE 0b00001000
#define WHITE_LONG_CASTLE  0b00000100
#define BLACK_SHORT_CASTLE 0b00000010
#define BLACK_LONG_CASTLE  0b00000001

#define EMPTY_BOARD    {{0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL}, 0}
#define STANDARD_BOARD {{0x00ff000000000000ULL, 0x4200000000000000ULL, 0x2400000000000000ULL, 0x8100000000000000ULL, 0x1000000000000000ULL, 0x0800000000000000ULL, 0x000000000000ff00ULL, 0x0000000000000042ULL, 0x0000000000000024ULL, 0x0000000000000081ULL, 0x0000000000000010ULL, 0x0000000000000008ULL}, 0x1f}

#define PUT_PIECE(board, piece, square) (board.bitboards[piece] |= (1ULL << square))

#define PIECE_BB(board)       (board.bitboards[0] | board.bitboards[1] | board.bitboards[2] | board.bitboards[3] | board.bitboards[4] | board.bitboards[5] | board.bitboards[6] | board.bitboards[7] | board.bitboards[8] | board.bitboards[9] | board.bitboards[10] | board.bitboards[11])
#define BLACK_PIECE_BB(board) (board.bitboards[0] | board.bitboards[1] | board.bitboards[2] | board.bitboards[3] | board.bitboards[4] | board.bitboards[5])
#define WHITE_PIECE_BB(board) (board.bitboards[6] | board.bitboards[7] | board.bitboards[8] | board.bitboards[9] | board.bitboards[10] | board.bitboards[11])

namespace chess
{
    namespace board
    {
        typedef struct
        {
            u64 bitboards[12]; // Contains 12 bitboards each for every piece type
            u8 flags;          // Contains flags like castling rights and current turn
        } Board;

        u64 zobrist_hash(const chess::board::Board &b);

	void promote_pawns(Board &b, u8 piece);

	void print_bb(const u64 &bb);

        /** Displays a board in the terminal @param board the board to be displayed @param mask bitmask which determines which squares should be marked. Used for debugging attack bitboards */
        void print_board(chess::board::Board board, bool display_flags=false, u64 mask=0ULL);
    }
}
