#include <board.h>

void print_board(Board board, bool show_extra)
{
    const char *piece_chars = "pPnNbBrRqQkK";
    for(u8 i = 0; i < 64; ++i)
    {
        bool has_piece = false;
        for(u8 j = 0; j < 12; ++j)
        {
            if(board.bitboards[j] & (1ULL << i))
            {
                printf("%c ", piece_chars[j]);
                has_piece = true;
            }
        }
        if(!has_piece)
        {
            printf(". ");
        }
        if((i + 1) % 8 == 0)
        {
            printf("\n");
        }
    }
}
