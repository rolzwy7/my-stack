#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main() {
    string a = "abcDEF";
    string b = "123";
    regex reg1("^[a-zA-Z]+$");
    cmatch m;
    bool res;
    res = regex_match(a.c_str(), m, reg1);
    cout << a << " = " << res << endl;

    res = regex_match(b.c_str(), m, reg1);
    cout << b << " = " << res << endl;

    return 0;
}
