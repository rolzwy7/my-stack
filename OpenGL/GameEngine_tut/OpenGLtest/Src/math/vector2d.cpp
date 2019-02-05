#include "vector2d.h"

namespace engine {
	namespace math {

		vector2d::vector2d() {
			x = y = 0.0f;
		}
		vector2d::vector2d(const float & x, const float & y) {
			this->x = x;
			this->y = y;
		}

		vector2d & vector2d::add(const vector2d & other) {
			this->x += other.x;
			this->y += other.y;
			return *this;
		}
		vector2d & vector2d::sub(const vector2d & other) {
			this->x -= other.x;
			this->y -= other.y;
			return *this;
		}
		vector2d & vector2d::mul(const vector2d & other) {
			this->x *= other.x;
			this->y *= other.y;
			return *this;
		}
		vector2d & vector2d::div(const vector2d & other) {
			if ((other.x != 0) && (other.y != 0)) {
				this->x /= other.x;
				this->y /= other.y;
			}
			else {
				std::cout << "[math/vector2d] ZeroDivision (" << *this << ")" << std::endl;
			}
			return *this;
		}

		std::ostream & operator<<(std::ostream & stream, const vector2d & vector) {
			stream << "vector2d(" << vector.x << ", " << vector.y << ")";
			return stream;
		}

		vector2d operator+(vector2d left, const vector2d & right) {
			return left.add(right);
		}
		vector2d operator-(vector2d left, const vector2d & right) {
			return left.sub(right);
		}
		vector2d operator*(vector2d left, const vector2d & right) {
			return left.mul(right);
		}
		vector2d operator/(vector2d left, const vector2d & right) {
			return left.div(right);
		}

		vector2d & operator+=(vector2d & left, const vector2d & right) {
			return left.add(right);
		}
		vector2d & operator-=(vector2d & left, const vector2d & right) {
			return left.sub(right);
		}
		vector2d & operator*=(vector2d & left, const vector2d & right) {
			return left.mul(right);
		}
		vector2d & operator/=(vector2d & left, const vector2d & right) {
			return left.div(right);
		}

		bool operator==(vector2d & left, const vector2d & right) {
			return (left.x == right.x)
				&& (left.y == right.y);
		}

		bool operator!=(vector2d & left, const vector2d & right) {
			return !(left == right);
		}

	} // namespace math 
} // namespace engine
