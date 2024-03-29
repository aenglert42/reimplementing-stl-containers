#include "TesterClass.hpp"
#include "Tests.hpp"

#define TESTS \
algorithm_equal, \
algorithm_lexicographical_compare, \
enable_if, \
is_integral, \
iterator_traits, \
less, \
make_pair, \
my_vector_iterator, \
my_map_iterator, \
pair, \
pair_delete_old_pointer, \
pair_operator_equal, \
pair_relational_operators, \
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
sfinae, \
vector_my_assign, \
vector_my_erase, \
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
vector_rational_operators, \
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
vector_clear, \
vector_get_allocator, \
vector_no_member_swap, \
my_vector_test, \
map_constructors, \
map_operator_equal, \
map_begin, \
map_end, \
map_rbegin, \
map_rend, \
map_empty, \
map_size, \
map_max_size, \
map_operator_access_element, \
map_at, \
map_insert, \
map_erase, \
map_swap, \
map_clear, \
map_key_comp, \
map_value_comp, \
map_find, \
map_count, \
map_lower_bound, \
map_upper_bound, \
map_equal_range, \
map_lexicographical_compares, \
my_map_test/*, \
avl_insert, \
avl_erase, \


*/

int main()
{
	TesterClass tester {TESTS};
}

// compile with: c++ -std=c++11 *.cpp