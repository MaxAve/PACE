#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
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

/**
 * @brief Makes the engine play out the given position against itself
 * 
 * @param b position to play
 * @param depth search depth for the engine
 */
void cpu_vs_cpu(Board &b, u8 depth)
{
    print_board(b, true); // Print board
    std::cout << "\nPosition evaluation: -\nPositions analyzed: -\n";

    bool p1_turn = true; // This variable is used to control who's turn it is (p1_turn == true means that it's white's turn)
    while(b.bitboards[KW] && b.bitboards[KB])
    {
        positions_analyzed = 0; // Set counter for positions analyzed to 0
        Eval evaluation = minimax(b, p1_turn, INT_MIN, INT_MAX, depth); // Evaluate the position and find the best move

        // Modify main board to reflect the move
        for(int i = 0; i < 12; ++i)
            b.bitboards[i] &= ~evaluation.new_bitboard; // Capture any pieces on the target square
        b.bitboards[evaluation.piece_to_move] = evaluation.new_bitboard; // Move piece
        b.bitboards[evaluation.promotion_piece] = evaluation.promotion_bitboard; // Promotion (if a pawn reaches the opposite end of board)

        print_board(b, true); // Print board
        p1_turn = !p1_turn; // Turn swap

        // Display position analysis and number of positions analyzed
        if(std::abs(evaluation.eval) < 1000000000)
        {
            std::cout << "\nPosition evaluation: " << evaluation.eval << "\n";
        }
        else {
            if(evaluation.eval > 0)
                std::cout << "\nPosition evaluation: +M" << (depth-(evaluation.eval-1000000000)-1)/2 << "\n";
            else
                std::cout << "\nPosition evaluation: -M" << (depth-(std::abs(evaluation.eval)-1000000000)-1)/2 << "\n";
        }
        if(positions_analyzed >= 1000000)
            std::cout << "Positions analyzed: " << positions_analyzed << " (~" << std::round((float)positions_analyzed/1000000) << " Million)\n";
        else
            std::cout << "Positions analyzed: " << positions_analyzed << " (< 1 Million)\n";
    }
}

int main(int argc, char** argv)
{
    Board board = fen_to_board("8/1k6/8/4Q3/3K4/8/8/8 w - - 0 1"); // Basic mate in 4 in Queen + King vs King endgame
    cpu_vs_cpu(board, 8); // Start a game with the engine playing against itself

    return 0;
}
