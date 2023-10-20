#include <iostream>
#include <string>
#include <vector>
#include "moves.h"
#include "board.h"
#include "types.h"

namespace chess
{
    namespace uci
    {
        typedef struct
        {
            std::vector<std::string> moves;
            u8 result;
        } PGN_simplified;

        /* Converts a chess board square to an integer which can be used in bitboards (e.g. e2 -> 11, g5 -> 33, f6 -> 42, etc.) */
        u8 chess_square_to_index(std::string square);

        /* Converts an integer which can be used in bitboards to a chess board square (e.g. 11 -> e2, 33 -> g5, 42 -> f6, etc.) */
        std::string index_to_chess_square(u8 index);

        /* Converts a FEN string into a Board representation */
        board::Board fen_to_board(std::string fen);
    }
}