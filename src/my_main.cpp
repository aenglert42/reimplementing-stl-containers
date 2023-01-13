#include "vector.hpp"
#include "map.hpp"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <limits>
#include <sys/time.h> // gettimeofday
#include <iomanip>	// std::setprecision

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define BOLD "\033[1m"
#define UNDERLINED "\033[4m"
#define RESET "\033[0m"

#define CAPTION_LENGTH 70
#define NUMBER_OF_ELEMENTS 100000

#define NAMESPACE ft

bool my_compare_function (int lhs, int rhs) {return lhs>rhs;}

void my_leaks(void)
{
	std::cerr << RED;
	#if defined(__APPLE__)
	system("leaks containers_ft | grep leaked");
	#endif
	std::cerr << RESET;
}

double get_time_in_ms(void)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return ((double)now.tv_sec * 1000 + (double)now.tv_usec / 1000);
}

double print_time_needed(double start_time, double end_time)
{
	double diff = (end_time - start_time);
	std::cout << "Time needed: " << std::fixed << std::setprecision(2) << diff << " ms" << std::endl << std::endl;
	return (diff);
}

void print_link(const std::string& first_path, const std::string& second_path = "")
{
	std::cout << "checkout: " << BLUE << first_path << RESET;
	if (second_path.empty() == false)
		std::cout << " & " << BLUE << second_path << RESET;
	std::cout << std::endl << std::endl;
}

void print_caption(const std::string& title)
{
	int length = (CAPTION_LENGTH - title.length()) / 2;

	std::cout << BOLD << YELLOW;
	for (int i = 0; i < length; ++i)
		std::cout << "<";
	std::cout << " " << title << " ";
	for (int i = 0; i < length; ++i)
		std::cout << ">";
	std::cout << RESET << std::endl << std::endl;
}

void print_sub_caption(const std::string& title)
{
	int length = (CAPTION_LENGTH - title.length()) / 2;

	std::cout << YELLOW;
	for (int i = 0; i < length; ++i)
		std::cout << "-";
	std::cout << " " << title << " ";
	for (int i = 0; i < length; ++i)
		std::cout << "-";
	std::cout << RESET << std::endl << std::endl;
}

template<class T>
void print_vector(NAMESPACE::vector<T>& vec, std::string i = "")
{
	std::cout << "Vec";
	if (i.empty() == false)
		std::cout << i;
	std::cout << " with size of " << vec.size()
		<< " and capacity of " << vec.capacity()
		<< " contains: " << std::endl;
	if (vec.empty())
		std::cout << "(nothing)";
	else
	{
		for (typename NAMESPACE::vector<T>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << std::endl;
	}
	std::cout << std::endl;
}

template<class T1, class T2, class T3>
void print_map(NAMESPACE::map<T1, T2, T3>& map, std::string i = "")
{
	std::cout << "Map";
	if (i.empty() == false)
		std::cout << i;
	std::cout << " with size of " << map.size()
		// << " and capacity of " << map.capacity()
		<< " contains: " << std::endl;
	if (map.empty())
		std::cout << "(nothing)";
	else
	{
		for (typename NAMESPACE::map<T1, T2, T3>::iterator it = map.begin(); it != map.end(); ++it)
			std::cout << "key: " << it->first << ", value: " << it->second << std::endl;
	}
	std::cout << std::endl;
}

int main(void)
{
	double start_time;
	double end_time;
	double std_time;
	double namespace_time;
	double ratio;
	#if defined(__APPLE__)
		atexit(my_leaks);
	#endif
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> vector
	print_caption("VECTOR");
	{
		typedef NAMESPACE::vector<int> namespace_vector_type;
		typedef std::vector<int> std_vector_type;
		namespace_vector_type vec(1, 4);
		namespace_vector_type::iterator it;
		namespace_vector_type::const_iterator cit;

		namespace_vector_type vec2;
		namespace_vector_type::iterator it2;
		namespace_vector_type::const_iterator cit2;

		// inner structure
		print_sub_caption("inner structure");
		print_link("/inc/vector.hpp:44");

		// iterators
		print_sub_caption("iterator compare");

		print_vector(vec);

		it = vec.begin();
		cit = vec.begin();
		if (it == cit)
			std::cout << "iterators are equal and comparable" << std::endl;
		else
			std::cout << "ERROR" << std::endl;

		// realloc
		print_sub_caption("dynamic allocation");
		std::cout << std::endl;
		std::cout << "old capacity: " << vec.capacity() << std::endl;
		vec.push_back(5);
		std::cout << "new capacity: " << vec.capacity() << std::endl;
		std::cout << std::endl;

		// swap
		print_sub_caption("swap");
		vec2.push_back(8);
		vec2.push_back(9);
		std::cout << "before swap:" << std::endl;
		it = vec.begin();
		it2 = vec2.begin();
		std::cout << RED;
		print_vector(vec);
		std::cout << RESET;
		std::cout << "and " << RED << "it" << RESET << " points to " << RED << *it << RESET << std::endl << std::endl; 
		std::cout << GREEN;
		print_vector(vec2, "2");
		std::cout << RESET;
		std::cout << "and " << GREEN << "it2" << RESET << " points to " << GREEN << *it2 << RESET << std::endl << std::endl; 

		swap(vec, vec2);
		std::cout << "after swap:" << std::endl;
		std::cout << RED;
		print_vector(vec);
		std::cout << RESET;
		std::cout << RED << "it" << RESET << " still points to " << GREEN << *it << RESET << " (which is now in " << GREEN << "vec2" << RESET << ") and it+1 points to " << *(it + 1) << std::endl << std::endl; 
		std::cout << GREEN;
		print_vector(vec2, "2");
		std::cout << RESET;
		std::cout << GREEN << "it2" << RESET << " still points to " << RED << *it2 << RESET << " (which is now in " << RED << "vec" << RESET << ") and it2+1 points to " << *(it2 + 1) << std::endl << std::endl; 

		// performance
		print_sub_caption("performance");
		std::cout << "inserting and erasing " << NUMBER_OF_ELEMENTS << " elements..." << std::endl << std::endl;

		// std
		std_vector_type std_vec;
		start_time = get_time_in_ms();
		for (int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
			std_vec.push_back(i);
		
		while (std_vec.empty() == false)
			std_vec.pop_back();

		end_time = get_time_in_ms();
		std::cout << "std:" << std::endl;
		std_time = print_time_needed(start_time, end_time);

		// NAMESPACE
		namespace_vector_type namespace_vec;
		start_time = get_time_in_ms();
		for (int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
			namespace_vec.push_back(i);
		
		while (namespace_vec.empty() == false)
			namespace_vec.pop_back();

		end_time = get_time_in_ms();
		std::cout << "NAMESPACE:" << std::endl;
		namespace_time = print_time_needed(start_time, end_time);

		// result
		ratio = (namespace_time / std_time);
		if (ratio < 1.1 && ratio > 0.9)
			std::cout << GREEN << "Performance of NAMESPACE and std is comparable." << std::endl;
		else if (ratio > 1)
			std::cout << RED << "NAMESPACE is " << ratio << " times slower than std." << std::endl;
		else if (ratio < 1)
			std::cout << GREEN << "NAMESPACE is " << (1 / ratio) << " times faster than std." << std::endl;
		std::cout << RESET << std::endl;
	}

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> map
	print_caption("MAP");
	{
		typedef NAMESPACE::map<int, std::string> namespace_map_type;
		typedef std::map<int, std::string> std_map_type;
		namespace_map_type map;
		namespace_map_type::iterator it;
		namespace_map_type::const_iterator cit;
		bool(*function_pointer)(int, int) = my_compare_function;
		NAMESPACE::map<int, std::string, bool(*)(int, int)> map2 (function_pointer);

		// inner structure
		print_sub_caption("inner structure");
		print_link("/inc/map.hpp:94");

		// pair
		print_sub_caption("pair");
		print_link("/inc/utils.hpp:8", "/inc/map.hpp:34");
		map.insert(NAMESPACE::make_pair(1, "banana"));
		map.insert(NAMESPACE::make_pair(2, "apple"));
		map.insert(NAMESPACE::make_pair(2, "pear"));
		map.insert(NAMESPACE::make_pair(4, "apple"));
		print_map(map);

		// compare
		print_sub_caption("compare");
		map2.insert(NAMESPACE::make_pair(1, "banana"));
		map2.insert(NAMESPACE::make_pair(2, "apple"));
		map2.insert(NAMESPACE::make_pair(2, "pear"));
		map2.insert(NAMESPACE::make_pair(4, "apple"));
		print_map(map2, "2");

		// std::allocator
		print_sub_caption("std::allocator");
		print_link("/inc/map.hpp:27", "/inc/tree.hpp:78");

		// iterator validity
		print_sub_caption("iterator validity");
		it = map.begin();
		cit = map.find(4);
		std::cout << "before insertion:" << std::endl;
		print_map(map);
		std::cout << "it points to " << it->first << " and cit points to " << cit->first << std::endl << std::endl;
		map.insert(NAMESPACE::make_pair(3, "cherry"));
		std::cout << "after insertion:" << std::endl;
		print_map(map);
		std::cout << "it points to " << it->first << " and cit points to " << cit->first << std::endl << std::endl;
		map.erase(2);
		std::cout << "after erase:" << std::endl;
		print_map(map);
		std::cout << "it points to " << it->first << " and cit points to " << cit->first << std::endl << std::endl;


		// performance
		print_sub_caption("performance");
		std::cout << "inserting and erasing " << NUMBER_OF_ELEMENTS << " elements..." << std::endl << std::endl;
	
		// std
		std_map_type std_map;
		start_time = get_time_in_ms();
		for (int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
			std_map.insert(std::make_pair(i, ""));
		
		while (std_map.empty() == false)
			std_map.erase(std_map.begin());
		end_time = get_time_in_ms();
		std::cout << "std:" << std::endl;
		std_time = print_time_needed(start_time, end_time);

		// NAMESPACE
		namespace_map_type namespace_map;
		start_time = get_time_in_ms();
		for (int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
			namespace_map.insert(NAMESPACE::make_pair(i, ""));
		
		while (namespace_map.empty() == false)
			namespace_map.erase(namespace_map.begin());
		end_time = get_time_in_ms();
		std::cout << "NAMESPACE:" << std::endl;
		namespace_time = print_time_needed(start_time, end_time);

		// result
		ratio = (namespace_time / std_time);
		if (ratio < 1.1 && ratio > 0.9)
			std::cout << GREEN << "Performance of NAMESPACE and std is comparable." << std::endl;
		else if (ratio > 1)
			std::cout << RED << "NAMESPACE is " << ratio << " times slower than std." << std::endl;
		else if (ratio < 1)
			std::cout << GREEN << "NAMESPACE is " << (1 / ratio) << " times faster than std." << std::endl;
		std::cout << RESET << std::endl;
	}
}