#include <stdio.h>
#include <stdlib.h>
#include <types.h>
#include <board.h>

int main(int argc, char** argv)
{
    Board b = {{0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL, 0ULL}, 0};
    PUT_PIECE(b, 1, 12);
    print_board(b, false);
    
    return 0;
}
