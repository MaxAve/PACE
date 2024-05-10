#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <limits.h>
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

bool clear_screen = true;

void cpu_vs_cpu(Board &b, u8 depth)
{
    if(clear_screen)
        (void)system("clear");
    print_board(b, true); // Print board
    std::cout << "\nPosition evaluation: -\nPositions analyzed: -\n";

    while(b.bitboards[KW] && b.bitboards[KB])
    {
        positions_analyzed = 0; // Set counter for positions analyzed to 0
        std::cout << "\nThinking...\n";
        Eval evaluation = minimax(b, b.flags & (1ULL << 4), INT_MIN, INT_MAX, depth); // Evaluate the position and find the best move
        std::cout << "Done thinking!\n";

        // Modify main board to reflect the move
        for(int i = 0; i < 12; ++i)
            b.bitboards[i] &= ~evaluation.new_bitboard; // Capture any pieces on the target square
        b.bitboards[evaluation.piece_to_move] = evaluation.new_bitboard; // Move piece
        b.bitboards[evaluation.promotion_piece] = evaluation.promotion_bitboard; // Promotion (if a pawn reaches the opposite end of board)

        if(clear_screen)
            (void)system("clear");

        print_board(b, true); // Print board
        b.flags ^= (1ULL << 4); // Switch turns

        //std::cout << "Position hash: " << chess::search::zobrist_hash(b) << "\n";

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

        std::cout << "\nUpdating transposition table...\n";

        //update_transposition_table(transposition_table_min_lru);

        //std::cout << "Done! (" << transposition_table.size() << " entries updated)\n";
    }
}

int main(int argc, char** argv)
{
    Board board = fen_to_board("r2qkbnr/pp2pppp/2npb3/8/3NP3/2N5/PPP2PPP/R1BQKB1R w KQkq - 0 1");
    chess::zobrist::init_zobrist_keys();
    cpu_vs_cpu(board, 4); // Start a game with the engine playing against itself

    return 0;
}
