#pragma once

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <limits.h>
#include "types.h"
#include "board.h"
#include "eval.h"
#include "moves.h"

namespace chess
{
    namespace search
    {
        typedef struct
        {
            int eval;
            u8 piece_to_move;
            u64 new_bitboard;
            u8 promotion_piece;
            u64 promotion_bitboard;
        } Eval;

        typedef struct
        {
            chess::board::Board board; // New position
            u8 piece_to_move; // The piece that was moved
        } BoardMove;

        bool compare_greater_board(const BoardMove &a, const BoardMove &b);

        bool compare_lesser_board(const BoardMove &a, const BoardMove &b);
        
        extern u64 positions_analyzed; // Counter for debugging

        extern std::unordered_map<u64, u8> position_history; // Used for checking for three-fold repetition

        /**
         * @brief Adds a board state and eval to the transposition table
         * @param board 
         */
        void add_to_transposition_table(const board::Board &board, int eval);

        /**
         * @brief Iterates through the transposition table, updating the score of each entry and deleting irrelevant ones
         * @param removal_score after every move the engine makes, each entry in the transposition table has their score removed. If said score is below removal_score, it will get deleted from the transposition table as we can assume that it has become irrelevant
         */
        void update_transposition_table(int removal_score);

        /**
         * @brief Minimax algorithm which returns the best move and evaluation in a given position
         * @param b board state to analyze
         * @param maximizing whether the computer is searching for the most positive or negative evaluation
         * @param alpha alpha value used in alpha-beta pruning (set to INT_MIN)
         * @param beta beta value used in alpha-beta pruning (set to INT_MAX)
         * @param depth search depth
         * @return Eval 
         */
        Eval minimax(const board::Board &b, bool maximizing, int alpha, int beta, u8 depth);
    }
}
