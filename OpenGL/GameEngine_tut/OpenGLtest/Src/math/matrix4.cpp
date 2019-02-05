#include "matrix4.h"


namespace engine {
	namespace math {

		matrix4::matrix4() {
			for (int i = 0; i < MATRIX4_AREA; ++i) {
				elements[i] = 0.0f;
			}
		}

		matrix4::matrix4(float diagonal) {
			for (int i = 0; i < MATRIX4_AREA; ++i) {
				elements[i] = 0.0f;
			}
			for (int i = 0; i < MATRIX4_EDGE; ++i) {
				elements[i + i * MATRIX4_EDGE] = diagonal;
			}
		}

		matrix4 & matrix4::mul(const matrix4 & other) { 
			float sum;
			//matrix4 tmp;
			for (int i = 0; i < MATRIX4_EDGE; ++i) {
				for (int j = 0; j < MATRIX4_EDGE; ++j) {
					sum = 0.0f;
					for (int k = 0; k < MATRIX4_EDGE; ++k) {
						sum += elements[i + k * 4] * other.elements[k + j * 4];
					}
					//tmp.elements[i + j * 4] = sum;
					elements[i + j * 4] = sum;
				}
			}
			// *this = tmp;
			return *this;
		}

		matrix4 matrix4::identity() {
			return matrix4(1.0f);
		}
		matrix4 matrix4::orthographic(float left, float right, float top, float bottom, float near, float far) {
			matrix4 ret(1.0f);
			ret.elements[0 + 0 * MATRIX4_EDGE] = 2.0f/(right-left);
			ret.elements[1 + 1 * MATRIX4_EDGE] = 2.0f/(top-bottom);
			ret.elements[2 + 2 * MATRIX4_EDGE] = -2.0f / (far - near);
			ret.elements[3 + 3 * MATRIX4_EDGE] = 1.0f;
			ret.elements[0 + 3 * MATRIX4_EDGE] = -((right + left) / (right - left));
			ret.elements[1 + 3 * MATRIX4_EDGE] = -((top + bottom) / (top - bottom));
			ret.elements[2 + 3 * MATRIX4_EDGE] = -((far + near) / (far - near));
			return ret;
		}

		matrix4 matrix4::perspective(float fov, float aspect_ratio, float near, float far) {
			matrix4 ret;
			ret.elements[0 + 0 * MATRIX4_EDGE] = 1.0f/(aspect_ratio * tan( to_radians(fov / 2.0f) ));
			ret.elements[1 + 1 * MATRIX4_EDGE] = 1.0f/(tan( to_radians(fov / 2.0f) ));
			ret.elements[2 + 2 * MATRIX4_EDGE] = -((far + near)/(far - near));
			ret.elements[3 + 2 * MATRIX4_EDGE] = -1.0f;
			ret.elements[2 + 3 * MATRIX4_EDGE] = -((2.0f * far * near)/(far - near));
			return ret;
		}

		matrix4 matrix4::translation(const vector3d & ltranslation) {
			matrix4 ret(1.0f);
			ret.elements[0 + 3 * MATRIX4_EDGE] = ltranslation.x;
			ret.elements[1 + 3 * MATRIX4_EDGE] = ltranslation.y;
			ret.elements[2 + 3 * MATRIX4_EDGE] = ltranslation.z;
			return ret;
		}

		matrix4 matrix4::rotation(float angle, const vector3d & axis) {
			matrix4 ret(1.0f);
			float r = to_radians(angle);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f -c;
			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			ret.elements[0 + 0 * MATRIX4_EDGE] = x * omc + c;
			ret.elements[1 + 0 * MATRIX4_EDGE] = y * x * omc + z * s;
			ret.elements[2 + 0 * MATRIX4_EDGE] = x * z * omc - y * s;
								 
			ret.elements[0 + 1 * MATRIX4_EDGE] = x * y * omc - z * s;
			ret.elements[1 + 1 * MATRIX4_EDGE] = y * omc + c;
			ret.elements[2 + 1 * MATRIX4_EDGE] = y * z * omc + x * s;
								 
			ret.elements[0 + 2 * MATRIX4_EDGE] = x * z * omc + y * s;
			ret.elements[1 + 2 * MATRIX4_EDGE] = y * z * omc - x * s;
			ret.elements[2 + 2 * MATRIX4_EDGE] = z * omc + c;

			return ret;
		}

		matrix4 matrix4::scale(const vector3d & lscale) {
			matrix4 ret(1.0f);
			ret.elements[0 + 0 * MATRIX4_EDGE] = lscale.x;
			ret.elements[1 + 1 * MATRIX4_EDGE] = lscale.y;
			ret.elements[2 + 2 * MATRIX4_EDGE] = lscale.z;
			return ret;
		}

		matrix4 operator*(matrix4 left, const matrix4 & right) {
			return left.mul(right);
		}

		matrix4 & operator*=(matrix4 & left, const matrix4 & right) {
			return left.mul(right);
		}

		std::ostream & operator<<(std::ostream & stream, const matrix4 & matrix) {
			stream << " - Printing matrix " << MATRIX4_EDGE << ":" << std::endl;
			for (int r = 0; r < MATRIX4_EDGE; ++r) {
				for (int c = 0; c < MATRIX4_EDGE; ++c) {
					stream << matrix.elements[r + c * MATRIX4_EDGE];
					stream << " ";
				}
				stream << std::endl;
			}
			return stream;
		}

		matrix4 & matrix4::print() {
			for (int r = 0; r < MATRIX4_EDGE; ++r) {
				for (int c = 0; c < MATRIX4_EDGE; ++c) {
					std::cout << elements[r + c * MATRIX4_EDGE] << " ";
				}
				std::cout << std::endl;
			}
			return *this;
		};

	}// namespace engine
}// namespace math
