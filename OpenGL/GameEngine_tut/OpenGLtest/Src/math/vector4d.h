#pragma once

#include <iostream>

namespace engine { 
	namespace math {
	
		struct vector4d {
			float x;
			float y;
			float z;
			float w;

			vector4d();
			vector4d(const float & x, const float & y, const float & z, const float & w);

			vector4d & add(const vector4d & other);
			vector4d & sub(const vector4d & other);
			vector4d & mul(const vector4d & other);
			vector4d & div(const vector4d & other);

			friend std::ostream & operator<<(std::ostream & stream, const vector4d & vector);
			friend vector4d operator+(vector4d left, const vector4d & right);
			friend vector4d operator-(vector4d left, const vector4d & right);
			friend vector4d operator*(vector4d left, const vector4d & right);
			friend vector4d operator/(vector4d left, const vector4d & right);

			friend vector4d & operator+=(vector4d & left, const vector4d & right);
			friend vector4d & operator-=(vector4d & left, const vector4d & right);
			friend vector4d & operator*=(vector4d & left, const vector4d & right);
			friend vector4d & operator/=(vector4d & left, const vector4d & right);

			friend bool operator==(vector4d & left, const vector4d & right);
			friend bool operator!=(vector4d & left, const vector4d & right);



		};
	

	} // namespace math 
} // namespace engine