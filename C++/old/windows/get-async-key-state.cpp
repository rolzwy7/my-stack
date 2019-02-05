#include <iostream>
#include <windows.h>

using namespace std;

int main() {
	SHORT current_key_state = 0;
	bool low_bit;
	bool high_bit;

	while (true) {
		for (int i = 65; i < 90 + 1; ++i) {
			current_key_state = GetAsyncKeyState(i);
			if (current_key_state) {

				high_bit = ((unsigned short)current_key_state >> 15);
				low_bit = current_key_state & 1;
				if (low_bit) {
					cout << (char)i;
				}

			}
		}
	}

    return 0;
}
