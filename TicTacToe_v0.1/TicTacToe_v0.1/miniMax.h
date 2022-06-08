#pragma once

#include <stdlib.h>
#include <time.h>

#include <tuple>
#include <vector>

#include "board.h"
#include "evaluate.h"

std::tuple<int, int> minimax(board& Board, int depth, int* searchCount);

std::tuple<int, int> minimize(board& Board, int depth, int* searchCount);

std::tuple<int, int> maximize(board& Board, int depth, int* searchCount);