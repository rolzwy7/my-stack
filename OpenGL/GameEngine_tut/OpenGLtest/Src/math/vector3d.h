#pragma once

#include <iostream>

namespace engine { 
	namespace math {
	
		struct vector3d {
			float x;
			float y;
			float z;

			vector3d();
			vector3d(const float & x, const float & y, const float & z);

			vector3d & add(const vector3d & other);
			vector3d & sub(const vector3d & other);
			vector3d & mul(const vector3d & other);
			vector3d & div(const vector3d & other);

			friend std::ostream & operator<<(std::ostream & stream, const vector3d & vector);
			friend vector3d operator+(vector3d left, const vector3d & right);
			friend vector3d operator-(vector3d left, const vector3d & right);
			friend vector3d operator*(vector3d left, const vector3d & right);
			friend vector3d operator/(vector3d left, const vector3d & right);

			friend vector3d & operator+=(vector3d & left, const vector3d & right);
			friend vector3d & operator-=(vector3d & left, const vector3d & right);
			friend vector3d & operator*=(vector3d & left, const vector3d & right);
			friend vector3d & operator/=(vector3d & left, const vector3d & right);

			friend bool operator==(vector3d & left, const vector3d & right);
			friend bool operator!=(vector3d & left, const vector3d & right);



		};
	

	} // namespace math 
} // namespace engine