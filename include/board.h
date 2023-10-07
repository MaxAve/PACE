#pragma once

#include "types.h"
#include <iostream>

#define EMPTY_BOARD {{0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL}, 0} // A Board struct which has a simple empty position
#define STANDARD_BOARD {{0x00ff000000000000ULL, 0x4200000000000000ULL, 0x2400000000000000ULL, 0x8100000000000000ULL, 0x1000000000000000ULL, 0x0800000000000000ULL, 0x000000000000ff00ULL, 0x0000000000000042ULL, 0x0000000000000024ULL, 0x0000000000000081ULL, 0x0000000000000010ULL, 0x0000000000000008ULL}, 0x0f} // A Board struct which has the standard chess setup

#define PUT_PIECE(board, piece, square)(board.bitboards[piece] |= (1ULL << square)) /** Places a piece on a board @param board A Board struct to be modified @param piece the piece ID (0-11) @param square the square where the new piece should be placed at (0-63) */

#define BLACK_PIECE_BB(board)(board.bitboards[0] | board.bitboards[1] | board.bitboards[2] | board.bitboards[3] | board.bitboards[4] | board.bitboards[5])
#define WHITE_PIECE_BB(board)(board.bitboards[6] | board.bitboards[7] | board.bitboards[8] | board.bitboards[9] | board.bitboards[10] | board.bitboards[11])

namespace chess
{
namespace board
{
typedef struct
{
    u64 bitboards[12]; // Contains 12 bitboards each for every piece type
    u8 flags;          // Contains flags like castling rights
} Board;

/** Displays a board in the terminal @param board the board to be displayed @param mask bitmask which determines which squares should be marked. Used for debugging attack bitboards */
void print_board(Board board, u64 mask);
}
}