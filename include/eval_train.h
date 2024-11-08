#pragma once

#include <iostream>
#include <vector>
#include "types.h"
#include "board.h"
#include "eval.h"
#include "moves.h"
#include "uci.h"

#define DRAW   0
#define P1_WIN 1
#define P2_WIN 2

namespace chess
{
namespace trainer
{
typedef struct
{
    int score;
    int pst[12][64];
} AgentScore;

u8 play_game(AgentScore &p1, AgentScore &p2, int depth);

void train_pst(int generations, int agents_per_generation, int mutation_range, int calc_depth); /* Train piece-square tables */
} // namespace trainer
} // namespace chess
