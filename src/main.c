#include <stdio.h>
#include <stdlib.h>
#include <types.h>
#include <board.h>

int main(int argc, char** argv)
{
    Board b = STANDARD_BOARD;
    PUT_PIECE(b, 7, 16);
    print_board(b);
    return 0;
}
