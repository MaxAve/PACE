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

    print_board(b); // Print board

    std::cout << "\nEvaluation: " << count_material(b);

    return 0;
}
