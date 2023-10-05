#include "../include/board.h"

void chess::board::print_board(chess::board::Board board, u64 mask)
{
    const char *piece_chars = "pnbrqkPNBRQK";
    for(char i = 63; i >= 0; --i)
    {
        bool has_piece = false;
        for(u8 j = 0; j < 12; ++j)
        {
            if(board.bitboards[j] & (1ULL << i))
            {
                std::cout << piece_chars[j];
                has_piece = true;
            }
        }
        if(!has_piece)
        {
            std::cout << ".";
        }
        if(mask & (1ULL << i))
        {
            std::cout << "*";
        }
        else {
            std::cout << " ";
        }
        if((i) % 8 == 0)
        {
            std::cout << "\n";
        }
    }
}
