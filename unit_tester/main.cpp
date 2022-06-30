#include "TesterClass.hpp"
#include "Tests.hpp"

#define TESTS \
algorithm_equal, \
algorithm_lexicographical_compare, \
enable_if, \
is_integral, \
make_pair, \
reverse_iterator, \
reverse_iterator_base, \
reverse_iterator_traits, \
reverse_iterator_operator_access_element, \
reverse_iterator_operator_minus, \
reverse_iterator_operator_minus_minus_1, \
reverse_iterator_operator_minus_minus_2, \
reverse_iterator_operator_plus, \
reverse_iterator_operator_plus_equal, \
reverse_iterator_operator_pointer, \
pair, \
pair_delete_old_pointer, \
pair_operator_equal, \
pair_relational_operators, \
sfinae

int main()
{
	TesterClass tester {TESTS};
}

// compile with: c++ -std=c++11 *.cpp