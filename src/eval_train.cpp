#include "../include/eval_train.h"

u8 chess::trainer::play_game(AgentScore &p1, AgentScore &p2, int depth)
{
    chess::board::Board board = chess::uci::fen_to_board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/PNBQKBNR w KQkq - 0 1");
    int moves = 0;
    while(true)
    {
        chess::search::Eval evaluation = chess::search::minimax(board, board.flags & (1ULL << 4), INT_MIN, INT_MAX, depth);
        
        for(int i = 0; i < 12; i++)
            board.bitboards[i] &= ~evaluation.new_bitboard;
        board.bitboards[evaluation.piece_to_move] = evaluation.new_bitboard;
        chess::board::promote_pawns(board, QUEEN);

        if(board.bitboards[KW] == 0)
        {
            p1.score += (100 - moves);
            return P1_WIN;
        }
        else if(board.bitboards[KB] == 0)
        {
            p2.score += (100 - moves);
            return P2_WIN;
        }

        if(chess::eval::is_draw(board, chess::search::position_history, WHITE_PIECE_BB(board), BLACK_PIECE_BB(board)))
        {
            p1.score += 50;
            p2.score += 50;
            return DRAW;
        }

        board.flags ^= (1ULL << 4);
        moves++;
    }
    return DRAW;
}

void chess::trainer::train_pst(int generations, int agents_per_generation, int mutation_range, int calc_depth)
{
    std::vector<chess::trainer::AgentScore> agents;

    for(int gen = 0; gen < generations; gen++)
    {
        std::cout << "Generation: " << gen << "\n";

        int game_num = 0;

        for(int p1 = 0; p1 < agents.size(); p1++)
        {
            for(int p2 = 0; p2 < agents.size(); p2++)
            {
                if(p1 != p2)
                {
                    std::cout << "Game #" << game_num << "(#" << p1 << " vs #" << p2 << "): ";

                    u8 res = chess::trainer::play_game(agents.at(p1), agents.at(p2), calc_depth);
                    
                    if(res == P1_WIN)
                        std::cout << "1 - 0\n";
                    else if(res == P2_WIN)
                        std::cout << "0 - 1\n";
                    else
                        std::cout << "1/2 - 1/2\n";
                }

                game_num++;
            }
        }
    }
}
