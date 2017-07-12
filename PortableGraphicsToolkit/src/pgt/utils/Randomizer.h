#pragma once
#include "primitives.h"
namespace pgt {
class Randomizer {
private:
	static const int SIZE = 0xFFFF;
	ushort* _numbers;
public: 
	Randomizer();
	~Randomizer();
	float rnd(int seed);
};
};