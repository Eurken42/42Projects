#include "../header/PmergeMe.class.hpp"

int main(int argc, char **argv)
{
	if (argc < 3 || argc > 3002)
	{
		std::cout << "Error: invalid arguments." << std::endl;
		exit(-1);
	}
	PmergeMe	sorting(argv);
	return (0);
}

