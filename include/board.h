#pragma once

#include <types.h>
#include <stdbool.h>
#include <stdio.h>

#define STANDARD_BOARD {{0x00ff000000000000ULL, 0x4200000000000000ULL, 0x2400000000000000ULL, 0x8100000000000000ULL, 0x1000000000000000ULL, 0x0800000000000000ULL, 0x000000000000ff00ULL, 0x0000000000000042ULL, 0x0000000000000024ULL, 0x0000000000000081ULL, 0x0000000000000010ULL, 0x0000000000000008ULL}, 0b00001111}
#define PUT_PIECE(board, piece, square)(board.bitboards[piece] |= (1ULL << square))

typedef struct
{
    u64 bitboards[12];  // Contains 12 bitboards each for every piece type
    u8 flags;           // Contains flags like castling rights
} Board;

void print_board(Board board);      /* Displays a board in the terminal */