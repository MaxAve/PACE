#pragma once

#include <vector>
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
            u8 age; // Used to determine whether this evaluation matters anymore (old evaluations should be deleted from lookup table)
        } EvalAge;

        extern std::unordered_map<board::Board, EvalAge, board::BoardHash, board::BoardEqual> lookup_table;

        extern u64 positions_analyzed;

        /**
         * @brief Adds a board state and eval to the lookup table
         * @param board 
         */
        void add_to_lookup(board::Board board, Eval eval);

        /**
         * @brief Iterates through the lookup table, updating the age of each element and deleting aged ones
         * @param elem_deletion_age the element age at which it should be deleted
         */
        void update_lookup(u8 elem_deletion_age);

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
