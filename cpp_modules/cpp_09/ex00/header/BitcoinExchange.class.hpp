#ifndef BITCOINEXCHANGE_CLASS_HPP
# define BITCOINEXCHANGE_CLASS_HPP

#include <iostream>
#include <iomanip>
#include <map>
#include <cstdlib>
#include <fstream>
#include <sstream>

class BitcoinExchange
{
	private:
		
		const std::string	inputFile;
		std::map<std::string, float>ratesMap;

		void	readDB();
		void	printMap();
		void	fillMap(std::string	line);

		void	parsingFile();
		int		checkDelim(std::string line);
		int		checkDate(std::string date);
		int		checkYear(std::string year);
		int		checkMonth(std::string month);
		int		checkDay(std::string day);
		void	findDate(std::string date, float val);
		std::string	decreaseDate(std::string date);
		float	checkValue(std::string value);
		void	compareDates(std::string line);

		void	error(std::string type);

	public:

		int	getBitcoinExchange(void) const;

		BitcoinExchange(void);
		BitcoinExchange(std::string inputFile);
		BitcoinExchange(BitcoinExchange const &src);
		BitcoinExchange&	operator=(BitcoinExchange const &assign);
		~BitcoinExchange(void);
};

#endif

