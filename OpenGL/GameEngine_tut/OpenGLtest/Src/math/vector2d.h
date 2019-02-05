#pragma once

#include <iostream>

namespace engine { 
	namespace math {
	
		struct vector2d {
			float x;
			float y;

			vector2d();
			vector2d(const float & x, const float & y);

			vector2d & add(const vector2d & other);
			vector2d & sub(const vector2d & other);
			vector2d & mul(const vector2d & other);
			vector2d & div(const vector2d & other);

			friend std::ostream & operator<<(std::ostream & stream, const vector2d & vector);

			friend vector2d operator+(vector2d left, const vector2d & right);
			friend vector2d operator-(vector2d left, const vector2d & right);
			friend vector2d operator*(vector2d left, const vector2d & right);
			friend vector2d operator/(vector2d left, const vector2d & right);

			friend vector2d & operator+=(vector2d & left, const vector2d & right);
			friend vector2d & operator-=(vector2d & left, const vector2d & right);
			friend vector2d & operator*=(vector2d & left, const vector2d & right);
			friend vector2d & operator/=(vector2d & left, const vector2d & right);

			friend bool operator==(vector2d & left, const vector2d & right);
			friend bool operator!=(vector2d & left, const vector2d & right);



		};
	

	} // namespace math 
} // namespace engine