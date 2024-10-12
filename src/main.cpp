#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <limits.h>
#include <chrono>
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
using chess::search::positions_analyzed;

bool clear_screen = false;

void player_vs_cpu(Board &b, u8 depth)
{
    if(clear_screen)
        system("clear");
    gui::display(b);

    while(b.bitboards[KW] && b.bitboards[KB])
    {
        // probably could have used a library for this part...
        int player_move;
        std::cout << "Move: ";
        std::cin >> player_move;
        int from_x = player_move / 1000;
        int from_y = player_move / 100 - from_x * 10;
        int to_x = ((player_move - ((player_move / 100) * 100)) / 10);
        int to_y = (player_move - ((player_move / 10) * 10));

        int from_pos = 63 - (from_x + from_y * 8);
        int to_pos = 63 - (to_x + to_y * 8);
        std::cout << from_pos << ", " << to_pos << "\n";
        u8 piece_to_move = get_piece_type(b, from_pos);
        u64 pre_move_board = b.bitboards[piece_to_move];
        for(int i = 0; i < 12; ++i)
            b.bitboards[i] &= ~(1ULL << to_pos); // Capture any pieces on the target square
        b.bitboards[piece_to_move] &= ~(1ULL << from_pos);
        b.bitboards[piece_to_move] |= (1ULL << to_pos);

        if(clear_screen)
            system("clear");

        u64 change = (b.bitboards[piece_to_move] & ~pre_move_board) | (pre_move_board & ~b.bitboards[piece_to_move]);
        gui::display(b, change);

        positions_analyzed = 0; // Set counter for positions analyzed to 0
        Eval evaluation = minimax(b, false, INT_MIN, INT_MAX, depth); // Evaluate the position and find the best move

        // Modify main board to reflect the move
        for(int i = 0; i < 12; ++i)
            b.bitboards[i] &= ~evaluation.new_bitboard; // Capture any pieces on the target square
        b.bitboards[evaluation.piece_to_move] = evaluation.new_bitboard; // Move piece
        b.bitboards[evaluation.promotion_piece] = evaluation.promotion_bitboard; // Promotion (if a pawn reaches the opposite end of board)

        if(clear_screen)
            system("clear");

        change = (evaluation.new_bitboard & ~b.bitboards[evaluation.piece_to_move]) | (b.bitboards[evaluation.piece_to_move] & ~evaluation.new_bitboard);
        gui::display(b, change);

        chess::search::position_history[chess::board::zobrist_hash(b)]++; // Add to move history

        if(chess::eval::is_draw(b, chess::search::position_history, WHITE_PIECE_BB(b), BLACK_PIECE_BB(b)))
        {
            std::cout << "\nDRAW!\n";
            break;
        }
    }
}

void cpu_vs_cpu(Board &b, u8 depth)
{
    std::vector<float> think_times;

    if(clear_screen)
        system("clear");
    gui::display(b);//print_board(b, true); // Print board
    std::cout << "\nPosition evaluation: -\nPositions analyzed: -\n";

    while(b.bitboards[KW] && b.bitboards[KB])
    {
        auto think_time_start = std::chrono::high_resolution_clock::now();

        positions_analyzed = 0; // Set counter for positions analyzed to 0
        //std::cout << "\nThinking...\n";
        Eval evaluation = minimax(b, b.flags & (1ULL << 4), INT_MIN, INT_MAX, depth); // Evaluate the position and find the best move
        //std::cout << "Done thinking!\n";

        auto think_time_end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(think_time_end - think_time_start);

        think_times.push_back((float)duration.count() / 1000.0);

        u64 change = (evaluation.new_bitboard & ~b.bitboards[evaluation.piece_to_move]) | (b.bitboards[evaluation.piece_to_move] & ~evaluation.new_bitboard);

        // Modify main board to reflect the move
        for(int i = 0; i < 12; ++i)
            b.bitboards[i] &= ~evaluation.new_bitboard; // Capture any pieces on the target square
        b.bitboards[evaluation.piece_to_move] = evaluation.new_bitboard; // Move piece
        b.bitboards[evaluation.promotion_piece] = evaluation.promotion_bitboard; // Promotion (if a pawn reaches the opposite end of board)

        chess::search::position_history[chess::board::zobrist_hash(b)]++; // Add to move history

        if(clear_screen)
            system("clear");

        gui::display(b, change);//print_board(b, true/*, chess::moves::get_attack_bitboard(5, WHITE_PIECE_BB(b), BLACK_PIECE_BB(b), WHITE_PIECE_BB(b) | BLACK_PIECE_BB(b), 0)*/); // Print board
        b.flags ^= (1ULL << 4); // Switch turns

        //std::cout << "Position hash: " << chess::board::zobrist_hash(b) << "\n";

        // Display position analysis and number of positions analyzed
        // if(std::abs(evaluation.eval) < 1000000000)
        // {
        //     std::cout << "\nPosition evaluation: " << evaluation.eval << "\n";
        // }
        // else {
        //     if(evaluation.eval > 0)
        //         std::cout << "\nPosition evaluation: +M" << (depth-(evaluation.eval-1000000000)-1)/2 << "\n";
        //     else
        //         std::cout << "\nPosition evaluation: -M" << (depth-(std::abs(evaluation.eval)-1000000000)-1)/2 << "\n";
        // }
        // if(positions_analyzed >= 1000000)
        //     std::cout << "Positions analyzed: " << positions_analyzed << " (~" << std::round((float)positions_analyzed/1000000) << " Million)\n";
        // else
        //     std::cout << "Positions analyzed: " << positions_analyzed << " (< 1 Million)\n";

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

    float sum = 0;
    float min_ = 69420.0;
    float max_ = -696429.0;
    std::cout << "Move\tThink time (s)\n";
    for(int i = 0; i < think_times.size(); i++)
    {
        if(think_times.at(i) < min_)
            min_ = think_times.at(i);
        if(think_times.at(i) > max_)
            max_ = think_times.at(i);
        sum += think_times.at(i);
        std::cout << (i/2) << "\t" << think_times.at(i) << "\n";
    }
    float avg = sum / (float)think_times.size();
    std::cout << "Average: " << avg << "\n";
    std::cout << "Max: " << max_ << "\n";
    std::cout << "Min: " << min_ << "\n";
}

int main(int argc, char** argv)
{
    Board board = fen_to_board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    chess::zobrist::init_zobrist_keys();

    player_vs_cpu(board, 7); // Start a game with the engine playing against itself

    return 0;
}
