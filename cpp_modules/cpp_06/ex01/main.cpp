#include <stdint.h>
#include <iostream>

typedef struct s_data {
	int i;
}	Data;

uintptr_t serialize(Data* ptr) {
	return reinterpret_cast<uintptr_t>(ptr);
}

Data* deserialize(uintptr_t raw) {
	return reinterpret_cast<Data *>(raw);
}

int main(void) {
	Data *d = new Data;
	Data *d2;
	uintptr_t num;

	d->i = 10;
	std::cout << d->i << std::endl;
	num = serialize(d);
	d2 = deserialize(num);
	std::cout << d2->i << std::endl;
	delete d;
	return 0;
}
