#include "../include/search.h"

u64 chess::search::positions_analyzed = 0ULL;

std::unordered_map<chess::board::Board, chess::search::EvalScored, chess::board::BoardHash, chess::board::BoardEqual> chess::search::transposition_table = {};

u64 chess::search::zobrist_hash(const chess::board::Board &b)
{
    u64 hash = 0;
    for(u8 i = 0; i < 12; ++i)
    {
        for(u8 j = 0; j < 64; ++j)
        {
            if(b.bitboards[i] & (1ULL << j))
            {
                hash ^= chess::zobrist::zobrist_keys[i][j];
            }
        }
    }
    for(u8 i = 0; i < 8; ++i)
    {
        if(b.flags & (1 << i))
        {
            hash ^= chess::zobrist::zobrist_keys_u8[i];
        }
    }
    return hash;
}

void chess::search::update_transposition_table(int removal_score)
{
    std::vector<chess::board::Board> keys_to_delete;
    for(auto& entry : chess::search::transposition_table)
    {
        entry.second.lru_score--;
        if(entry.second.lru_score <= removal_score)
            keys_to_delete.push_back(entry.first);
    }
    for(auto& key : keys_to_delete)
    {
        chess::search::transposition_table.erase(key);
    }
}

chess::search::Eval chess::search::minimax(const chess::board::Board &b, bool maximizing, int alpha, int beta, u8 depth)
{
    chess::search::Eval position_eval;
    
    if(!b.bitboards[KW]) {
        position_eval.eval = -1000000000 - depth; // Checkmate - amount of moves required to get there
        return position_eval;
    } else if(!b.bitboards[KB]) {
        position_eval.eval = 1000000000 + depth; // Checkmate + amount of moves required to get there
        return position_eval;
    } else if(depth == 0) {
        //if(chess::search::transposition_table.find(b) == chess::search::transposition_table.end())
        //{
            position_eval.eval = chess::eval::eval_pst(b); // TODO improve evaluation
        //     chess::search::add_to_transposition_table(b, position_eval);
        // }
        // else {
        //     position_eval.eval = chess::search::transposition_table[b].eval.eval;
        //     chess::search::transposition_table[b].lru_score++; // Increase evaluation relevancy score
        // }
        return position_eval;
    } else {
        if(maximizing)
        {
            position_eval = {INT_MIN, 0, 0ULL};

            for(u8 i = 6; i < 12; ++i)
            {
                for(char j = 63; j >= 0; --j)
                {
                    if(b.bitboards[i] & (1ULL << j))
                    {
                        const u64 w_bb = WHITE_PIECE_BB(b);
                        const u64 b_bb = BLACK_PIECE_BB(b);

                        const u64 moves_bb = chess::moves::get_attack_bitboard(i, w_bb, b_bb, w_bb | b_bb, j);
                        const u64 capture_moves_bb = moves_bb & b_bb; // Moves that result in piece captures
                        const u64 passive_moves_bb = moves_bb & ~capture_moves_bb; // Passive moves

                        // Check aggressive moves
                        for(u8 k = 0; k < 64; ++k)
                        {
                            const u64 moved_piece = capture_moves_bb & (1ULL << k);
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
                                
                                chess::search::Eval hypothetical_eval;
                                // if(chess::search::transposition_table.find(hypothetical_board) == chess::search::transposition_table.end())
                                // {
                                    // Go deeper into search tree and save result to transposition table
                                    hypothetical_eval = chess::search::minimax(hypothetical_board, false, alpha, beta, depth-1);
                                //     const chess::search::EvalScored e = {hypothetical_eval.eval, 0};
                                //     chess::search::transposition_table[hypothetical_board] = e;
                                // }
                                // else {
                                //     hypothetical_eval.eval = chess::search::transposition_table[hypothetical_board].eval;
                                //     chess::search::transposition_table[hypothetical_board].lru_score += 1;
                                // }

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
                        // Check passive moves
                        for(u8 k = 0; k < 64; ++k)
                        {
                            const u64 moved_piece = passive_moves_bb & (1ULL << k);
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

                                chess::search::Eval hypothetical_eval;
                                // if(chess::search::transposition_table.find(hypothetical_board) == chess::search::transposition_table.end())
                                // {
                                    // Go deeper into search tree and save result to transposition table
                                    hypothetical_eval = chess::search::minimax(hypothetical_board, false, alpha, beta, depth-1);
                                //     const chess::search::EvalScored e = {hypothetical_eval.eval, 0};
                                //     chess::search::transposition_table[hypothetical_board] = e;
                                // }
                                // else {
                                //     hypothetical_eval.eval = chess::search::transposition_table[hypothetical_board].eval;
                                //     chess::search::transposition_table[hypothetical_board].lru_score += 1;
                                // }

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
        else {
            position_eval = {INT_MAX, 0, 0ULL};

            for(u8 i = 0; i < 6; ++i)
            {
                for(u8 j = 0; j < 64; ++j)
                {
                    if(b.bitboards[i] & (1ULL << j))
                    {
                        const u64 w_bb = WHITE_PIECE_BB(b);
                        const u64 b_bb = BLACK_PIECE_BB(b);

                        u64 moves_bb = chess::moves::get_attack_bitboard(i, w_bb, b_bb, w_bb | b_bb, j);
                        const u64 capture_moves_bb = moves_bb & b_bb; // Moves that result in piece captures
                        const u64 passive_moves_bb = moves_bb & ~capture_moves_bb; // Passive moves

                        // Check aggresive moves
                        for(u8 k = 0; k < 64; ++k)
                        {
                            const u64 moved_piece = capture_moves_bb & (1ULL << k);
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

                                chess::search::Eval hypothetical_eval;
                                // if(chess::search::transposition_table.find(hypothetical_board) == chess::search::transposition_table.end())
                                // {
                                    // Go deeper into search tree and save result to transposition table
                                    hypothetical_eval = chess::search::minimax(hypothetical_board, true, alpha, beta, depth-1);
                                //     const chess::search::EvalScored e = {hypothetical_eval.eval, 0};
                                //     chess::search::transposition_table[hypothetical_board] = e;
                                // }
                                // else {
                                //     hypothetical_eval.eval = chess::search::transposition_table[hypothetical_board].eval;
                                //     chess::search::transposition_table[hypothetical_board].lru_score += 1;
                                // }

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
                        // Check passive moves
                        for(u8 k = 0; k < 64; ++k)
                        {
                            const u64 moved_piece = passive_moves_bb & (1ULL << k);
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

                                chess::search::Eval hypothetical_eval;
                                // if(chess::search::transposition_table.find(hypothetical_board) == chess::search::transposition_table.end())
                                // {
                                    // Go deeper into search tree and save result to transposition table
                                    hypothetical_eval = chess::search::minimax(hypothetical_board, true, alpha, beta, depth-1);
                                //     const chess::search::EvalScored e = {hypothetical_eval.eval, 0};
                                //     chess::search::transposition_table[hypothetical_board] = e;
                                // }
                                // else {
                                //     hypothetical_eval.eval = chess::search::transposition_table[hypothetical_board].eval;
                                //     chess::search::transposition_table[hypothetical_board].lru_score += 1;
                                // }

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

        return position_eval;
    }
}
