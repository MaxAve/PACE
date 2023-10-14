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
    std::cout << "\nPosition evaluation: -\nPositions analyzed: -\n";

    bool white_turn = true; // This variable is used to control who's turn it is
    while(b.bitboards[KW] && b.bitboards[KB])
    {
        positions_analyzed = 0; // Set counter for positions analyzed to 0
        Eval evaluation = minimax(b, white_turn, INT_MIN, INT_MAX, 8); // Evaluate the position and find the best move

        // Modify main board to reflect the move
        for(int i = 0; i < 12; ++i)
            b.bitboards[i] &= ~evaluation.new_bitboard;
        b.bitboards[evaluation.piece_to_move] = evaluation.new_bitboard;
        b.bitboards[evaluation.promotion_piece] = evaluation.promotion_bitboard;

        print_board(b); // Print board
        white_turn = !white_turn; // Turn swap

        // Display position analysis and number of positions analyzed
        std::cout << "\nPosition evaluation: " << evaluation.eval << "\n";
        std::cout << "Positions analyzed: " << positions_analyzed << " (~" << std::round((float)positions_analyzed/1000000) << " Million)\n";
    }
}

int main(int argc, char** argv)
{
    Board b = fen_to_board("8/1k6/8/4Q3/3K4/8/8/8"); // Basic mate in 4 in Queen + King vs King endgame
    cpu_vs_cpu(b); // Start a game with the engine playing against itself

    return 0;
}
