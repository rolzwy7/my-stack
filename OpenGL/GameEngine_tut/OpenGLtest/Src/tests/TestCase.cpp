#include "TestCase.h"


namespace engine {
	namespace tests {

		TestCase::TestCase() {

		}

		void testVectors() {
			using namespace math;
			using std::cout;
			using std::endl;
			vector2d a2(5.0f, 5.0f);
			vector2d b2(2.0f, 2.0f);
			cout << "\n[logger] Vector2d" << endl;
			cout << "Before A: " << a2 << endl;
			cout << "Before B: " << b2 << endl;
			cout << "A + B: " << a2 + b2 << endl;
			cout << "A - B: " << a2 - b2 << endl;
			cout << "A * B: " << a2 * b2 << endl;
			cout << "A / B: " << a2 / b2 << endl;
			cout << "B / A: " << b2 / a2 << endl;
			cout << "After A: " << a2 << endl;
			cout << "After B: " << b2 << endl;

			vector3d a3(5.0f, 5.0f, 5.0f);
			vector3d b3(2.0f, 2.0f, 2.0f);
			cout << "\n[logger] Vector3d" << endl;
			cout << "Before A: " << a3 << endl;
			cout << "Before B: " << b3 << endl;
			cout << "A + B: " << a3 + b3 << endl;
			cout << "A - B: " << a3 - b3 << endl;
			cout << "A * B: " << a3 * b3 << endl;
			cout << "A / B: " << a3 / b3 << endl;
			cout << "B / A: " << b3 / a3 << endl;
			cout << "After A: " << a3 << endl;
			cout << "After B: " << b3 << endl;

			vector4d a4(5.0f, 5.0f, 5.0f, 5.0f);
			vector4d b4(2.0f, 2.0f, 2.0f, 2.0f);
			cout << "\n[logger] Vector4d" << endl;
			cout << "Before A: " << a4 << endl;
			cout << "Before B: " << b4 << endl;
			cout << "A + B: " << a4 + b4 << endl;
			cout << "A - B: " << a4 - b4 << endl;
			cout << "A * B: " << a4 * b4 << endl;
			cout << "A / B: " << a4 / b4 << endl;
			cout << "B / A: " << b4 / a4 << endl;
			cout << "After A: " << a4 << endl;
			cout << "After B: " << b4 << endl;
		}

	}//namespace tests
} // namespace engine