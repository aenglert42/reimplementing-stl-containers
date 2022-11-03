#pragma once

#include <cassert>		// assert
#include <iostream>		// std::cout
// #include <iterator>		// std::reverse_iterator
#include <map>			// std::map
#include <sstream>		// std::stringstream
#include <string>		// std::string
#include <utility>		// std::make_pair
#include <vector>		// std::vector

//https://en.cppreference.com/w/cpp/preprocessor/replace checkout to abilitate use of ','
#define EXPECTED_OUTPUT(TEXT) container.fill_container(__func__, __LINE__, container.stream.str(), #TEXT)

#include "../inc/ft_algorithm.hpp"
#include "../inc/ft_iterator.hpp"
#include "../inc/ft_type_traits.hpp"
#include "../inc/utils.hpp"
#include "../inc/ft_vector.hpp"

// TEMPLATE FOR TEST FUNCTIONS (remove <> and edit text within)
// void <test_function_name>(TestContainer& container)
// {
// 	<code with std::cout output and without return statement>
// 	EXPECTED_OUTPUT(<expected output (no "" needed to indicate string)>);
// }

bool mypredicate (int i, int j) {
  return (i==j);
}

void algorithm_equal(TestContainer& container)
{
	int myints[] = {20,40,60,80,100};               //   myints: 20 40 60 80 100
	std::vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

	// using default comparison:
	if ( ft::equal (myvector.begin(), myvector.end(), myints) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

													//   myints: 20 40 60 80 100
	myvector[3]=81;                                 // myvector: 20 40 60 81 100

	// using predicate comparison:
	if ( ft::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

//////////////////////////////////
	EXPECTED_OUTPUT(The contents of both sequences are equal.\nThe contents of both sequences differ.\n);
}

bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }

void algorithm_lexicographical_compare(TestContainer& container)
{
	char foo[]="Apple";
	char bar[]="apartment";

	std::cout << std::boolalpha;

	std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

	std::cout << "Using default comparison (operator<): ";
	std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9);
	std::cout << '\n';

	std::cout << "Using mycomp as comparison object: ";
	std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(Comparing foo and bar lexicographically (foo<bar):\nUsing default comparison (operator<): true\nUsing mycomp as comparison object: false\n);
}

template <class T>
typename ft::enable_if<std::is_integral<T>::value,bool>::type is_odd (T i) {return bool(i%2);}

template < class T, class = typename ft::enable_if<std::is_integral<T>::value>::type>
bool is_even (T i) {return !bool(i%2);}

void enable_if(TestContainer& container)
{
	short int i = 1;    // code does not compile if type of i is not integral

	std::cout << std::boolalpha;
	std::cout << "i is odd: " << is_odd(i) << std::endl;
	std::cout << "i is even: " << is_even(i) << std::endl;

//////////////////////////////////
	EXPECTED_OUTPUT(i is odd: true\ni is even: false\n);
}

void is_integral(TestContainer& container)
{
	std::cout << std::boolalpha;
	std::cout << "is_integral:" << std::endl;
	std::cout << "char: " << ft::is_integral<char>::value << std::endl;
	std::cout << "int: " << ft::is_integral<int>::value << std::endl;
	std::cout << "float: " << ft::is_integral<float>::value << std::endl;
	std::cout << "double: " << ft::is_integral<double>::value << std::endl;

//////////////////////////////////
	EXPECTED_OUTPUT(is_integral:\nchar: true\nint: true\nfloat: false\ndouble: false\n);
}

void make_pair(TestContainer& container)
{
	ft::pair <int,int> foo;
	ft::pair <int,int> bar;

	foo = ft::make_pair (10,20);
	bar = ft::make_pair (10.5,'A'); // ok: implicit conversion from pair<double,char>

	std::cout << "foo: " << foo.first << " " << foo.second << '\n';
	std::cout << "bar: " << bar.first << " " << bar.second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(foo: 10 20\nbar: 10 65\n);
}

// void iterator(TestContainer& container)
// {
// 	int numbers[]={10,20,30,40,50};
// 	ft::iterator from(numbers);
// 	ft::iterator until(numbers+5);
// 	for (ft::iterator it=from; it!=until; it++)
// 		std::cout << *it << ' ';
// 	std::cout << '\n';

// //////////////////////////////////
// 	EXPECTED_OUTPUT(10 20 30 40 50\n);
// }

void reverse_iterator(TestContainer& container)
{
	std::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);

	typedef std::vector<int>::iterator iter_type;
															// ? 0 1 2 3 4 5 6 7 8 9 ?
	iter_type from (myvector.begin());                     //   ^
															//         ------>
	iter_type until (myvector.end());                      //                       ^
															//
	ft::reverse_iterator<iter_type> rev_until (from);     // ^
															//         <------
	ft::reverse_iterator<iter_type> rev_from (until);     //                     ^

	std::cout << "myvector:";
	while (rev_from != rev_until)
		std::cout << ' ' << *rev_from++;
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector: 9 8 7 6 5 4 3 2 1 0\n);
}

void reverse_iterator_base(TestContainer& container)
{
	std::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);

	typedef std::vector<int>::iterator iter_type;

	ft::reverse_iterator<iter_type> rev_end (myvector.begin());
	ft::reverse_iterator<iter_type> rev_begin (myvector.end());

	std::cout << "myvector:";
	for (iter_type it = rev_end.base(); it != rev_begin.base(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector: 0 1 2 3 4 5 6 7 8 9\n);
}

void reverse_iterator_traits(TestContainer& container)
{
	typedef ft::iterator_traits<int*> traits;
	if (typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag))
		std::cout << "int* is a random-access iterator" << std::endl;

//////////////////////////////////
	EXPECTED_OUTPUT(int* is a random-access iterator\n);
}

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

void reverse_iterator_operator_minus(TestContainer& container)
{
	std::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

	typedef std::vector<int>::iterator iter_type;

	std::reverse_iterator<iter_type> rev_iterator;

	rev_iterator = myvector.rend() - 3;

	std::cout << "myvector.rend()-3 points to: " << *rev_iterator << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector.rend()-3 points to: 2\n);
}

void reverse_iterator_operator_minus_minus_1(TestContainer& container)
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

void reverse_iterator_operator_minus_minus_2(TestContainer& container)
{
	std::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);

	typedef std::vector<int>::iterator iter_type;

	std::reverse_iterator<iter_type> rev_begin (myvector.end());
	std::reverse_iterator<iter_type> rev_end (myvector.begin());

	std::reverse_iterator<iter_type> rev_iterator = rev_begin;
	while ( rev_iterator != rev_end )
		std::cout << *rev_iterator++ << ' ';
	std::cout << '\n';

	while ( rev_iterator != rev_begin )
		std::cout << *(--rev_iterator) << ' ';
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(9 8 7 6 5 4 3 2 1 0 \n0 1 2 3 4 5 6 7 8 9 \n);
}

void reverse_iterator_operator_plus(TestContainer& container)
{
	std::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

	typedef std::vector<int>::iterator iter_type;

	std::reverse_iterator<iter_type> rev_it;

	rev_it = myvector.rbegin() +3;

	std::cout << "The fourth element from the end is: " << *rev_it << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(The fourth element from the end is: 6\n);
}

void reverse_iterator_operator_plus_equal(TestContainer& container)
{
	std::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

	typedef std::vector<int>::iterator iter_type;

	std::reverse_iterator<iter_type> rev_iterator = myvector.rbegin();

	rev_iterator += 2;

	std::cout << "The third element from the end is: " << *rev_iterator << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(The third element from the end is: 7\n);
}

void reverse_iterator_operator_pointer(TestContainer& container)
{
	std::map<int,std::string> numbers;
	numbers.insert (std::make_pair(1,"one")); // AE change to ft::make_pair
	numbers.insert (std::make_pair(2,"two")); // AE change to ft::make_pair
	numbers.insert (std::make_pair(3,"three")); // AE change to ft::make_pair

	typedef std::map<int,std::string>::iterator map_iter;

	std::reverse_iterator<map_iter> rev_end (numbers.begin());

	std::reverse_iterator<map_iter> rev_iterator (numbers.end());

	for ( ; rev_iterator != rev_end ; ++rev_iterator )
		std::cout << rev_iterator->first << ' ' << rev_iterator->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(3 three\n2 two\n1 one\n);
}

void pair(TestContainer& container)
{
	ft::pair <std::string,double> product1;                     // default constructor
	ft::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
	ft::pair <std::string,double> product3 (product2);          // copy constructor

	product1 = ft::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)

	product2.first = "shoes";                  // the type of first is string
	product2.second = 39.90;                   // the type of second is double

	std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
	std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
	std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(The price of lightbulbs is $0.99\nThe price of shoes is $39.9\nThe price of tomatoes is $2.3\n);
}

void pair_delete_old_pointer(TestContainer& container)
{
	int *one = new int(1);
	int *two = new int(2);
	int *three = new int(3);
	ft::pair<char, int *>  paerle;
	ft::pair<char, int *>  paerle2;

	paerle = ft::make_pair('a', one);
	paerle2 = ft::make_pair('b', two);
	std::cout << *(paerle.second) << std::endl;
	std::cout << paerle.first << std::endl;

	paerle = paerle2;
	// paerle.second = two;
	std::cout << *(paerle.second) << std::endl;
	std::cout << paerle.first << std::endl;
	std::cout << *one << std::endl;

	paerle = ft::make_pair('c', three);
	std::cout << *(paerle.second) << std::endl;
	std::cout << paerle.first << std::endl;

	delete(one);
	delete(two);
	delete(three);

//////////////////////////////////
	EXPECTED_OUTPUT(1\na\n2\nb\n1\n3\nc\n);
}

void pair_operator_equal(TestContainer& container)
{
	ft::pair <std::string,int> planet, homeplanet;

	planet = ft::make_pair("Earth",6371);

	homeplanet = planet;

	std::cout << "Home planet: " << homeplanet.first << '\n';
	std::cout << "Planet size: " << homeplanet.second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(Home planet: Earth\nPlanet size: 6371\n);
}

void pair_relational_operators(TestContainer& container)
{
	ft::pair<int,char> foo (10,'z');
	ft::pair<int,char> bar (90,'a');

	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

//////////////////////////////////
	EXPECTED_OUTPUT(foo and bar are not equal\nfoo is less than bar\nfoo is less than or equal to bar\n);
}

template <class T>
struct is_pointer
{
  template <class U>
  static char is_ptr(U *);

  template <class X, class Y>
  static char is_ptr(Y X::*);

  template <class U>
  static char is_ptr(U (*)());

  static double is_ptr(...);

  static T t;
  enum { value = sizeof(is_ptr(t)) == sizeof(char) };
};

struct Foo {
  int bar;
};

void sfinae(TestContainer& container)
{
	typedef int * IntPtr;
	typedef int Foo::* FooMemberPtr;
	typedef int (*FuncPtr)();
	typedef int one;
	typedef char  *two;

	char a = 'a';
	two two_two = &a;

	// printf("%c %c\n", a, *two_two);              // prints a, a
	std::cout << a << " " << *two_two << std::endl;
	// printf("%d\n",is_pointer<IntPtr>::value);        // prints 1
	std::cout << is_pointer<IntPtr>::value << std::endl;
	// printf("%d\n",is_pointer<FooMemberPtr>::value);  // prints 1
	std::cout << is_pointer<FooMemberPtr>::value << std::endl;
	// printf("%d\n",is_pointer<FuncPtr>::value);       // prints 1
	std::cout << is_pointer<FuncPtr>::value << std::endl;
	// printf("%d\n",is_pointer<one>::value);       // prints 0
	std::cout << is_pointer<one>::value << std::endl;
	// printf("%d\n",is_pointer<two>::value);       // prints 1
	std::cout << is_pointer<two>::value << std::endl;

//////////////////////////////////
	EXPECTED_OUTPUT(a a\n1\n1\n1\n0\n1\n);
}

void vector_costructors(TestContainer& container)
{
	// constructors used in the same order as described above:
	ft::Vector<int> first;                                // empty vector of ints
	ft::Vector<int> second (4,100);                       // four ints with value 100
	ft::Vector<int> third (second.begin(),second.end());  // iterating through second
	ft::Vector<int> fourth (third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	ft::Vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of fifth are:";
	for (ft::Vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(The contents of fifth are: 16 2 77 29\n);
}

void vector_operator_equal(TestContainer& container)
{
	ft::Vector<int> foo (3,0);
	ft::Vector<int> bar (5,0);

	bar = foo;
	foo = ft::Vector<int>();

	std::cout << "Size of foo: " << int(foo.size()) << '\n';
	std::cout << "Size of bar: " << int(bar.size()) << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(Size of foo: 0\nSize of bar: 3\n);
}

void my_vector_iterator(TestContainer& container)
{
	ft::Vector<int> v;
	v.push_back(5);
	v.push_back(5);
	v.push_back(8);
	v.push_back(4);

	for (ft::Vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << std::endl;
	std::cout << std::endl;

	for (ft::Vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it)
		std::cout << *it << std::endl;
	std::cout << std::endl;

	// ft::Vector<const int> vec; // AE https://stackoverflow.com/questions/47794223/getting-const-iterator-from-begin-instead-of-cbegin
	// vec.push_back(5);
	// vec.push_back(5);
	// vec.push_back(8);
	// vec.push_back(4);

	// for (ft::Vector<const int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
	// 	std::cout << *it << std::endl;
	// std::cout << std::endl;

	// for (ft::Vector<const int>::const_reverse_iterator it = vec.rbegin(); it != vec.rend(); ++it)
	// 	std::cout << *it << std::endl;
	// std::cout << std::endl;

//////////////////////////////////
	EXPECTED_OUTPUT(5\n5\n8\n4\n\n4\n8\n5\n5\n\n);
}