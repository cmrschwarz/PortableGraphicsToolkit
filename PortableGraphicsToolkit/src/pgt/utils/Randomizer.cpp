#include "Randomizer.h"
#include <cstdlib>
#include <time.h>   
namespace pgt {

Randomizer::Randomizer() {
	_numbers = new ushort[SIZE];
	std::srand(32367);
	for (int i = 0; i < SIZE; i++) {
		_numbers[i] = std::rand();
	}
	
}
Randomizer::~Randomizer() {
	delete[] _numbers;
}
float Randomizer::rnd(int seed) {
	return (float)(_numbers[seed%SIZE]) / RAND_MAX;
}
}