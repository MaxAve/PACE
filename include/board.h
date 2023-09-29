#include <types.h>
#include <stdbool.h>
#include <stdio.h>

#define PUT_PIECE(board, piece, square)(board.bitboards[piece] |= (1ULL << square))

typedef struct
{
    u64 bitboards[12];  // Contains 12 bitboards each for every piece type
    u8 flags;           // Contains flags like castling rights
} Board;

void print_board(Board board, bool show_extra);     /* Displays a board in the terminal */