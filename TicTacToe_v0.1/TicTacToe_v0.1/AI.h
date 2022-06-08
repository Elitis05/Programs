#pragma once

#include <tuple>

#include "miniMax.h"

class AI {
private:
	int searchCount;

public:
	AI(void);
	int searchPos(board &Board);
	int getSearchCount();
	void initSearchCount();
};