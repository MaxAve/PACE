#include "../include/search.h"

chess::search::Eval chess::search::minimax(const chess::board::Board &b, bool maximizing, int alpha, int beta, u8 depth)
{
    chess::search::Eval position_eval;
    
    const u64 w_bb = WHITE_PIECE_BB(b);
    const u64 b_bb = BLACK_PIECE_BB(b);

    if(!b.bitboards[KW])
    {
        position_eval.eval = -1000000000 - depth; // Checkmate - amount of moves required to get there
        return position_eval;
    }
    else if(!b.bitboards[KB])
    {
        position_eval.eval = 1000000000 + depth; // Checkmate + amount of moves required to get there
        return position_eval;
    }
    else if(chess::eval::is_draw(b, chess::search::position_history, w_bb, b_bb))
    {
        position_eval.eval = 0;
        return position_eval;
    }
    else if(depth == 0) {
        position_eval.eval = chess::eval::eval_pst(b); // TODO improve evaluation
        return position_eval;
    }
    else
    {
        if(maximizing)
        {
            position_eval = {INT_MIN, 0, 0ULL};

            for(u8 i = 6; i < 12; ++i)
            {
                for(char j = 63; j >= 0; --j)
                {
                    if(b.bitboards[i] & (1ULL << j))
                    {
                        const u64 moves_bb = chess::moves::get_attack_bitboard(i, w_bb, b_bb, w_bb | b_bb, j);
                        u64 ordered_moves[2];
                        ordered_moves[0] = moves_bb & b_bb; // Capturing moves
                        ordered_moves[1] = moves_bb & ~ordered_moves[0]; // Passive moves

                        for(u8 k = 0; k < 2; ++k)
                        {
                            for(u8 l = 0; l < 64; ++l)
                            {
                                const u64 moved_piece = ordered_moves[k] & (1ULL << l);
                                if(moved_piece)
                                {
                                    chess::board::Board hypothetical_board = b;
                                    hypothetical_board.bitboards[i] |= moved_piece;
                                    hypothetical_board.bitboards[i] &= ~(1ULL << j);
                                    for(u8 l = 0; l < 6; ++l)
                                    {
                                        hypothetical_board.bitboards[l] &= ~moved_piece; // Captured piece
                                    }

                                    // Promotion
                                    hypothetical_board.bitboards[10] |= (hypothetical_board.bitboards[6] & 0xff00000000000000ULL);
                                    hypothetical_board.bitboards[6] &= 0x00ffffffffffffffULL;

                                    chess::search::Eval hypothetical_eval = chess::search::minimax(hypothetical_board, false, alpha, beta, depth-1);

                                    if(hypothetical_eval.eval > position_eval.eval)
                                    {
                                        position_eval.eval = hypothetical_eval.eval;
                                        position_eval.new_bitboard = hypothetical_board.bitboards[i];
                                        position_eval.piece_to_move = i;
                                        position_eval.promotion_piece = 10;
                                        position_eval.promotion_bitboard = hypothetical_board.bitboards[10];
                                    }

                                    positions_analyzed++;

                                    alpha = std::max(alpha, position_eval.eval);
                                    if(alpha >= beta)
                                        return position_eval;
                                }
                            }
                        }
                    }
                }
            }
        }
        else {
            position_eval = {INT_MAX, 0, 0ULL};

            for(u8 i = 0; i < 6; ++i)
            {
                for(u8 j = 0; j < 64; ++j)
                {
                    if(b.bitboards[i] & (1ULL << j))
                    {
                        u64 moves_bb = chess::moves::get_attack_bitboard(i, w_bb, b_bb, w_bb | b_bb, j);
                        u64 ordered_moves[2];
                        ordered_moves[0] = moves_bb & b_bb; // Capturing moves
                        ordered_moves[1] = moves_bb & ~ordered_moves[0]; // Passive moves

                        for(u8 k = 0; k < 2; ++k)
                        {
                            for(u8 l = 0; l < 64; ++l)
                            {
                                const u64 moved_piece = ordered_moves[k] & (1ULL << l);
                                if(moved_piece)
                                {
                                    chess::board::Board hypothetical_board = b;
                                    hypothetical_board.bitboards[i] |= moved_piece;
                                    hypothetical_board.bitboards[i] &= ~(1ULL << j);
                                    for(u8 l = 6; l < 12; ++l)
                                    {
                                        hypothetical_board.bitboards[l] &= ~moved_piece; // Piece capture
                                    }

                                    // Promotion
                                    hypothetical_board.bitboards[4] |= (hypothetical_board.bitboards[0] & 0x00000000000000ffULL);
                                    hypothetical_board.bitboards[0] &= 0xffffffffffffff00ULL;

                                    chess::search::Eval hypothetical_eval = chess::search::minimax(hypothetical_board, true, alpha, beta, depth-1);

                                    if(hypothetical_eval.eval < position_eval.eval)
                                    {
                                        position_eval.eval = hypothetical_eval.eval;
                                        position_eval.new_bitboard = hypothetical_board.bitboards[i];
                                        position_eval.piece_to_move = i;
                                        position_eval.promotion_piece = 4;
                                        position_eval.promotion_bitboard = hypothetical_board.bitboards[4];
                                    }

                                    positions_analyzed++;

                                    beta = std::min(beta, position_eval.eval);
                                    if(alpha >= beta)
                                        return position_eval;
                                }
                            }
                        }
                    }
                }
            }
        }

        return position_eval;
    }
}

bool chess::search::compare_greater_board(const chess::search::BoardMove &a, const chess::search::BoardMove &b)
{
    return chess::eval::eval_pst(a.board) > chess::eval::eval_pst(b.board);
}

bool chess::search::compare_lesser_board(const chess::search::BoardMove &a, const chess::search::BoardMove &b)
{
    return chess::eval::eval_pst(a.board) < chess::eval::eval_pst(b.board);
}

u64 chess::search::positions_analyzed = 0ULL;
std::unordered_map<u64, u8> chess::search::position_history = {};
