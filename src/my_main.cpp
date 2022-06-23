#include "ft_vector.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>

#define BLUE "\033[34m"
#define RESET "\033[0m"

void my_leaks(void)
{
	std::cerr << BLUE;
	system("leaks containers_ft | grep leaked");
	std::cerr << RESET;
}

int main(void)
{
	atexit(my_leaks);
	// vector
	ft::vector<int> v;
	v.print();
	ft::pair<std::string, int> p;
	p.first = "abc";
	p.second = 1;
	std::cout << p.first << ", " << p.second << std::endl;
	ft::pair<std::string, int> p2("xyz", 2);
	std::cout << p2.first << ", " << p2.second << std::endl;
	ft::pair<std::string, int> p3(p2);
	std::cout << p3.first << ", " << p3.second << std::endl;
	p3 = p;
	std::cout << p3.first << ", " << p3.second << std::endl;
	//pair / make_pair
	int i = 5;
	char c = 'c';
	ft::pair<int, char> p4 = ft::make_pair(i, c);
	std::cout << p4.first << ", " << p4.second << std::endl;
}