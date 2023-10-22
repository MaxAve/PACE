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

    while(b.bitboards[KW] && b.bitboards[KB])
    {
        positions_analyzed = 0; // Set counter for positions analyzed to 0
        Eval evaluation = minimax(b, b.flags & (1ULL << 4), INT_MIN, INT_MAX, depth); // Evaluate the position and find the best move

        // Modify main board to reflect the move
        for(int i = 0; i < 12; ++i)
            b.bitboards[i] &= ~evaluation.new_bitboard; // Capture any pieces on the target square
        b.bitboards[evaluation.piece_to_move] = evaluation.new_bitboard; // Move piece
        b.bitboards[evaluation.promotion_piece] = evaluation.promotion_bitboard; // Promotion (if a pawn reaches the opposite end of board)

        print_board(b, true); // Print board
        b.flags ^= (1ULL << 4); // Switch turns

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
    Board board = STANDARD_BOARD; // Basic mate in 4 in Queen + King vs King endgame
    cpu_vs_cpu(board, 6); // Start a game with the engine playing against itself

    Board b = STANDARD_BOARD;
    Board b2 = EMPTY_BOARD;
    Eval e = {234, 12, 23, 3, 5};
    Eval e2 = {69, 120, 420, 120, 1};

    std::unordered_map<Board, Eval, BoardHash, BoardEqual> m;

    m[b] = e2;
    m[b2] = e;

    std::cout << m[b2].eval;

    return 0;
}
