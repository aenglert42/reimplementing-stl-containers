#include "ft_vector.hpp"

void my_leaks(void)
{
	system("leaks test");
}

int main(void)
{
	atexit(my_leaks);
	ft::vector<int> v;
	v.print();
}