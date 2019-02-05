#include "vector4d.h"

namespace engine {
	namespace math {

		vector4d::vector4d() {
			x = y = z = w = 0.0f;
		}

		vector4d::vector4d(const float & x, const float & y, const float & z, const float & w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		vector4d & vector4d::add(const vector4d & other) {
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			this->w += other.w;
			return *this;
		}
		vector4d & vector4d::sub(const vector4d & other) {
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			this->w -= other.w;
			return *this;
		}
		vector4d & vector4d::mul(const vector4d & other) {
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;
			this->w *= other.w;
			return *this;
		}
		vector4d & vector4d::div(const vector4d & other) {
			if ((other.x != 0) && (other.y != 0) && (other.z != 0) && (other.w != 0)) {
				this->x /= other.x;
				this->y /= other.y;
				this->z /= other.z;
				this->w /= other.w;
			}
			else {
				std::cout << "[math/vector4d] ZeroDivision (" << *this << ")" << std::endl;
			}
			return *this;
		}

		std::ostream & operator<<(std::ostream & stream, const vector4d & vector) {
			stream << "vector4d(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
			return stream;
		}

		vector4d operator+(vector4d left, const vector4d & right) {
			return left.add(right);
		}
		vector4d operator-(vector4d left, const vector4d & right) {
			return left.sub(right);
		}
		vector4d operator*(vector4d left, const vector4d & right) {
			return left.mul(right);
		}
		vector4d operator/(vector4d left, const vector4d & right) {
			return left.div(right);
		}

		vector4d & operator+=(vector4d & left, const vector4d & right) {
			return left.add(right);
		}
		vector4d & operator-=(vector4d & left, const vector4d & right) {
			return left.sub(right);
		}
		vector4d & operator*=(vector4d & left, const vector4d & right) {
			return left.mul(right);
		}
		vector4d & operator/=(vector4d & left, const vector4d & right) {
			return left.div(right);
		}

		bool operator==(vector4d & left, const vector4d & right) {
			return (left.x == right.x)
				&& (left.y == right.y)
				&& (left.z == right.z)
				&& (left.w == right.w);
		}

		bool operator!=(vector4d & left, const vector4d & right) {
			return !(left == right);
		}

	} // namespace math 
} // namespace engine
