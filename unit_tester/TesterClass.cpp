#include "TesterClass.hpp"

#include <iostream>	// std::cout, std::cerr
#include <iomanip>	// std::setw

TesterClass::TesterClass(std::initializer_list<function_ptr> init) : vector_of_tests(init)
{
	executeTests();
}

void TesterClass::display_result(void)
{
	std::cout << std::left << std::setfill('.') << std::setw(TAB_WIDTH) << container.test_name << std::right;
	if (container.expected_output == container.real_output)
		std::cout << GREEN << "OK" << RESET;
	else
	{
		std::cout << RED << "KO" << std::endl;
		std::cerr << YELLOW << "in: " << container.test_name << " " << TEST_FILE << ":" << container.line << "\n\nexpected:\n" << container.expected_output << std::endl;
		std::cerr << "recieved:\n" << container.real_output << RESET << std::endl;
	}
	std::cout << std::endl;
}

void TesterClass::executeTests(void)
{
	std::cout << BOLD << "\nTesting..." << RESET << std::endl;
	for(auto function : vector_of_tests)
	{
		container.stream.clear();
		container.stream.str("");
		std::streambuf* tmp = std::cout.rdbuf();
		std::cout.rdbuf(container.stream.rdbuf());
		function(container);
		std::cout.rdbuf(tmp);
		display_result();
	}
	std::cout << BOLD << "DONE\n" << RESET << std::endl;
}

void TestContainer::fill_container(std::string name, int line, std::string real, std::string expected)
{
	this->test_name = name;
	this->line = line;
	this->real_output = real;
	this->expected_output = expected;
}