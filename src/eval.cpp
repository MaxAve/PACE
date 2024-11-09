#include "../include/eval.h"

int chess::eval::eval_pst(const board::Board &b)
{
    int eval = 0;
    for(u8 i = 0; i < 6; ++i)
    {
        for(u8 j = 0; j < 64; ++j)
        {
            if(b.bitboards[i] & (1ULL << j))
            {
                eval -= piece_square_tables[i][j];
            }
        }
    }
    for(u8 i = 6; i < 12; ++i)
    {
        for(u8 j = 0; j < 64; ++j)
        {
            if(b.bitboards[i] & (1ULL << j))
            {
                eval += piece_square_tables[i-6][63-j];
            }
        }
    }
    return eval;
}

int chess::eval::get_material_diff(const board::Board &board, int p, int n, int b, int r, int q, int k)
{
	int eval = 0;
	for(int i = 0; i < 64; i++)
	{
		if(board.bitboards[PW] & (1ULL << i))
			eval += p;
		if(board.bitboards[NW] & (1ULL << i))
			eval += n;
		if(board.bitboards[BW] & (1ULL << i))
			eval += b;
		if(board.bitboards[RW] & (1ULL << i))
			eval += r;
		if(board.bitboards[QW] & (1ULL << i))
			eval += q;
		if(board.bitboards[KW] & (1ULL << i))
			eval += k;
		if(board.bitboards[PB] & (1ULL << i))
			eval -= p;
		if(board.bitboards[NB] & (1ULL << i))
			eval -= n;
		if(board.bitboards[BB] & (1ULL << i))
			eval -= b;
		if(board.bitboards[RB] & (1ULL << i))
			eval -= r;
		if(board.bitboards[QB] & (1ULL << i))
			eval -= q;
		if(board.bitboards[KB] & (1ULL << i))
			eval -= k;
	}
	return eval;
}

bool chess::eval::is_draw(const chess::board::Board &b,
                          const std::unordered_map<u64, u8> &position_history,
                          u64 white_pieces_bb,
                          u64 black_pieces_bb)
{
    // Threefold repetition
    for(auto &position : position_history)
    {
        if(position.second > 2)
        {
            return true;
        }
    }

    // Stalemate
    if(b.flags & WHITE_TURN)
    {
        // Check for any legal moves when its white's turn
        for(int i = 6; i < 12; ++i)
        {
            for(int j = 0; j < 64; ++j)
            {
                if(chess::moves::get_attack_bitboard(i, white_pieces_bb, black_pieces_bb, white_pieces_bb | black_pieces_bb, j) != 0)
                {
                    return false;
                }
            }
        }
    }
    else
    {
        // Check for any legal mvoes when its black's turn
        for(int i = 0; i < 6; ++i)
        {
            for(int j = 0; j < 64; ++j)
            {
                if(chess::moves::get_attack_bitboard(i, white_pieces_bb, black_pieces_bb, white_pieces_bb | black_pieces_bb, j) != 0)
                {
                    return false;
                }
            }
        }
    }

    return true; // There must be a stalemate
}
