#include <iostream>
#include "../include/types.h"
#include "../include/board.h"
#include "../include/moves.h"

using namespace chess;
using namespace chess::board;
using namespace chess::moves;

int main(int argc, char** argv)
{
    /*
    This is a demo of some of the newly added features
    */

    Board b = EMPTY_BOARD; // Board

    u64 attack_bb = 0ULL;

    u8 pos = 36; // Piece's square
    u8 piece_type = QW; // Piece's type

    PUT_PIECE(b, piece_type, pos);
    attack_bb = get_attack_bitboard(b, pos, piece_type, WHITE_PIECE_BB(b), BLACK_PIECE_BB(b), PIECE_BB(b)); // Set attack_bb to the attack bitboard of the piece

    print_board(b, attack_bb); // Print board

    return 0;
}
