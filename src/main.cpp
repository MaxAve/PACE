#include <iostream>
#include "../include/types.h"
#include "../include/board.h"
#include "../include/moves.h"

using namespace chess;
using namespace chess::board;
using namespace chess::moves;

int main(int argc, char** argv)
{
    // This is a demo of some of the newly added features

    Board b = EMPTY_BOARD;
    u64 attack_bb = 0ULL;
    u8 pos = 36;
    PUT_PIECE(b, BB, pos);
    attack_bb = get_attack_bitboard(b, pos, BB, WHITE_PIECE_BB(b), BLACK_PIECE_BB(b), PIECE_BB(b));
    print_board(b, attack_bb);

    return 0;
}
