#include <iostream>

#if _DEBUG
#include <windows.h>
#endif


namespace vec {

	struct Vector2d {
		float x, y;

		Vector2d() {
			x = y = 0.0f;
		}

		Vector2d(float x, float y) {
			this->x = x;
			this->y = y;
		}

		friend float dot(const Vector2d & A, const Vector2d & B) {
			return (A.x * B.x) + (A.y * B.y);
		}

		friend float operator&(const Vector2d & left, const Vector2d & right) {
			return dot(left, right);
		};

		Vector2d & add(const Vector2d & other) {
			this->x += other.x;
			this->y += other.y;
			return *this;
		};
		Vector2d & sub(const Vector2d & other) {
			this->x -= other.x;
			this->y -= other.y;
			return *this;
		};
		Vector2d & mul(const Vector2d & other) {
			this->x *= other.x;
			this->y *= other.y;
			return *this;
		};
		Vector2d & div(const Vector2d & other) {
			this->x /= other.x;
			this->y /= other.y;
			return *this;
		};

		friend Vector2d operator+(Vector2d left, const Vector2d & right) {
			return left.add(right);
		}
		friend Vector2d operator-(Vector2d left, const Vector2d & right) {
			return left.sub(right);
		}
		friend Vector2d operator*(Vector2d left, const Vector2d & right) {
			return left.mul(right);
		}
		friend Vector2d operator/(Vector2d left, const Vector2d & right) {
			return left.div(right);
		}

		friend void operator+=(Vector2d & left, const Vector2d & right) {
			left.add(right);
		}
		friend void operator-=(Vector2d & left, const Vector2d & right) {
			left.sub(right);
		}
		friend void operator*=(Vector2d & left, const Vector2d & right) {
			left.mul(right);
		}
		friend void operator/=(Vector2d & left, const Vector2d & right) {
			left.div(right);
		}

		friend std::ostream & operator<<(std::ostream & stream, const Vector2d & vector) {
			stream << "Vector2d(" << vector.x << "," << vector.y << ")";
			return stream;
		}

	};

} // namespace vec


int main(int argc, char *argv[]) {
	using namespace vec;
	
	Vector2d a(5.0f, 10.0f);
	Vector2d b(5.0f, 10.0f);


	std::cout << "dot " << (a & b) << std::endl;

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << "+ " << a + b << std::endl;
	std::cout << "- " << a - b << std::endl;
	std::cout << "* " << a * b << std::endl;
	std::cout << "/ " << a / b << std::endl;
	

	#if _DEBUG
	std::cout << "\n\n";
	system("pause");
	#endif
}