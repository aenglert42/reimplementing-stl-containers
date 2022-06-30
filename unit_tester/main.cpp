#include "TesterClass.hpp"
#include "Tests.hpp"

#define TESTS \
reverse_iterator_operator_access_element, \
reverse_iterator_operator_minus_minus, \
reverse_iterator_operator_pointer

int main()
{
	TesterClass tester {TESTS};
}

// compile with: c++ -std=c++11 *.cpp