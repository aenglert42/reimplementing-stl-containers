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
	ft::vector<int> v;
	
	v.print();

}