#include "../include/eval_train.h"

chess::trainer::AgentScore chess::trainer::current_games[2];

bool chess::trainer::compare_score(const AgentScore &a, const AgentScore &b)
{
	return a.score < b.score;
}

int chess::trainer::eval_pst(const board::Board &b)
{
    int eval = 0;
    for(u8 i = 0; i < 6; ++i)
    {
        for(u8 j = 0; j < 64; ++j)
        {
            if(b.bitboards[i] & (1ULL << j))
            {
                eval -= chess::trainer::current_games[0].pst[i][j];
            }
        }
    }
    for(u8 i = 6; i < 12; ++i)
    {
        for(u8 j = 0; j < 64; ++j)
        {
            if(b.bitboards[i] & (1ULL << j))
            {
                eval += chess::trainer::current_games[1].pst[i-6][63-j];
            }
        }
    }
    return eval;
}

chess::trainer::AgentScore chess::trainer::breed_agents(const chess::trainer::AgentScore &a, const chess::trainer::AgentScore &b, int mutation)
{
	chess::trainer::AgentScore as;
	as.score = 0;
	for(int i = 0; i < 6; i++)
	{
		for(int j = 0; j < 64; j++)
		{
			as.pst[i][j] = (((rand()%2)==0) ? a.pst[i][j] : b.pst[i][j]) + ((rand() % (2*mutation)) - mutation);
		}
	}
	return as;
}

u8 chess::trainer::play_game(chess::board::Board board, const AgentScore &p1, const AgentScore &p2, int depth)
{
    int moves = 0;

	chess::trainer::current_games[0] = p1;
	chess::trainer::current_games[1] = p2;

    while(true)
    {
        chess::search::Eval evaluation = chess::search::minimax(board, board.flags & (1ULL << 4), INT_MIN, INT_MAX, depth, chess::trainer::eval_pst);
        
        for(int i = 0; i < 12; i++)
            board.bitboards[i] &= ~evaluation.new_bitboard;
        board.bitboards[evaluation.piece_to_move] = evaluation.new_bitboard;
        chess::board::promote_pawns(board, QUEEN);

		chess::search::position_history[chess::board::zobrist_hash(board)]++;

        if(board.bitboards[KW] == 0)
        {
			chess::gui::display(board);
            return P1_WIN;
        }
        else if(board.bitboards[KB] == 0)
        {
			chess::gui::display(board);
            return P2_WIN;
        }

        if(chess::eval::is_draw(board, chess::search::position_history, WHITE_PIECE_BB(board), BLACK_PIECE_BB(board)))
        {
			chess::gui::display(board);

			int diff = chess::eval::get_material_diff(board);
			std::cout << "Material difference: " << diff << "\n";

			// At low depth, the engine will struggle to convert a winning position
			// If the material difference is significant enough, we will give the winning engine the victory since
			// we can assume it would have likely won with a higher depth
			if(diff >= 4)
				return P1_WIN;
			else if(diff <= -4)
				return P2_WIN;
            return DRAW;
        }

        board.flags ^= (1ULL << 4);
        moves++;
    }

    return DRAW;
}

void chess::trainer::train_pst(int generations, int agents_per_generation, int survivors, int mutation_range, int calc_depth)
{
    std::vector<chess::trainer::AgentScore> agents;
	
	for(int i = 0; i < agents_per_generation; i++)
	{
		chess::trainer::AgentScore as;
		as.score = 0;
		for(int a = 0; a < 5; a++)
		{
			for(int b = 0; b < 64; b++)
			{
				as.pst[a][b] = rand() % 1000;
			}
		}
		for(int b = 0; b < 64; b++)
		{
			as.pst[5][b] = (rand() % 100) + 100000;
		}
		//DEBUG
		/*for(int a = 0; a < 6; a++)
		{
			for(int b = 0; b < 64; b++)
			{
				std::cout << as.pst[a][b] << " ";
			}
			std::cout << "\n";
		}*/
		agents.emplace_back(as);
	}

    for(int gen = 0; gen < generations; gen++)
    {
        std::cout << "Generation: " << gen << "\n";

        int game_num = 1;

        for(int p1 = 0; p1 < agents.size(); p1++)
        {
            for(int p2 = 0; p2 < agents.size(); p2++)
            {
                if(p1 != p2)
                {
    				chess::board::Board b = chess::uci::fen_to_board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/PNBQKBNR w KQkq - 0 1");
                    u8 res = chess::trainer::play_game(b, agents.at(p1), agents.at(p2), calc_depth);
					chess::search::position_history.clear();
                    
                    std::cout << "Game #" << game_num << "(#" << p1 << " vs #" << p2 << "): ";
                    if(res == P1_WIN)
					{
						agents.at(p1).score += 10;
						agents.at(p2).score -= 3;
                        std::cout << "1 - 0\n";
					}
                    else if(res == P2_WIN)
					{
						agents.at(p2).score += 10;
						agents.at(p1).score -= 3;
                        std::cout << "0 - 1\n";
					}
                    else
					{
						agents.at(p1).score += 5;
						agents.at(p1).score += 5;
                        std::cout << "1/2 - 1/2\n";
					}
                }

                game_num++;
            }
        }

		std::cout << "\nGENERATION SCORE\nAGENT\tSCORE\n";
		for(int i = 0; i < agents.size(); i++)
		{
			std::cout << "#" << i << ":\t" << agents.at(i).score << "\n";
		}

		std::sort(agents.begin(), agents.end(), chess::trainer::compare_score);
		for(int i = 0; i < agents.size() - survivors; i++)
		{
			agents.erase(agents.begin());
		}
		std::cout << "\nSURVIVORS (" << agents.size() << ")\n";
		for(int i = 0; i < agents.size(); i++)
		{
			std::cout << "#" << i << ":\t" << agents.at(i).score << "\n";
			agents.at(i).score = 0;
		}

		// Breed
    	std::vector<chess::trainer::AgentScore> best_agents = agents;
		for(int i = 0; i < agents_per_generation - best_agents.size(); i++)
		{
			agents.emplace_back(chess::trainer::breed_agents(best_agents.at(rand() % best_agents.size()), best_agents.at(rand() % best_agents.size()), mutation_range));
		}

		std::cout << "Created " << (agents_per_generation - best_agents.size()) << " agents (now " << agents.size() << ")\n";
    }
}
