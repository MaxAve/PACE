#pragma once

#include "types.h"
#include "board.h"

namespace chess
{
namespace moves
{
/* Returns the piece color of a piece at a given square */
bool get_piece_color(board::Board b, u8 square);

/* Returns the piece ID of a piece at a given square */
u8 get_piece_type(board::Board b, u8 square);

/* Returns a bitboard which defines to which squares a given piece can move to in a given position */
u64 get_attack_bitboard(chess::board::Board b, u8 square, u8 piece_type, u64 white_pieces_bb, u64 black_pieces_bb, u64 all_pieces_bb);
}
}