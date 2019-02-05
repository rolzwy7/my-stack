#include "vector3d.h"

namespace engine {
	namespace math {

		vector3d::vector3d() {
			x = y = z = 0.0f;
		}
		vector3d::vector3d(const float & x, const float & y, const float & z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		vector3d & vector3d::add(const vector3d & other) {
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			return *this;
		}
		vector3d & vector3d::sub(const vector3d & other) {
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			return *this;
		}
		vector3d & vector3d::mul(const vector3d & other) {
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;
			return *this;
		}
		vector3d & vector3d::div(const vector3d & other) {
			if ((other.x != 0) && (other.y != 0) && (other.z != 0)) {
				this->x /= other.x;
				this->y /= other.y;
				this->z /= other.z;
			}
			else {
				std::cout << "[math/vector3d] ZeroDivision (" << *this << ")" << std::endl;
			}
			return *this;
		}

		std::ostream & operator<<(std::ostream & stream, const vector3d & vector) {
			stream << "vector3d(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
			return stream;
		}

		vector3d operator+(vector3d left, const vector3d & right) {
			return left.add(right);
		}
		vector3d operator-(vector3d left, const vector3d & right) {
			return left.sub(right);
		}
		vector3d operator*(vector3d left, const vector3d & right) {
			return left.mul(right);
		}
		vector3d operator/(vector3d left, const vector3d & right) {
			return left.div(right);
		}

		vector3d & operator+=(vector3d & left, const vector3d & right) {
			return left.add(right);
		}
		vector3d & operator-=(vector3d & left, const vector3d & right) {
			return left.sub(right);
		}
		vector3d & operator*=(vector3d & left, const vector3d & right) {
			return left.mul(right);
		}
		vector3d & operator/=(vector3d & left, const vector3d & right) {
			return left.div(right);
		}

		bool operator==(vector3d & left, const vector3d & right) {
			return (left.x == right.x)
				&& (left.y == right.y)
				&& (left.z == right.z);
		}

		bool operator!=(vector3d & left, const vector3d & right) {
			return !(left == right);
		}

	} // namespace math 
} // namespace engine
