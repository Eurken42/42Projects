#include <iostream>
#include "A.class.hpp"
#include "B.class.hpp"
#include "C.class.hpp"

Base *generate(void) {
	srand(time(NULL));
	int randNum = (rand() % 3) + 1;

	if (randNum == 1)
		return new A;
	else if (randNum == 2)
		return new B;
	else 
		return new C;
}

void identify(Base *p) {
	A *a;
	a = dynamic_cast<A *>(p);
	if (a)
		std::cout << "A" << std::endl;
	else {
		B *b;
		b = dynamic_cast<B *>(p);
		if (b)
			std::cout << "B" << std::endl;
		else {
			C *c;
			c = dynamic_cast<C *>(p);
			if (c)
				std::cout << "C" << std::endl;
		}
	}	
}

void identify(Base &p) {
	try {
		A &a = dynamic_cast<A &>(p);
		(void) a;
		std::cout << "A" << std::endl;
	}
	catch (std::exception& e) {
		(void) e;
	}	
	try {
		B &b = dynamic_cast<B &>(p);
		(void) b;
		std::cout << "B" << std::endl;
	}
	catch (std::exception& e) {
		(void) e;
	}
	try {
		C &c = dynamic_cast<C &>(p);
		(void) c;
		std::cout << "C" << std::endl;
	}
	catch (std::exception& e) {
		(void) e;
	}
}

int main(void) {
	Base *t = generate();
	identify(*t);
	delete t;
	t = generate();
	identify(t);
	delete t;
	return 0;
}
