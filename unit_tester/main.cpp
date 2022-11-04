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
my_vector_iterator, \
vector_operator_equal, \
vector_costructors, \
vector_resize, \
vector_begin, \
vector_end, \
vector_rbegin, \
vector_rend, \
vector_size, \
vector_capacity, \
vector_empty, \
vector_reserve, \
vector_operator_access_element, \
vector_at, \
vector_front, \
vector_back, \
vector_data, \
vector_assign, \
vector_push_back, \
vector_pop_back, \
vector_insert, \
vector_erase, \
vector_swap, \
vector_no_member_swap, \
vector_rational_operators, \
sfinae/*, \
vector_iterator, \
vector_iterator_base, \
vector_iterator_traits, \
vector_iterator_operator_access_element, \
vector_iterator_operator_minus, \
vector_iterator_operator_minus_minus_1, \
vector_iterator_operator_minus_minus_2, \
vector_iterator_operator_plus, \
vector_iterator_operator_plus_equal, \
vector_iterator_operator_pointer, \
*/

int main()
{
	TesterClass tester {TESTS};
}

// compile with: c++ -std=c++11 *.cpp