#include "../include/uci.h"

chess::board::Board chess::uci::fen_to_board(std::string fen)
{
    chess::board::Board board = EMPTY_BOARD;
    u8 square = 63;
    for(int i = 0; i < fen.length(); ++i)
    {
        switch(fen[i])
        {
            case 'p':
            PUT_PIECE(board, PB, square);
            square--;
            break;

            case 'n':
            PUT_PIECE(board, NB, square);
            square--;
            break;

            case 'b':
            PUT_PIECE(board, BB, square);
            square--;
            break;

            case 'r':
            PUT_PIECE(board, RB, square);
            square--;
            break;

            case 'q':
            PUT_PIECE(board, QB, square);
            square--;
            break;

            case 'k':
            PUT_PIECE(board, KB, square);
            square--;
            break;

            case 'P':
            PUT_PIECE(board, PW, square);
            square--;
            break;

            case 'N':
            PUT_PIECE(board, NW, square);
            square--;
            break;

            case 'B':
            PUT_PIECE(board, BW, square);
            square--;
            break;

            case 'R':
            PUT_PIECE(board, RW, square);
            square--;
            break;

            case 'Q':
            PUT_PIECE(board, QW, square);
            square--;
            break;

            case 'K':
            PUT_PIECE(board, KW, square);
            square--;
            break;

            default:
            if((int)(fen[i]) > 48 && (int)(fen[i]) < 57)
            {
                square -= (fen[i]-48);
            }
            break;
        }
    }
    return board;
}
