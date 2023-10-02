#include <board.h>

void print_board(Board board, u64 mask)
{
    const char *piece_chars = "pnbrqkPNBRQK";
    for(char i = 63; i >= 0; --i)
    {
        bool has_piece = false;
        for(u8 j = 0; j < 12; ++j)
        {
            if(board.bitboards[j] & (1ULL << i))
            {
                printf("%c", piece_chars[j]);
                has_piece = true;
            }
        }
        if(!has_piece)
        {
            printf(".");
        }
        if(mask & (1ULL << i))
        {
            printf("*");
        }
        else {
            printf(" ");
        }
        if((i) % 8 == 0)
        {
            printf("\n");
        }
    }
}
