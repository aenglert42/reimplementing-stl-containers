#include "ft_vector.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>

#define BLUE "\033[34m"
#define RESET "\033[0m"

void my_leaks(void)
{
	std::cerr << BLUE;
	#if defined(__APPLE__)
	system("leaks containers_ft | grep leaked");
	#endif
	std::cerr << RESET;
}

int main(void)
{
	#if defined(__APPLE__)
	atexit(my_leaks);
	#endif
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> vector
	// constructor
	ft::Vector<int> v;
	v.push_back(5);
	v.push_back(5);
	v.push_back(8);
	v.push_back(4);
	v.print();

	ft::Vector<std::string> v2;
	v2.push_back("A");
	v2.push_back("B");
	v2.push_back("C");
	v2.print();

	ft::Vector<int> v3;
	v3.push_back(8);
	v3.push_back(8);
	v3.push_back(5);
	v3.print();

}