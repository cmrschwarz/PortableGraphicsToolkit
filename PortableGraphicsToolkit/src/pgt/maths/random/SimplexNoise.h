#pragma once

#include <cstddef>  // size_t

namespace pgt {
class SimplexNoise {
public:
	// 2D Perlin simplex noise
	static float noise(float x, float y);
};

};