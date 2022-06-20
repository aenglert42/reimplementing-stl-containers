#include "ft_vector.hpp"
#include <iostream>

#define BLUE "\033[34m"
#define RESET "\033[0m"

// void my_leaks(void)
// {
// 	std::cerr << BLUE;
// 	system("leaks containers_ft");
// 	std::cerr << RESET;
// }

int main(void)
{
	// atexit(my_leaks);
	ft::vector<int> v;
	v.print();
}