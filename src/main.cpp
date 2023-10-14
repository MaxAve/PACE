#include <iostream>
#include <cmath>
#include "../include/types.h"
#include "../include/board.h"
#include "../include/moves.h"
#include "../include/eval.h"
#include "../include/search.h"
#include "../include/uci.h"

using namespace chess;
using namespace chess::board;
using namespace chess::moves;
using namespace chess::eval;
using namespace chess::search;
using namespace chess::uci;

void cpu_vs_cpu(Board &b)
{
    print_board(b); // Print board
    std::cout << "\n";

    bool max = true; // This variable is used to control who's turn it is
    while(true)
    {
        positions_analyzed = 0; // Set counter for positions analyzed to 0
        Eval evaluation = minimax(b, max, INT_MIN, INT_MAX, 6); // Evaluate the position and find the best move

        // Modify main board to reflect the move
        for(int i = 0; i < 12; ++i)
            b.bitboards[i] &= ~evaluation.new_bitboard;
        b.bitboards[evaluation.piece_to_move] = evaluation.new_bitboard;
        b.bitboards[evaluation.promotion_piece] = evaluation.promotion_bitboard;

        print_board(b); // Print board
        max = !max; // Turn swap

        // Display position analysis and number of positions analyzed
        std::cout << "\nPosition evaluation: " << evaluation.eval << "\n";
        std::cout << "Positions analyzed: " << positions_analyzed << " (~" << std::round((float)positions_analyzed/1000000) << " Million)\n";
    }
}

int main(int argc, char** argv)
{
    Board b = STANDARD_BOARD; // Main board
    cpu_vs_cpu(b); // Start a game with the engine playing against itself

    return 0;
}
