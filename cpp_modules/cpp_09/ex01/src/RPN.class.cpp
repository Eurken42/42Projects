#include "../header/RPN.class.hpp"
#include <cctype>

int RPN::checkOperator(char action)
{
	if (action != '+' && action != '-' && action != '/' && action != '*')
	{
		std::cout << "Error" << std::endl;
		exit (-1);
	}
	return (1);
}

void RPN::singleOperation()
{
	int	operand1, operand2, result;
	char action;

	operand2 = numbers.top();
	numbers.pop();
	operand1 = numbers.top();
	numbers.pop();
	action = stack.top();
	stack.pop();
	switch (action)
	{
		case 42:
			result = operand1 * operand2;
			break;
		case 43:
			result = operand1 + operand2;
			break;
		case 45:
			result = operand1 - operand2;
			break;
		case 47:
			result = operand1 / operand2;
			break;
		default:
			std::cout << "Error" << std::endl;
	}
	numbers.push(result);
}

void RPN::fillStack()
{
	int	exp_size = expression.size();	

	if (exp_size < 3)
		exit (-1);
	for (int i = 0; i < exp_size; i++)
	{
		if (expression[i] != ' ')
		{
			if (isdigit(expression[i]) != 0)
				numbers.push(expression[i] - '0');
			else if (checkOperator(expression[i]))
				stack.push(expression[i]);
			if (stack.size() == 1 && numbers.size() >= 2)
				singleOperation();
		}
	}
}

std::string RPN::getExpression(void) const
{
	return (this->expression);
}

RPN::RPN(std::string input) : expression(input)
{
	fillStack();
	if (!numbers.empty())
		std::cout << numbers.top() << std::endl;
	return ;
}

RPN::RPN(RPN const &src)
{
	*this = src;
	return ;
}

RPN &	RPN::operator=(const RPN &assign)
{
	this->expression = assign.getExpression();
	return (*this);
}

RPN::~RPN(void)
{
	return ;
}
