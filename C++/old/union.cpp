#include <iostream>

using namespace std;

/*
"The memory occupied by a union will be large enough to hold the largest member of the union."
*/

union Person {
    int id;
    int age;
};


int main() {

    Person p;

    p.id = 5;
    p.age = 17;

    cout << p.id << endl;  // 17
    cout << p.age << endl; // 17

    return 0;
}
