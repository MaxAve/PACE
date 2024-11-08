#include "../include/gui.h"

void chess::gui::display(const chess::board::Board &b, u64 highlight)
{
    const int screen_width = 14 * 8;
    const int screen_height = 7 * 8;

    u8 colors[screen_height][screen_width];

    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            for(int y2 = 0; y2 < 7; y2++)
            {
                for(int x2 = 0; x2 < 14; x2++)
                {
                    if((y % 2 == 0 && x % 2 == 0 ) || (y % 2 == 1 && x % 2 == 1 ))
                        colors[y * 7 + y2][x * 14 + x2] = 0;
                    else
                        colors[y * 7 + y2][x * 14 + x2] = 1;
                }
            }
        }
    }

    for(char i = 0; i < 64; i++)
    {
        int y = (7 - (i / 8)) * 7;
        int x = (7 - (i % 8)) * 14;

        if(highlight & (1ULL << i))
        {
            for(int y2 = 0; y2 < 7; y2++)
                for(int x2 = 0; x2 < 14; x2++)
                    colors[y + y2][x + x2] = GUI_COLOR_HIGHLIGHT;
        }

        // Juicer
        if(b.bitboards[PW] & (1ULL << i))
        {
            for(int a = 0; a < 3; a++)
            {
                colors[y + 3 + a][x + 5] = GUI_COLOR_WHITE;
                colors[y + 3 + a][x + 6] = GUI_COLOR_WHITE;
                colors[y + 3 + a][x + 7] = GUI_COLOR_WHITE;
                colors[y + 3 + a][x + 8] = GUI_COLOR_WHITE;
            }
            colors[y + 5][x + 4] = GUI_COLOR_WHITE;
            colors[y + 5][x + 9] = GUI_COLOR_WHITE;
            colors[y + 2][x + 6] = GUI_COLOR_WHITE;
            colors[y + 2][x + 7] = GUI_COLOR_WHITE;
        }

        // Knight
        if(b.bitboards[NW] & (1ULL << i))
        {
            for(int a = 0; a < 5; a++)
            {
                colors[y + 1 + a][x + 5] = GUI_COLOR_WHITE;
                colors[y + 1 + a][x + 6] = GUI_COLOR_WHITE;
                colors[y + 1 + a][x + 7] = GUI_COLOR_WHITE;
                colors[y + 1 + a][x + 8] = GUI_COLOR_WHITE;
            }
            colors[y + 2][x + 3] = GUI_COLOR_WHITE;
            colors[y + 2][x + 4] = GUI_COLOR_WHITE;
            colors[y + 1][x + 9] = GUI_COLOR_WHITE;
            colors[y + 2][x + 9] = GUI_COLOR_WHITE;
            colors[y + 3][x + 9] = GUI_COLOR_WHITE;
            colors[y + 5][x + 9] = GUI_COLOR_WHITE;
            colors[y + 5][x + 4] = GUI_COLOR_WHITE;
        }

        // Bishop
        if(b.bitboards[BW] & (1ULL << i))
        {
            for(int a = 0; a < 3; a++)
            {
                colors[y + 3 + a][x + 5] = GUI_COLOR_WHITE;
                colors[y + 3 + a][x + 6] = GUI_COLOR_WHITE;
                colors[y + 3 + a][x + 7] = GUI_COLOR_WHITE;
                colors[y + 3 + a][x + 8] = GUI_COLOR_WHITE;
            }
            colors[y + 5][x + 4] = GUI_COLOR_WHITE;
            colors[y + 5][x + 9] = GUI_COLOR_WHITE;
            colors[y + 3][x + 4] = GUI_COLOR_WHITE;
            colors[y + 3][x + 9] = GUI_COLOR_WHITE;
            colors[y + 3][x + 5] = GUI_COLOR_WHITE;
            colors[y + 2][x + 5] = GUI_COLOR_WHITE;
            colors[y + 2][x + 6] = GUI_COLOR_WHITE;
            colors[y + 2][x + 8] = GUI_COLOR_WHITE;
            colors[y + 1][x + 6] = GUI_COLOR_WHITE;
            colors[y + 1][x + 7] = GUI_COLOR_WHITE;
        }

        // THE ROOOK
        if(b.bitboards[RW] & (1ULL << i))
        {
            for(int a = 0; a < 4; a++)
            {
                colors[y + 2 + a][x + 5] = GUI_COLOR_WHITE;
                colors[y + 2 + a][x + 6] = GUI_COLOR_WHITE;
                colors[y + 2 + a][x + 7] = GUI_COLOR_WHITE;
                colors[y + 2 + a][x + 8] = GUI_COLOR_WHITE;
            }
            colors[y + 5][x + 4] = GUI_COLOR_WHITE;
            colors[y + 5][x + 9] = GUI_COLOR_WHITE;
            colors[y + 2][x + 4] = GUI_COLOR_WHITE;
            colors[y + 2][x + 9] = GUI_COLOR_WHITE;
            colors[y + 1][x + 4] = GUI_COLOR_WHITE;
            colors[y + 1][x + 9] = GUI_COLOR_WHITE;
            colors[y + 1][x + 6] = GUI_COLOR_WHITE;
            colors[y + 1][x + 7] = GUI_COLOR_WHITE;
        }

        // Queen
        if(b.bitboards[QW] & (1ULL << i))
        {
            for(int a = 0; a < 4; a++)
            {
                for(int b = 0; b < 6; b++)
                {
                    colors[y + 2 + a][x + 4 + b] = GUI_COLOR_WHITE;
                }
            }
            colors[y + 5][x + 3] = GUI_COLOR_WHITE;
            colors[y + 5][x + 10] = GUI_COLOR_WHITE;
            colors[y + 3][x + 3] = GUI_COLOR_WHITE;
            colors[y + 3][x + 10] = GUI_COLOR_WHITE;
            colors[y + 2][x + 2] = GUI_COLOR_WHITE;
            colors[y + 2][x + 11] = GUI_COLOR_WHITE;
            colors[y + 1][x + 4] = GUI_COLOR_WHITE;
            colors[y + 1][x + 6] = GUI_COLOR_WHITE;
            colors[y + 1][x + 7] = GUI_COLOR_WHITE;
            colors[y + 1][x + 9] = GUI_COLOR_WHITE;
        }

        // King
        if(b.bitboards[KW] & (1ULL << i))
        {
            for(int a = 0; a < 3; a++)
            {
                for(int b = 0; b < 6; b++)
                {
                    colors[y + 3 + a][x + 4 + b] = GUI_COLOR_WHITE;
                }
            }
            colors[y + 4][x + 3] = GUI_COLOR_WHITE;
            colors[y + 4][x + 10] = GUI_COLOR_WHITE;
            colors[y + 3][x + 3] = GUI_COLOR_WHITE;
            colors[y + 3][x + 2] = GUI_COLOR_WHITE;
            colors[y + 3][x + 10] = GUI_COLOR_WHITE;
            colors[y + 3][x + 11] = GUI_COLOR_WHITE;
            colors[y + 2][x + 3] = GUI_COLOR_WHITE;
            colors[y + 2][x + 4] = GUI_COLOR_WHITE;
            colors[y + 2][x + 5] = GUI_COLOR_WHITE;
            colors[y + 2][x + 8] = GUI_COLOR_WHITE;
            colors[y + 2][x + 9] = GUI_COLOR_WHITE;
            colors[y + 2][x + 10] = GUI_COLOR_WHITE;
            colors[y + 1][x + 6] = GUI_COLOR_WHITE;
            colors[y + 1][x + 7] = GUI_COLOR_WHITE;
        }

        // Juicer
        if(b.bitboards[PB] & (1ULL << i))
        {
            for(int a = 0; a < 3; a++)
            {
                colors[y + 3 + a][x + 5] = GUI_COLOR_BLACK;
                colors[y + 3 + a][x + 6] = GUI_COLOR_BLACK;
                colors[y + 3 + a][x + 7] = GUI_COLOR_BLACK;
                colors[y + 3 + a][x + 8] = GUI_COLOR_BLACK;
            }
            colors[y + 5][x + 4] = GUI_COLOR_BLACK;
            colors[y + 5][x + 9] = GUI_COLOR_BLACK;
            colors[y + 2][x + 6] = GUI_COLOR_BLACK;
            colors[y + 2][x + 7] = GUI_COLOR_BLACK;
        }

        // Knight
        if(b.bitboards[NB] & (1ULL << i))
        {
            for(int a = 0; a < 5; a++)
            {
                colors[y + 1 + a][x + 5] = GUI_COLOR_BLACK;
                colors[y + 1 + a][x + 6] = GUI_COLOR_BLACK;
                colors[y + 1 + a][x + 7] = GUI_COLOR_BLACK;
                colors[y + 1 + a][x + 8] = GUI_COLOR_BLACK;
            }
            colors[y + 2][x + 3] = GUI_COLOR_BLACK;
            colors[y + 2][x + 4] = GUI_COLOR_BLACK;
            colors[y + 1][x + 9] = GUI_COLOR_BLACK;
            colors[y + 2][x + 9] = GUI_COLOR_BLACK;
            colors[y + 3][x + 9] = GUI_COLOR_BLACK;
            colors[y + 5][x + 9] = GUI_COLOR_BLACK;
            colors[y + 5][x + 4] = GUI_COLOR_BLACK;
        }

        // Bishop
        if(b.bitboards[BB] & (1ULL << i))
        {
            for(int a = 0; a < 3; a++)
            {
                colors[y + 3 + a][x + 5] = GUI_COLOR_BLACK;
                colors[y + 3 + a][x + 6] = GUI_COLOR_BLACK;
                colors[y + 3 + a][x + 7] = GUI_COLOR_BLACK;
                colors[y + 3 + a][x + 8] = GUI_COLOR_BLACK;
            }
            colors[y + 5][x + 4] = GUI_COLOR_BLACK;
            colors[y + 5][x + 9] = GUI_COLOR_BLACK;
            colors[y + 3][x + 4] = GUI_COLOR_BLACK;
            colors[y + 3][x + 9] = GUI_COLOR_BLACK;
            colors[y + 3][x + 5] = GUI_COLOR_BLACK;
            colors[y + 2][x + 5] = GUI_COLOR_BLACK;
            colors[y + 2][x + 6] = GUI_COLOR_BLACK;
            colors[y + 2][x + 8] = GUI_COLOR_BLACK;
            colors[y + 1][x + 6] = GUI_COLOR_BLACK;
            colors[y + 1][x + 7] = GUI_COLOR_BLACK;
        }

        // THE ROOOK
        if(b.bitboards[RB] & (1ULL << i))
        {
            for(int a = 0; a < 4; a++)
            {
                colors[y + 2 + a][x + 5] = GUI_COLOR_BLACK;
                colors[y + 2 + a][x + 6] = GUI_COLOR_BLACK;
                colors[y + 2 + a][x + 7] = GUI_COLOR_BLACK;
                colors[y + 2 + a][x + 8] = GUI_COLOR_BLACK;
            }
            colors[y + 5][x + 4] = GUI_COLOR_BLACK;
            colors[y + 5][x + 9] = GUI_COLOR_BLACK;
            colors[y + 2][x + 4] = GUI_COLOR_BLACK;
            colors[y + 2][x + 9] = GUI_COLOR_BLACK;
            colors[y + 1][x + 4] = GUI_COLOR_BLACK;
            colors[y + 1][x + 9] = GUI_COLOR_BLACK;
            colors[y + 1][x + 6] = GUI_COLOR_BLACK;
            colors[y + 1][x + 7] = GUI_COLOR_BLACK;
        }

        // Queen
        if(b.bitboards[QB] & (1ULL << i))
        {
            for(int a = 0; a < 4; a++)
            {
                for(int b = 0; b < 6; b++)
                {
                    colors[y + 2 + a][x + 4 + b] = GUI_COLOR_BLACK;
                }
            }
            colors[y + 5][x + 3] = GUI_COLOR_BLACK;
            colors[y + 5][x + 10] = GUI_COLOR_BLACK;
            colors[y + 3][x + 3] = GUI_COLOR_BLACK;
            colors[y + 3][x + 10] = GUI_COLOR_BLACK;
            colors[y + 2][x + 2] = GUI_COLOR_BLACK;
            colors[y + 2][x + 11] = GUI_COLOR_BLACK;
            colors[y + 1][x + 4] = GUI_COLOR_BLACK;
            colors[y + 1][x + 6] = GUI_COLOR_BLACK;
            colors[y + 1][x + 7] = GUI_COLOR_BLACK;
            colors[y + 1][x + 9] = GUI_COLOR_BLACK;
        }

        // King
        if(b.bitboards[KB] & (1ULL << i))
        {
            for(int a = 0; a < 3; a++)
            {
                for(int b = 0; b < 6; b++)
                {
                    colors[y + 3 + a][x + 4 + b] = GUI_COLOR_BLACK;
                }
            }
            colors[y + 4][x + 3] = GUI_COLOR_BLACK;
            colors[y + 4][x + 10] = GUI_COLOR_BLACK;
            colors[y + 3][x + 3] = GUI_COLOR_BLACK;
            colors[y + 3][x + 2] = GUI_COLOR_BLACK;
            colors[y + 3][x + 10] = GUI_COLOR_BLACK;
            colors[y + 3][x + 11] = GUI_COLOR_BLACK;
            colors[y + 2][x + 3] = GUI_COLOR_BLACK;
            colors[y + 2][x + 4] = GUI_COLOR_BLACK;
            colors[y + 2][x + 5] = GUI_COLOR_BLACK;
            colors[y + 2][x + 8] = GUI_COLOR_BLACK;
            colors[y + 2][x + 9] = GUI_COLOR_BLACK;
            colors[y + 2][x + 10] = GUI_COLOR_BLACK;
            colors[y + 1][x + 6] = GUI_COLOR_BLACK;
            colors[y + 1][x + 7] = GUI_COLOR_BLACK;
        }
    }

    for(int y = 0; y < screen_height; y++)
    {
        for(int x = 0; x < screen_width; x++)
        {
            std::string out = "";
            
            switch(colors[y][x])
            {
                case 0:
                    out = "\033[0;42m \033[0m";
                    break;
                case 1:
                    out = "\033[0;102m \033[0m";
                    break;
                case 2:
                    out = "\033[0;40m \033[0m";
                    break;
                case 3:
                    out = "\033[0;107m \033[0m";
                    break;
                case 4:
                    out = "\033[0;43m \033[0m";
                    break;
                default:
                    out = " ";
                    break;
            }
            std::cout << out;
        }
        if((y % 7) == 3)
            std::cout << " " << y / 7;
        std::cout << "\n";
    }

    std::cout << "      0             1             2             3             4             5             6             7\n";
}
