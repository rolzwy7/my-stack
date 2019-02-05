#include "angles.h"

namespace engine {
	namespace math {
		float to_radians(float degrees) {
			return degrees * (M_PI / 180.0f);
		}
		float to_degrees(float radians) {
			return 180.0f * (radians / M_PI);
		}
	} // namespace math
} // namespace engine



