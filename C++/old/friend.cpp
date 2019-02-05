#include <string>
#include <sstream>
#include <iostream>

#if _DEBUG
	#include <windows.h>
#endif // _DEBUG



class A {
private: 
	int m_priv;
public:
	A(int priv) { 
		this->m_priv = priv;
	};
	friend void printPrivate(A* ptr);
};

void printPrivate(A *ptr) {
	ptr->m_priv++;
	std::cout << "[*] I can see and modify your private members \\( ;-;)/" << std::endl;
	std::cout << ptr->m_priv << std::endl;
}


int main(int argc, char* argv[]) {

	A* ptr = new A(15);

	printPrivate(ptr);
	printPrivate(ptr);

	delete ptr;

	#if _DEBUG
		std::cout << std::endl;
		system("pause");
	#endif // _DEBUG
	return 0;
}
