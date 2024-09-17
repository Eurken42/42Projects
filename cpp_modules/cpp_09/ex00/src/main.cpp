#include "../header/BitcoinExchange.class.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error, could not open file." << std::endl;
		exit(1);
	}

	BitcoinExchange	converter(argv[1]);
	return (0);
}
