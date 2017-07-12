#include "maths.h"


namespace pgt {

float toRadians(float degrees) {
	return degrees / 180.0f * (float)(M_PI);
}

}