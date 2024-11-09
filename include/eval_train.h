#pragma once

#include <iostream>
#include <vector>
#include "types.h"
#include "board.h"
#include "eval.h"
#include "moves.h"
#include "uci.h"
#include "gui.h"

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
    int pst[6][64];
} AgentScore;

bool compare_score(const AgentScore &a, const AgentScore &b);

extern AgentScore current_games[2];

int eval_pst(const board::Board &b);

u8 play_game(chess::board::Board board, const AgentScore &p1, const AgentScore &p2, int depth);

void train_pst(int generations, int agents_per_generation, int survivors, int mutation_range, int calc_depth); /* Train piece-square tables */
} // namespace trainer
} // namespace chess
