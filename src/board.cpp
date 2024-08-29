#include "../include/board.h"

u64 chess::board::zobrist_hash(const chess::board::Board &b)
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

void chess::board::print_board(chess::board::Board board, bool display_flags, u64 mask)
{
    std::string piece_chars = "PNBRQKPNBRQK";
    for(char i = 63; i >= 0; --i)
    {
        bool has_piece = false;
        for(u8 j = 0; j < 12; ++j)
        {
            std::string p = "";
            p += (j < 6) ? "\033[33m" : "\033[97m";
            p += piece_chars[j];
            if(board.bitboards[j] & (1ULL << i))
            {
                std::cout << p;
                has_piece = true;
            }
        }
        // bruh
        if(!has_piece && !(mask & (1ULL << i)))
            std::cout << "\033[30m. ";
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
    std::cout << "\n\033[97mPosition flags: ";
    for(int i = 4; i >= 0; --i)
    {
        std::cout << ((board.flags & (1ULL << i)) ? '1' : '0');
    }
    std::cout << "\n\033[97m";
}
