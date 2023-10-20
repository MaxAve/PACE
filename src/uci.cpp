#include "../include/uci.h"

u8 chess::uci::chess_square_to_index(std::string square)
{
    u8 index = 0;
    const std::string files = "hgfedcba";
    for(u8 i = 0; i < files.length(); ++i)
    {
        if(files[i] == square[0])
            index += i;
    }
    index += (((char)square[1]-48)*8)-8;
    return index;
}

std::string chess::uci::index_to_chess_square(u8 index)
{
    std::string square = "";
    const std::string files = "hgfedcba";
    square += files[index % 8];
    square += std::to_string(((index - (index % 8)) / 8) + 1);
    return square;
}

chess::board::Board chess::uci::fen_to_board(std::string fen)
{
    chess::board::Board board = EMPTY_BOARD;
    u8 square = 63;
    bool parsing_position = true;
    u8 board_representation_end = 0;
    for(int i = 0; i < fen.length(); ++i)
    {
        if(parsing_position)
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

                case ' ':
                parsing_position = false;
                board_representation_end = i;
                break;

                default:
                if((int)(fen[i]) > 48 && (int)(fen[i]) < 57)
                {
                    square -= (fen[i]-48);
                }
                break;
            }
        }
        else {
            break;
        }
    }
    if(fen[board_representation_end+1] == 'w')
        board.flags |= WHITE_TURN;
    if(fen[board_representation_end+3] != '-')
    {
        for(int i = board_representation_end+3; i < fen.length(); ++i)
        {
            switch(fen[i])
            {
                case 'K':
                board.flags |= WHITE_SHORT_CASTLE;
                break;

                case 'Q':
                board.flags |= WHITE_LONG_CASTLE;
                break;

                case 'k':
                board.flags |= BLACK_SHORT_CASTLE;
                break;

                case 'q':
                board.flags |= BLACK_LONG_CASTLE;
                break;
            }
        }
    }
    return board;
}
