#pragma once

#include <vector>
#include <algorithm>
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

        // Used in lookup tables
        typedef struct
        {
            Eval eval;
            int lru_score; // Used to determine how relevant an entry is (should be incremented when entry is accessed)
        } EvalScored;

        extern std::unordered_map<board::Board, EvalScored, board::BoardHash, board::BoardEqual> transposition_table;

        extern u64 positions_analyzed;

        /**
         * @brief Adds a board state and eval to the transposition table
         * @param board 
         */
        void add_to_transposition_table(board::Board board, Eval eval);

        /**
         * @brief Iterates through the transposition table, updating the score of each entry and deleting irrelevant ones
         * @param max_table_size when the table is larger than max_table_size, a certain amount of entries with the lowest LRU score will be deleted to keep the table at a constant size
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
