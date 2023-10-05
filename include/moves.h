#pragma once

#include <stdbool.h>
#include "types.h"
#include "board.h"

bool get_piece_color(Board b, u8 square); /* Returns the piece color of a piece at a given square */
u8 get_piece_type(Board b, u8 square); /* Returns the piece ID of a piece at a given square */
u64 get_attack_bitboard(Board b, u8 square, u8 piece_type, u64 enemy_bb, u64 friendly_bb); /* Returns a bitboard which defines to which squares a given piece can move to in a given position */