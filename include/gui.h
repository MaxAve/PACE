#pragma once

#include "types.h"
#include "board.h"

#define GUI_COLOR_LIGHT 0
#define GUI_COLOR_DARK 1
#define GUI_COLOR_BLACK 2
#define GUI_COLOR_WHITE 3
#define GUI_COLOR_HIGHLIGHT 4

namespace chess
{
namespace gui
{
void display(const board::Board &b, u64 highlight=0ULL);
} // namespace gui
} // namespace chess