#include "../header/PmergeMe.class.hpp"
#include <cctype>
#include <ctime>
#include <ios>
#include <vector>

void PmergeMe::error()
{
	std::cout << "Error" << std::endl;
	exit(-1);
}

void PmergeMe::printVector(std::vector<int> &v)
{
	std::vector<int>::iterator	it;

	for (it = v.begin(); it != v.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
}

void PmergeMe::printDq(std::deque<int> &d)
{
	std::deque<int>::iterator	it;

	std::cout << "     Deq:";
	for (it = d.begin(); it != d.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
}

void PmergeMe::printArray()
{
	int i = 1;
	std::cout << "Before:";
	while (unsorted[i])
	{
		std::cout << " " << unsorted[i];
		i++;
	}
	std::cout << std::endl;
}

void PmergeMe::parsing()
{
	int	i, j;

	i = 1;
	while (unsorted[i])
	{
		j = 0;
		while (unsorted[i][j])
		{
			if (isdigit(unsorted[i][j]) == 0)
				error();
			j++;
		}
		vec.push_back(atoi(unsorted[i]));
		dq.push_back(atoi(unsorted[i]));
		i++;
	}
	printArray();
}

void PmergeMe::sort()
{
	clock_t	start, finish;
	double	time_v, time_dq;

	std::cout << "After :";
	start = clock();
	sortVector(0, vec.size() - 1);
	finish = clock();
	time_v = ((double) (finish - start)) / CLOCKS_PER_SEC;
	printVector(vec);

	start = clock();
	sortDq(0, dq.size() - 1);
	finish = clock();
	time_dq = ((double) (finish - start)) / CLOCKS_PER_SEC;

	std::cout << "Time to process a range of " << vec.size() << " elements with std::vector is: " << std::fixed << time_v  << std::endl;
	std::cout << "Time to process a range of " << dq.size() << " elements with std::deque is: " << std::fixed << time_dq  << std::endl;

	return ;	
}

void PmergeMe::insertionVector(int beg, int end)
{
	for (int i = beg; i < end; i++)
	{
		int temp = vec[i + 1];
		int	j = i + 1;
		while (j > beg && vec[j - 1] > temp)
		{
			vec[j] = vec[j - 1];
			j--;
		}
		vec[j] = temp;
	}
}

void PmergeMe::insertionDq(int beg, int end)
{
	for (int i = beg; i < end; i++)
	{
		int temp = dq[i + 1];
		int	j = i + 1;
		while (j > beg && dq[j - 1] > temp)
		{
			dq[j] = dq[j - 1];
			j--;
		}
		dq[j] = temp;
	}
}

void PmergeMe::mergeVector(int beg, int mid, int end)
{
	int	n1 = mid - beg + 1;
	int	n2 = end - mid;
	int	right_i = 0;
	int	left_i = 0;

	std::vector<int> left(vec.begin() + beg, vec.begin() + mid + 1);
	std::vector<int> right(vec.begin() + mid + 1, vec.begin() + end + 1);

	for (int i = beg; i <= end; i++)
	{
		if (right_i == n2)
		{
			vec[i] = left[left_i];
			left_i++;
		}
		else if (left_i == n1)
		{
			vec[i] = right[right_i];
			right_i++;
		}
		else if (right[right_i] > left[left_i])
		{
			vec[i] = left[left_i];
			left_i++;
		}
		else
		{
			vec[i] = right[right_i];
			right_i++;
		}
	}
}

void PmergeMe::mergeDq(int beg, int mid, int end)
{
	int	n1 = mid - beg + 1;
	int	n2 = end - mid;
	int	right_i = 0;
	int	left_i = 0;

	std::deque<int> left(dq.begin() + beg, dq.begin() + mid + 1);
	std::deque<int> right(dq.begin() + mid + 1, dq.begin() + end + 1);

	for (int i = beg; i <= end; i++)
	{
		if (right_i == n2)
		{
			dq[i] = left[left_i];
			left_i++;
		}
		else if (left_i == n1)
		{
			dq[i] = right[right_i];
			right_i++;
		}
		else if (right[right_i] > left[left_i])
		{
			dq[i] = left[left_i];
			left_i++;
		}
		else
		{
			dq[i] = right[right_i];
			right_i++;
		}
	}
}

void PmergeMe::sortVector(int beg, int end)
{
	if (end - beg > K)
	{
		int	mid = (beg + end) / 2;
		sortVector(beg, mid);
		sortVector(mid + 1, end);
		mergeVector(beg, mid, end);
	}
	else
		insertionVector(beg, end);
}

void PmergeMe::sortDq(int beg, int end)
{
	if (end - beg > K)
	{
		int	mid = (beg + end) / 2;
		sortDq(beg, mid);
		sortDq(mid + 1, end);
		mergeDq(beg, mid, end);
	}
	else
		insertionDq(beg, end);

}

char** PmergeMe::getUnsorted(void) const
{
	return (this->unsorted);
}

PmergeMe::PmergeMe(char** unsorted) : unsorted(unsorted)
{
	parsing();
	sort();
	return ;
}

PmergeMe::PmergeMe(PmergeMe const &src)
{
	*this = src;
	return ;
}

PmergeMe &	PmergeMe::operator=(const PmergeMe &assign)
{
	this->unsorted = assign.getUnsorted();
	return (*this);
}

PmergeMe::~PmergeMe(void)
{
	return ;
}

