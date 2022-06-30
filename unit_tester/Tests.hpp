#pragma once

#include <cassert>		// assert
#include <iostream>		// std::cout
#include <iterator>		// std::reverse_iterator
#include <map>			// std::map
#include <sstream>		// std::stringstream
#include <string>		// std::string
#include <utility>		// std::make_pair
#include <vector>		// std::vector

#define EXPECTED_OUTPUT(TEXT) container.fill_container(__func__, __LINE__, container.stream.str(), #TEXT)

// #include "ft_iterator.hpp"

// TEMPLATE FOR TEST FUNCTIONS (remove <> and edit text within)
// void <test_function_name>(TestContainer& container)
// {
// 	<code with std::cout output and without return statement>
// 	EXPECTED_OUTPUT(<expected output (no "" needed to indicate string)>);
// }

void reverse_iterator_operator_access_element(TestContainer& container)
{
	std::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);  // myvector: 0 1 2 3 4 5 6 7 8 9

	typedef std::vector<int>::iterator iter_type;

	std::reverse_iterator<iter_type> rev_iterator = myvector.rbegin();

	std::cout << "The fourth element from the end is: " << rev_iterator[3] << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(The fourth element from the end is: 6\n);
}

void reverse_iterator_operator_minus_minus(TestContainer& container)
{
	std::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

	typedef std::vector<int>::iterator iter_type;

	std::reverse_iterator<iter_type> rev_iterator = myvector.rend();

	rev_iterator -= 4;

	std::cout << "rev_iterator now points to: " << *rev_iterator << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(rev_iterator now points to: 3\n);
}

void reverse_iterator_operator_pointer(TestContainer& container)
{
	std::map<int,std::string> numbers;
	numbers.insert (std::make_pair(1,"one"));
	numbers.insert (std::make_pair(2,"two"));
	numbers.insert (std::make_pair(3,"three"));

	typedef std::map<int,std::string>::iterator map_iter;

	std::reverse_iterator<map_iter> rev_end (numbers.begin());

	std::reverse_iterator<map_iter> rev_iterator (numbers.end());

	for ( ; rev_iterator != rev_end ; ++rev_iterator )
		std::cout << rev_iterator->first << ' ' << rev_iterator->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(3 three\n2 two\n1 one\n);
}
