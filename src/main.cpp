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
#include "../include/gui.h"

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

        chess::search::position_history[chess::board::zobrist_hash(b)]++; // Add to move history

        if(clear_screen)
            (void)system("clear");

        print_board(b, true/*, chess::moves::get_attack_bitboard(5, WHITE_PIECE_BB(b), BLACK_PIECE_BB(b), WHITE_PIECE_BB(b) | BLACK_PIECE_BB(b), 0)*/); // Print board
        b.flags ^= (1ULL << 4); // Switch turns

        std::cout << "Position hash: " << chess::board::zobrist_hash(b) << "\n";

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

        if(chess::eval::is_draw(b, chess::search::position_history, WHITE_PIECE_BB(b), BLACK_PIECE_BB(b)))
        {
            std::cout << "\nDRAW!\n";
            break;
        }

        //std::cout << "\nUpdating transposition table...\n";

        //update_transposition_table(transposition_table_min_lru);

        //std::cout << "Done! (" << transposition_table.size() << " entries updated)\n";
        // std::cout << "\n\nMove history:\n\n";
        // for(auto& entry : chess::search::position_history) {
        //     std::cout << entry.first << ": " << std::to_string(entry.second) << "\n";
        // }
    }
}

int main(int argc, char** argv)
{
    Board board = fen_to_board("rn2kb1r/pp2pppp/2p2n2/q4b2/2BP4/2N2N2/PPP2PPP/R1BQK2R w - - 0 1");
    chess::zobrist::init_zobrist_keys();
    // cpu_vs_cpu(board, 4); // Start a game with the engine playing against itself

    gui::display(board);

    return 0;
}
