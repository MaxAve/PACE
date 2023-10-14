#include <iostream>
#include "board.h"

namespace chess
{
    namespace uci
    {
        /* Converts a FEN string into a Board representation */
        board::Board fen_to_board(std::string fen);
    }
}