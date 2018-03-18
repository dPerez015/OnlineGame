#pragma once
#include <random>
#include <cmath>
#include "intergerPos.h"

class cofre {

public:
	intergerPosition pos;

	int open() {
		return floor(rand() * 4 / RAND_MAX);
	}
};