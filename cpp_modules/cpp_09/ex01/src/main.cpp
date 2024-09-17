#include "../header/RPN.class.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error: Incorrect amount of arguments." << std::endl;
		return (-1);
	}
	RPN	calculator(argv[1]);
	return (0);
}

