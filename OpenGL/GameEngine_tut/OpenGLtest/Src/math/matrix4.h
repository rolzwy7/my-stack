#pragma once
#include "math.h"
#include <iostream>

#define MATRIX4_EDGE 4
#define MATRIX4_AREA 16

namespace engine {
	namespace math {

		struct matrix4 {

			union {
				float elements[MATRIX4_AREA];
				vector4d columns[MATRIX4_EDGE];
			};

			matrix4();
			matrix4(float diagonal);

			matrix4 & mul(const matrix4 & other);

			static matrix4 identity();
			static matrix4 orthographic(float left, float right, float top, float bottom, float near, float far);
			static matrix4 perspective(float fov, float aspect_ratio, float near, float far);
			static matrix4 translation(const vector3d & ltranslation);
			static matrix4 rotation(float angle, const vector3d & axis);
			static matrix4 scale(const vector3d & lscale);

			friend matrix4 operator*(matrix4 left, const matrix4 & right);
			friend matrix4 & operator*=(matrix4 & left, const matrix4 & right);

			friend std::ostream & operator<<(std::ostream & stream, const matrix4 & matrix);

			matrix4 & print();

		};

	} // namespace engine
} // namespace math
