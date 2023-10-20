#include "../include/board.h"

void chess::board::print_board(chess::board::Board board, bool display_flags, u64 mask)
{
    std::string piece_chars = "pnbrqkPNBRQK";
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
        // bruh
        if(!has_piece && !(mask & (1ULL << i)))
            std::cout << ". ";
        if(!has_piece && (mask & (1ULL << i)))
            std::cout << "* ";
        if(has_piece && !(mask & (1ULL << i)))
            std::cout << " ";
        if(has_piece && (mask & (1ULL << i)))
            std::cout << "*";
        if((i) % 8 == 0)
        {
            std::cout << "\n";
        }
    }
    std::cout << "Flags: ";
    for(int i = 4; i >= 0; --i)
    {
        std::cout << ((board.flags & (1ULL << i)) ? '1' : '0');
    }
    std::cout << "\n";
}
