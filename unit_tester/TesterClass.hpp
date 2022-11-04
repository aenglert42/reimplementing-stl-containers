#pragma once

#include <vector>
#include <sstream>			// std::stringstream
#include <initializer_list>	// std::initializer_list

#define TEST_FILE "Tests.hpp"

// text formating
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define BOLD "\033[1m"
#define UNDERLINED "\033[4m"
#define RESET "\033[0m"
#define TAB_WIDTH 50

class TestContainer
{
	public:
		std::stringstream stream;
		std::string test_name;
		int line;
		std::string expected_output;
		std::string real_output;
		void fill_container(std::string, int, std::string, std::string);
};

class TesterClass
{
	public:
		typedef std::vector<void (*)(TestContainer&)> test_collection;
		typedef void (*function_ptr)(TestContainer&);
		TestContainer container;
		std::vector<function_ptr> vector_of_tests;
		TesterClass(std::initializer_list<function_ptr> init);
		int _ko_counter = 0;
	private:
		TesterClass(void);
		void executeTests(void);
		void display_result(void);
};