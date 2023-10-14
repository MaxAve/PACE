#pragma once

#include "types.h"
#include "board.h"
#include "eval.h"
#include "moves.h"

namespace chess
{
    namespace search
    {
        extern u64 positions_analyzed;

        typedef struct
        {
            int eval;
            u8 piece_to_move;
            u64 new_bitboard;
            u8 promotion_piece;
            u64 promotion_bitboard;
        } Eval;

        /**
         * @brief Minimax algorithm which returns the best move and evaluation in a given position
         * 
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