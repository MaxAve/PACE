#include <iostream>
#include "../include/types.h"
#include "../include/board.h"
#include "../include/moves.h"
#include "../include/eval.h"

using namespace chess;
using namespace chess::board;
using namespace chess::moves;
using namespace chess::eval;

int main(int argc, char** argv)
{
    /*
    This is a demo of some of the newly added features
    */

    Board b = STANDARD_BOARD; // Standard board setupa

    print_board(b, get_attack_bitboard(NW, WHITE_PIECE_BB(b), BLACK_PIECE_BB(b), PIECE_BB(b), 1)); // Print board

    std::cout << "\nEvaluation: " << count_material(b);

    return 0;
}
