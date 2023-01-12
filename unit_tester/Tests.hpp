#pragma once

#include <cassert>		// assert
#include <iostream>		// std::cout
// #include <iterator>		// std::reverse_iterator
#include <map>			// std::map
#include <sstream>		// std::stringstream
#include <string>		// std::string
#include <utility>		// std::make_pair
#include <vector>		// std::vector
#include <algorithm>    // std::sort, std::includes

//https://en.cppreference.com/w/cpp/preprocessor/replace checkout to abilitate use of ','
#define EXPECTED_OUTPUT(TEXT) container.fill_container(__func__, __LINE__, container.stream.str(), #TEXT)

#define NAMESPACE ft
#define BENCHMARK_NUMBER 100000

#include "../inc/algorithm.hpp"
#include "../inc/iterator.hpp"
#include "../inc/type_traits.hpp"
#include "../inc/utils.hpp"
#include "../inc/vector.hpp"
#include "../inc/map.hpp"
#include "../inc/functional.hpp"

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
	if ( NAMESPACE::equal (myvector.begin(), myvector.end(), myints) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

													//   myints: 20 40 60 80 100
	myvector[3]=81;                                 // myvector: 20 40 60 81 100

	// using predicate comparison:
	if ( NAMESPACE::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
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
	std::cout << NAMESPACE::lexicographical_compare(foo,foo+5,bar,bar+9);
	std::cout << '\n';

	std::cout << "Using mycomp as comparison object: ";
	std::cout << NAMESPACE::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(Comparing foo and bar lexicographically (foo<bar):\nUsing default comparison (operator<): true\nUsing mycomp as comparison object: false\n);
}

template <class T>
typename NAMESPACE::enable_if<NAMESPACE::is_integral<T>::value,bool>::type is_odd (T i) {return bool(i%2);}

template < class T, class = typename NAMESPACE::enable_if<NAMESPACE::is_integral<T>::value>::type>
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
	std::cout << "char: " << NAMESPACE::is_integral<char>::value << std::endl;
	std::cout << "int: " << NAMESPACE::is_integral<int>::value << std::endl;
	std::cout << "float: " << NAMESPACE::is_integral<float>::value << std::endl;
	std::cout << "double: " << NAMESPACE::is_integral<double>::value << std::endl;

//////////////////////////////////
	EXPECTED_OUTPUT(is_integral:\nchar: true\nint: true\nfloat: false\ndouble: false\n);
}

void iterator_traits(TestContainer& container)
{
	typedef NAMESPACE::iterator_traits<int*> traits;
	if (typeid(traits::iterator_category)==typeid(NAMESPACE::random_access_iterator_tag))
		std::cout << "int* is a random-access iterator\n";

//////////////////////////////////
	EXPECTED_OUTPUT(int* is a random-access iterator\n);
}

void less(TestContainer& container)
{
	int foo[]={10,20,5,15,25};
	int bar[]={15,10,20};
	std::sort (foo, foo+5, NAMESPACE::less<int>());  // 5 10 15 20 25
	std::sort (bar, bar+3, NAMESPACE::less<int>());  //   10 15 20
	if (std::includes (foo, foo+5, bar, bar+3, NAMESPACE::less<int>()))
		std::cout << "foo includes bar.\n";

//////////////////////////////////
	EXPECTED_OUTPUT(foo includes bar.\n);
}

void make_pair(TestContainer& container)
{
	NAMESPACE::pair <int,int> foo;
	NAMESPACE::pair <int,int> bar;

	foo = NAMESPACE::make_pair (10,20);
	bar = NAMESPACE::make_pair (10.5,'A'); // ok: implicit conversion from pair<double,char>

	std::cout << "foo: " << foo.first << " " << foo.second << '\n';
	std::cout << "bar: " << bar.first << " " << bar.second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(foo: 10 20\nbar: 10 65\n);
}

void reverse_iterator(TestContainer& container)
{
	NAMESPACE::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);

	typedef NAMESPACE::vector<int>::iterator iter_type;
															// ? 0 1 2 3 4 5 6 7 8 9 ?
	iter_type from (myvector.begin());                     //   ^
															//         ------>
	iter_type until (myvector.end());                      //                       ^
															//
	NAMESPACE::reverse_iterator<iter_type> rev_until (from);     // ^
															//         <------
	NAMESPACE::reverse_iterator<iter_type> rev_from (until);     //                     ^

	std::cout << "myvector:";
	while (rev_from != rev_until)
		std::cout << ' ' << *rev_from++;
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector: 9 8 7 6 5 4 3 2 1 0\n);
}

void reverse_iterator_base(TestContainer& container)
{
	NAMESPACE::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);

	typedef NAMESPACE::vector<int>::iterator iter_type;

	NAMESPACE::reverse_iterator<iter_type> rev_end (myvector.begin());
	NAMESPACE::reverse_iterator<iter_type> rev_begin (myvector.end());

	std::cout << "myvector:";
	for (iter_type it = rev_end.base(); it != rev_begin.base(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector: 0 1 2 3 4 5 6 7 8 9\n);
}

void reverse_iterator_traits(TestContainer& container)
{
	typedef NAMESPACE::iterator_traits<int*> traits;
	if (typeid(traits::iterator_category)==typeid(NAMESPACE::random_access_iterator_tag))
		std::cout << "int* is a random-access iterator" << std::endl;

//////////////////////////////////
	EXPECTED_OUTPUT(int* is a random-access iterator\n);
}

void reverse_iterator_operator_access_element(TestContainer& container)
{
	NAMESPACE::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);  // myvector: 0 1 2 3 4 5 6 7 8 9

	typedef NAMESPACE::vector<int>::iterator iter_type;

	NAMESPACE::reverse_iterator<iter_type> rev_iterator = myvector.rbegin();

	std::cout << "The fourth element from the end is: " << rev_iterator[3] << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(The fourth element from the end is: 6\n);
}

void reverse_iterator_operator_minus(TestContainer& container)
{
	NAMESPACE::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

	typedef NAMESPACE::vector<int>::iterator iter_type;

	NAMESPACE::reverse_iterator<iter_type> rev_iterator;

	rev_iterator = myvector.rend() - 3;

	std::cout << "myvector.rend()-3 points to: " << *rev_iterator << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector.rend()-3 points to: 2\n);
}

void reverse_iterator_operator_minus_minus_1(TestContainer& container)
{
	NAMESPACE::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

	typedef NAMESPACE::vector<int>::iterator iter_type;

	NAMESPACE::reverse_iterator<iter_type> rev_iterator = myvector.rend();

	rev_iterator -= 4;

	std::cout << "rev_iterator now points to: " << *rev_iterator << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(rev_iterator now points to: 3\n);
}

void reverse_iterator_operator_minus_minus_2(TestContainer& container)
{
	NAMESPACE::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);

	typedef NAMESPACE::vector<int>::iterator iter_type;

	NAMESPACE::reverse_iterator<iter_type> rev_begin (myvector.end());
	NAMESPACE::reverse_iterator<iter_type> rev_end (myvector.begin());

	NAMESPACE::reverse_iterator<iter_type> rev_iterator = rev_begin;
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
	NAMESPACE::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

	typedef NAMESPACE::vector<int>::iterator iter_type;

	NAMESPACE::reverse_iterator<iter_type> rev_it;

	rev_it = myvector.rbegin() +3;

	std::cout << "The fourth element from the end is: " << *rev_it << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(The fourth element from the end is: 6\n);
}

void reverse_iterator_operator_plus_equal(TestContainer& container)
{
	NAMESPACE::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

	typedef NAMESPACE::vector<int>::iterator iter_type;

	NAMESPACE::reverse_iterator<iter_type> rev_iterator = myvector.rbegin();

	rev_iterator += 2;

	std::cout << "The third element from the end is: " << *rev_iterator << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(The third element from the end is: 7\n);
}

void reverse_iterator_operator_pointer(TestContainer& container)
{
	NAMESPACE::map<int,std::string> numbers;
	numbers.insert (NAMESPACE::make_pair(1,"one"));
	numbers.insert (NAMESPACE::make_pair(2,"two"));
	numbers.insert (NAMESPACE::make_pair(3,"three"));

	typedef NAMESPACE::map<int,std::string>::iterator map_iter;

	NAMESPACE::reverse_iterator<map_iter> rev_end (numbers.begin());

	NAMESPACE::reverse_iterator<map_iter> rev_iterator (numbers.end());

	for ( ; rev_iterator != rev_end ; ++rev_iterator )
		std::cout << rev_iterator->first << ' ' << rev_iterator->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(3 three\n2 two\n1 one\n);
}

void pair(TestContainer& container)
{
	NAMESPACE::pair <std::string,double> product1;                     // default constructor
	NAMESPACE::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
	NAMESPACE::pair <std::string,double> product3 (product2);          // copy constructor

	product1 = NAMESPACE::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)

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
	NAMESPACE::pair<char, int *>  paerle;
	NAMESPACE::pair<char, int *>  paerle2;

	paerle = NAMESPACE::make_pair('a', one);
	paerle2 = NAMESPACE::make_pair('b', two);
	std::cout << *(paerle.second) << std::endl;
	std::cout << paerle.first << std::endl;

	paerle = paerle2;
	// paerle.second = two;
	std::cout << *(paerle.second) << std::endl;
	std::cout << paerle.first << std::endl;
	std::cout << *one << std::endl;

	paerle = NAMESPACE::make_pair('c', three);
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
	NAMESPACE::pair <std::string,int> planet, homeplanet;

	planet = NAMESPACE::make_pair("Earth",6371);

	homeplanet = planet;

	std::cout << "Home planet: " << homeplanet.first << '\n';
	std::cout << "Planet size: " << homeplanet.second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(Home planet: Earth\nPlanet size: 6371\n);
}

void pair_relational_operators(TestContainer& container)
{
	NAMESPACE::pair<int,char> foo (10,'z');
	NAMESPACE::pair<int,char> bar (90,'a');

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
	NAMESPACE::vector<int> first;                                // empty vector of ints
	NAMESPACE::vector<int> second (4,100);                       // four ints with value 100
	NAMESPACE::vector<int> third (second.begin(),second.end());  // iterating through second
	NAMESPACE::vector<int> fourth (third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	NAMESPACE::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of fifth are:";
	for (NAMESPACE::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(The contents of fifth are: 16 2 77 29\n);
}

void vector_operator_equal(TestContainer& container)
{
	NAMESPACE::vector<int> foo (3,0);
	NAMESPACE::vector<int> bar (5,0);

	bar = foo;
	foo = NAMESPACE::vector<int>();

	std::cout << "Size of foo: " << int(foo.size()) << '\n';
	std::cout << "Size of bar: " << int(bar.size()) << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(Size of foo: 0\nSize of bar: 3\n);
}

void my_map_iterator(TestContainer& container)
{
	NAMESPACE::map<std::string, int> myMap;
	myMap.insert(NAMESPACE::make_pair("5", 5));
	myMap.insert(NAMESPACE::make_pair("1", 1));
	myMap.insert(NAMESPACE::make_pair("8", 8));

	NAMESPACE::map<std::string, int>::iterator it = myMap.begin();
	std::cout << it->first << std::endl;
	it = myMap.end();
	it--;
	std::cout << it->first << std::endl;
	it--;
	std::cout << it->first << std::endl;
	it--;
	std::cout << it->first << std::endl;
	it++;
	it++;
	it++;
	if (it == myMap.end())
		std::cout << "equal" << std::endl;

	// const_iterator
	const NAMESPACE::map<std::string, int> myConstMap (myMap);
	NAMESPACE::map<std::string, int>::const_iterator cit = myConstMap.begin();
	std::cout << cit->first << std::endl;
	cit = myConstMap.end();
	cit--;
	std::cout << cit->first << std::endl;
	cit--;
	std::cout << cit->first << std::endl;
	cit--;
	std::cout << cit->first << std::endl;
	cit++;
	cit++;
	cit++;
	if (cit == myConstMap.end())
		std::cout << "equal" << std::endl;

	// reverse iterator
	NAMESPACE::map<std::string, int>::reverse_iterator rit = myMap.rbegin();
	std::cout << rit->first << std::endl;
	rit = myMap.rend();
	rit--;
	std::cout << rit->first << std::endl;
	rit--;
	std::cout << rit->first << std::endl;
	rit--;
	std::cout << rit->first << std::endl;
	rit++;
	rit++;
	rit++;
	if (rit == myMap.rend())
		std::cout << "equal" << std::endl;

	// reverse const_iterator
	NAMESPACE::map<std::string, int>::const_reverse_iterator crit = myConstMap.rbegin();
	std::cout << crit->first << std::endl;
	crit = myConstMap.rend();
	crit--;
	std::cout << crit->first << std::endl;
	crit--;
	std::cout << crit->first << std::endl;
	crit--;
	std::cout << crit->first << std::endl;
	crit++;
	crit++;
	crit++;
	if (crit == myConstMap.rend())
		std::cout << "equal" << std::endl;

//////////////////////////////////
	EXPECTED_OUTPUT(1\n8\n5\n1\nequal\n1\n8\n5\n1\nequal\n8\n1\n5\n8\nequal\n8\n1\n5\n8\nequal\n);
}

void my_vector_iterator(TestContainer& container)
{
	NAMESPACE::vector<int> v;
	v.push_back(5);
	v.push_back(5);
	v.push_back(8);
	v.push_back(4);

	for (NAMESPACE::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << std::endl;
	std::cout << std::endl;

	for (NAMESPACE::vector<int>::const_iterator cit = v.begin(); cit != v.end(); ++cit)
		std::cout << *cit << std::endl;
	std::cout << std::endl;

	for (NAMESPACE::vector<int>::reverse_iterator rit = v.rbegin(); rit != v.rend(); ++rit)
		std::cout << *rit << std::endl;
	std::cout << std::endl;

	for (NAMESPACE::vector<int>::const_reverse_iterator crit = v.rbegin(); crit != v.rend(); ++crit)
		std::cout << *crit << std::endl;
	std::cout << std::endl;

	NAMESPACE::vector<int>::iterator it = v.begin() + 1;
	NAMESPACE::vector<int>::const_iterator cit = v.begin();
	NAMESPACE::vector<int>::reverse_iterator rit = v.rbegin() + 1;
	NAMESPACE::vector<int>::const_reverse_iterator crit = v.rbegin();

	std::cout << it - cit << cit - it << rit - crit << crit - rit << std::endl;

	it += 3;
	it -= 2;
	it = it - 1;

	cit += 3;
	cit -= 2;
	cit = cit - 1;

	rit += 3;
	rit -= 2;
	rit = rit - 1;

	crit += 3;
	crit -= 2;
	crit = crit - 1;

	std::cout << *it << *cit << *rit << *crit << std::endl;

//////////////////////////////////
	EXPECTED_OUTPUT(5\n5\n8\n4\n\n5\n5\n8\n4\n\n4\n8\n5\n5\n\n4\n8\n5\n5\n\n1-11-1\n5584\n);
}

void vector_resize(TestContainer& container)
{
	NAMESPACE::vector<int> myvector;

	// set some initial content:
	for (int i=1;i<10;i++) myvector.push_back(i);

	myvector.resize(5);
	myvector.resize(8,100);
	myvector.resize(12);

	std::cout << "myvector contains:";
	for (int i=0;i<(int)myvector.size();i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector contains: 1 2 3 4 5 100 100 100 0 0 0 0\n);
}

void vector_reserve(TestContainer& container)
{
	NAMESPACE::vector<int>::size_type sz;

	NAMESPACE::vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i=0; i<100; ++i) {
		foo.push_back(i);
		if (sz!=foo.capacity()) {
		sz = foo.capacity();
		std::cout << "capacity changed: " << sz << '\n';
		}
	}

	NAMESPACE::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);   // this is the only difference with foo above
	std::cout << "making bar grow:\n";
	for (int i=0; i<100; ++i) {
		bar.push_back(i);
		if (sz!=bar.capacity()) {
		sz = bar.capacity();
		std::cout << "capacity changed: " << sz << '\n';
		}
	}

//////////////////////////////////
	EXPECTED_OUTPUT(making foo grow:\ncapacity changed: 1\ncapacity changed: 2\ncapacity changed: 4\ncapacity changed: 8\ncapacity changed: 16\ncapacity changed: 32\ncapacity changed: 64\ncapacity changed: 128\nmaking bar grow:\ncapacity changed: 100\n);
}

void vector_begin(TestContainer& container)
{
	NAMESPACE::vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);

	std::cout << "myvector contains:";
	for (NAMESPACE::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector contains: 1 2 3 4 5\n);
}

void vector_end(TestContainer& container)
{
	NAMESPACE::vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);

	std::cout << "myvector contains:";
	for (NAMESPACE::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector contains: 1 2 3 4 5\n);
}

void vector_rbegin(TestContainer& container)
{
	NAMESPACE::vector<int> myvector (5);  // 5 default-constructed ints

	int i=0;

	NAMESPACE::vector<int>::reverse_iterator rit = myvector.rbegin();
	for (; rit!= myvector.rend(); ++rit)
		*rit = ++i;

	std::cout << "myvector contains:";
	for (NAMESPACE::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector contains: 5 4 3 2 1\n);
}

void vector_rend(TestContainer& container)
{
	NAMESPACE::vector<int> myvector (5);  // 5 default-constructed ints

	NAMESPACE::vector<int>::reverse_iterator rit = myvector.rbegin();

	int i=0;
	for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
		*rit = ++i;

	std::cout << "myvector contains:";
	for (NAMESPACE::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector contains: 5 4 3 2 1\n);
}

void vector_size(TestContainer& container)
{
	NAMESPACE::vector<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i=0; i<10; i++) myints.push_back(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.insert (myints.end(),10,100);
	std::cout << "2. size: " << myints.size() << '\n';

	myints.pop_back();
	std::cout << "3. size: " << myints.size() << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(0. size: 0\n1. size: 10\n2. size: 20\n3. size: 19\n);
}

void vector_insert(TestContainer& container)
{
	NAMESPACE::vector<int> myvector (3,100);
	NAMESPACE::vector<int>::iterator it;

// myvector.print();

	it = myvector.begin();
	it = myvector.insert ( it , 200 );
// myvector.print();

	myvector.insert (it,2,300);
// myvector.print();

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	NAMESPACE::vector<int> anothervector (2,400);
// anothervector.print();
	myvector.insert (it+2,anothervector.begin(),anothervector.end());
// myvector.print();

	int myarray [] = { 501,502,503 };
	myvector.insert (myvector.begin(), myarray, myarray+3);
// myvector.print();

	std::cout << "myvector contains:";
	for (it=myvector.begin(); it<myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector contains: 501 502 503 300 300 400 400 200 100 100 100\n);
}

void vector_rational_operators(TestContainer& container)
{
	NAMESPACE::vector<int> foo (3,100);   // three ints with a value of 100
	NAMESPACE::vector<int> bar (2,200);   // two ints with a value of 200

	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

//////////////////////////////////
	EXPECTED_OUTPUT(foo and bar are not equal\nfoo is less than bar\nfoo is less than or equal to bar\n);
}

void vector_capacity(TestContainer& container)
{
	NAMESPACE::vector<int> myvector;

	// set some content in the vector:
	for (int i=0; i<100; i++) myvector.push_back(i);

	std::cout << "size: " << (int) myvector.size() << '\n';
	std::cout << "capacity: " << (int) myvector.capacity() << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(size: 100\ncapacity: 128\n);
}

void vector_empty(TestContainer& container)
{
	NAMESPACE::vector<int> myvector;
	int sum (0);

	for (int i=1;i<=10;i++) myvector.push_back(i);

	while (!myvector.empty())
	{
		sum += myvector.back();
		myvector.pop_back();
	}

	std::cout << "total: " << sum << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(total: 55\n);
}

void vector_operator_access_element(TestContainer& container)
{
	NAMESPACE::vector<int> myvector (10);   // 10 zero-initialized elements

	NAMESPACE::vector<int>::size_type sz = myvector.size();

	// assign some values:
	for (unsigned i=0; i<sz; i++) myvector[i]=i;

	// reverse vector using operator[]:
	for (unsigned i=0; i<sz/2; i++)
	{
		int temp;
		temp = myvector[sz-1-i];
		myvector[sz-1-i]=myvector[i];
		myvector[i]=temp;
	}

	std::cout << "myvector contains:";
	for (unsigned i=0; i<sz; i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector contains: 9 8 7 6 5 4 3 2 1 0\n);
}

void vector_at(TestContainer& container)
{
	NAMESPACE::vector<int> myvector (10);   // 10 zero-initialized ints

	// assign some values:
	for (unsigned i=0; i<myvector.size(); i++)
		myvector.at(i)=i;

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); i++)
		std::cout << ' ' << myvector.at(i);
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector contains: 0 1 2 3 4 5 6 7 8 9\n);
}

void vector_front(TestContainer& container)
{
	NAMESPACE::vector<int> myvector;

	myvector.push_back(78);
	myvector.push_back(16);

	// now front equals 78, and back 16

	myvector.front() -= myvector.back();

	std::cout << "myvector.front() is now " << myvector.front() << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector.front() is now 62\n);
}

void vector_back(TestContainer& container)
{
	NAMESPACE::vector<int> myvector;

	myvector.push_back(10);

	while (myvector.back() != 0)
	{
		myvector.push_back ( myvector.back() -1 );
	}

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size() ; i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector contains: 10 9 8 7 6 5 4 3 2 1 0\n);
}

void vector_data(TestContainer& container)
{
	NAMESPACE::vector<int> myvector (5);

	int* p = myvector.data();

	*p = 10;
	++p;
	*p = 20;
	p[2] = 100;

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector contains: 10 20 0 100 0\n);
}

void vector_assign(TestContainer& container)
{
	NAMESPACE::vector<int> first;
	NAMESPACE::vector<int> second;
	NAMESPACE::vector<int> third;

	first.assign (7,100);             // 7 ints with a value of 100

	NAMESPACE::vector<int>::iterator it;
	it=first.begin()+1;

	second.assign (it,first.end()-1); // the 5 central values of first

	int myints[] = {1776,7,4};
	third.assign (myints,myints+3);   // assigning from array.

	std::cout << "Size of first: " << int (first.size()) << '\n';
	std::cout << "Size of second: " << int (second.size()) << '\n';
	std::cout << "Size of third: " << int (third.size()) << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(Size of first: 7\nSize of second: 5\nSize of third: 3\n);
}

void vector_push_back(TestContainer& container)
{
	NAMESPACE::vector<int> myvector;

	myvector.push_back (5);
	myvector.push_back (5);
	myvector.push_back (8);
	myvector.push_back (4);


	std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";

//////////////////////////////////
	EXPECTED_OUTPUT(myvector stores 4 numbers.\n);
}

void vector_pop_back(TestContainer& container)
{
	NAMESPACE::vector<int> myvector;
	int sum (0);
	myvector.push_back (100);
	myvector.push_back (200);
	myvector.push_back (300);

	while (!myvector.empty())
	{
		sum+=myvector.back();
		myvector.pop_back();
	}

	std::cout << "The elements of myvector add up to " << sum << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(The elements of myvector add up to 600\n);
}

void vector_erase(TestContainer& container)
{
	NAMESPACE::vector<int> myvector;

	// set some values (from 1 to 10)
	for (int i=1; i<=10; i++) myvector.push_back(i);

	// erase the 6th element
	myvector.erase (myvector.begin()+5);

	// erase the first 3 elements:
	myvector.erase (myvector.begin(),myvector.begin()+3);

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector contains: 4 5 7 8 9 10\n);
}

void vector_swap(TestContainer& container)
{
	NAMESPACE::vector<int> foo (3,100);   // three ints with a value of 100
	NAMESPACE::vector<int> bar (5,200);   // five ints with a value of 200

	foo.swap(bar);

	std::cout << "foo contains:";
	for (unsigned i=0; i<foo.size(); i++)
		std::cout << ' ' << foo[i];
	std::cout << '\n';

	std::cout << "bar contains:";
	for (unsigned i=0; i<bar.size(); i++)
		std::cout << ' ' << bar[i];
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(foo contains: 200 200 200 200 200\nbar contains: 100 100 100\n);
}

void vector_no_member_swap(TestContainer& container)
{
	NAMESPACE::vector<int> foo (3,100);   // three ints with a value of 100
	NAMESPACE::vector<int> bar (5,200);   // five ints with a value of 200

	foo.swap(bar);

	std::cout << "foo contains:";
	for (NAMESPACE::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "bar contains:";
	for (NAMESPACE::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(foo contains: 200 200 200 200 200\nbar contains: 100 100 100\n);
}

void vector_clear(TestContainer& container)
{
	NAMESPACE::vector<int> myvector;
	myvector.push_back (100);
	myvector.push_back (200);
	myvector.push_back (300);

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	myvector.clear();
	myvector.push_back (1101);
	myvector.push_back (2202);

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector contains: 100 200 300\nmyvector contains: 1101 2202\n);
}

void vector_get_allocator(TestContainer& container)
{
	NAMESPACE::vector<int> myvector;
	int * p;
	unsigned int i;

	// allocate an array with space for 5 elements using vector's allocator:
	p = myvector.get_allocator().allocate(5);

	// construct values in-place on the array:
	for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

	std::cout << "The allocated array contains:";
	for (i=0; i<5; i++) std::cout << ' ' << p[i];
	std::cout << '\n';

	// destroy and deallocate:
	for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
	myvector.get_allocator().deallocate(p,5);

//////////////////////////////////
	EXPECTED_OUTPUT(The allocated array contains: 0 1 2 3 4\n);
}

void vector_my_assign(TestContainer& container)
{
	NAMESPACE::vector<int> vct(7);
	NAMESPACE::vector<int> vct_two(4);
	NAMESPACE::vector<int> vct_three;
	NAMESPACE::vector<int> vct_four;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	for (unsigned long int i = 0; i < vct_two.size(); ++i)
		vct_two[i] = (vct_two.size() - i) * 5;
	std::cout << vct.size() << std::endl;
	std::cout << vct_two.size() << std::endl;

	vct_three.assign(vct.begin(), vct.end());
	vct.assign(vct_two.begin(), vct_two.end());
	vct_two.assign(2, 42);
	vct_four.assign(4, 21);

	std::cout << "### After assign(): ###" << std::endl;

	std::cout << vct.size() << std::endl;
	std::cout << vct_two.size() << std::endl;
	std::cout << vct_three.size() << std::endl;
	std::cout << vct_four.size() << std::endl;

	vct_four.assign(6, 84);
	std::cout << vct_four.size() << std::endl;

	std::cout << "### assign() on enough capacity and low size: ###" << std::endl;

	vct.assign(5, 53);
	vct_two.assign(vct_three.begin(), vct_three.begin() + 3);

	std::cout << vct.size() << std::endl;
	std::cout << vct_two.size() << std::endl;

//////////////////////////////////
	EXPECTED_OUTPUT(7\n4\n### After assign(): ###\n4\n2\n7\n4\n6\n### assign() on enough capacity and low size: ###\n5\n3\n);
}

static void	checkErase(NAMESPACE::vector<std::string> const &vct,
					NAMESPACE::vector<std::string>::const_iterator const &it)
{
	static int i = 0;
	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
}

void vector_my_erase(TestContainer& container)
{
	NAMESPACE::vector<std::string> vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = std::string((vct.size() - i), i + 65);

	checkErase(vct, vct.erase(vct.begin() + 2));

	checkErase(vct, vct.erase(vct.begin()));
	checkErase(vct, vct.erase(vct.end() - 1));

	checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));
	checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

	vct.push_back("Hello");
	vct.push_back("Hi there");

	checkErase(vct, vct.erase(vct.end() - 3, vct.end()));

	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");

	checkErase(vct, vct.erase(vct.begin(), vct.end()));

//////////////////////////////////
	EXPECTED_OUTPUT([0] erase: 2\n[1] erase: 0\n[2] erase: 7\n[3] erase: 0\n[4] erase: 1\n[5] erase: 1\n[6] erase: 0\n);
}

bool fncomp (char lhs, char rhs) {return lhs>rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs>rhs;}
};

void map_constructors(TestContainer& container)
{
	NAMESPACE::map<char,int> first;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;

	NAMESPACE::map<char,int> second (first.begin(),first.end());

	first['c']=500;
	first['d']=700;

	NAMESPACE::map<char,int> third (second);

	second['a']=100;
	second['b']=300;

	NAMESPACE::map<char,int,classcomp> fourth;                 // class as Compare

	fourth['a']=10;
	fourth['b']=30;
	fourth['c']=50;

	bool(*fn_pt)(char,char) = fncomp;
	NAMESPACE::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

	fifth.insert(NAMESPACE::make_pair('a', 10));
	fifth.insert(NAMESPACE::make_pair('b', 30));
	fifth.insert(NAMESPACE::make_pair('c', 50));


	NAMESPACE::map<char,int>::iterator it;
	for (it=first.begin(); it!=first.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	for (it=second.begin(); it!=second.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	for (it=third.begin(); it!=third.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	for (it=fourth.begin(); it!=fourth.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	for (it=fifth.begin(); it!=fifth.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(a => 10\nb => 30\nc => 500\nd => 700\na => 100\nb => 300\nc => 50\nd => 70\na => 10\nb => 30\nc => 50\nd => 70\nc => 50\nb => 30\na => 10\nc => 50\nb => 30\na => 10\n);
}

void map_operator_equal(TestContainer& container)
{
	NAMESPACE::map<char,int> first;
	NAMESPACE::map<char,int> second;

	first['x']=8;
	first['y']=16;
	first['z']=32;

	second=first;                // second now contains 3 ints
	first=NAMESPACE::map<char,int>();  // and first is now empty

	NAMESPACE::map<char,int>::iterator it;
	std::cout << "Size of first: " << first.size() << '\n';
	for (it=first.begin(); it!=first.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "Size of second: " << second.size() << '\n';
	for (it=second.begin(); it!=second.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(Size of first: 0\nSize of second: 3\nx => 8\ny => 16\nz => 32\n);
}

void map_begin(TestContainer& container)
{
	NAMESPACE::map<char,int> mymap;

	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;

	// show content:
	for (NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(a => 200\nb => 100\nc => 300\n);
}

void map_end(TestContainer& container)
{
	NAMESPACE::map<char,int> mymap;

	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;

	// show content:
	for (NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(a => 200\nb => 100\nc => 300\n);
}

void map_rbegin(TestContainer& container)
{
	NAMESPACE::map<char,int> mymap;

	mymap['x'] = 100;
	mymap['y'] = 200;
	mymap['z'] = 300;

	// show content:
	NAMESPACE::map<char,int>::reverse_iterator rit;
	for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
		std::cout << rit->first << " => " << rit->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(z => 300\ny => 200\nx => 100\n);
}

void map_rend(TestContainer& container)
{
	NAMESPACE::map<char,int> mymap;

	mymap['x'] = 100;
	mymap['y'] = 200;
	mymap['z'] = 300;

	// show content:
	NAMESPACE::map<char,int>::reverse_iterator rit;
	for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
		std::cout << rit->first << " => " << rit->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(z => 300\ny => 200\nx => 100\n);
}

void map_empty(TestContainer& container)
{
	NAMESPACE::map<char,int> mymap;

	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;

	while (!mymap.empty())
	{
		std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
		mymap.erase(mymap.begin());
	}

//////////////////////////////////
	EXPECTED_OUTPUT(a => 10\nb => 20\nc => 30\n);
}

void map_size(TestContainer& container)
{
	NAMESPACE::map<char,int> mymap;
	mymap['a']=101;
	mymap['b']=202;
	mymap['c']=302;

	std::cout << "mymap.size() is " << mymap.size() << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(mymap.size() is 3\n);
}

void map_max_size(TestContainer& container)
{
	int i;
	NAMESPACE::map<int,int> mymap;

	if (mymap.max_size()>1000)
	{
		for (i=0; i<1000; i++) mymap[i]=0;
		std::cout << "The map contains 1000 elements.\n";
	}
	else std::cout << "The map could not hold 1000 elements.\n";

//////////////////////////////////
	EXPECTED_OUTPUT(The map contains 1000 elements.\n);
}

void map_operator_access_element(TestContainer& container)
{
	NAMESPACE::map<char,std::string> mymap;

	mymap['a']="an element";
	mymap['b']="another element";
	mymap['c']=mymap['b'];

	std::cout << "mymap['a'] is " << mymap['a'] << '\n';
	std::cout << "mymap['b'] is " << mymap['b'] << '\n';
	std::cout << "mymap['c'] is " << mymap['c'] << '\n';
	std::cout << "mymap['d'] is " << mymap['d'] << '\n';

	std::cout << "mymap now contains " << mymap.size() << " elements.\n";

//////////////////////////////////
	EXPECTED_OUTPUT(mymap['a'] is an element\nmymap['b'] is another element\nmymap['c'] is another element\nmymap['d'] is \nmymap now contains 4 elements.\n);
}

void map_at(TestContainer& container)
{
	// NAMESPACE::map<std::string,int> mymap = {
	// 				{ "alpha", 0 },
	// 				{ "beta", 0 },
	// 				{ "gamma", 0 } };

	std::map<std::string,int> mymap;
	mymap["alpha"]=0;
	mymap["beta"]=0;
	mymap["gamma"]=0;

	mymap.at("alpha") = 10;
	mymap.at("beta") = 20;
	mymap.at("gamma") = 30;

	for (auto& x: mymap) {
		std::cout << x.first << ": " << x.second << '\n';
	}
	try{
		mymap.at("lambda") = 30;
	}
	catch (const std::out_of_range& oor) {
		std::cout << "exeption caught: " << oor.what() << '\n';
	}

// const map
	const std::map<std::string,int> myconstmap(mymap);
	int test = myconstmap.at("alpha");
	std::cout << test << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(alpha: 10\nbeta: 20\ngamma: 30\nexeption caught: map::at\n10\n);
}

void map_insert(TestContainer& container)
{
	NAMESPACE::map<char,int> mymap;

	// first insert function version (single parameter):
	mymap.insert ( NAMESPACE::pair<char,int>('a',100) );
	mymap.insert ( NAMESPACE::pair<char,int>('z',200) );

	NAMESPACE::pair<NAMESPACE::map<char,int>::iterator,bool> ret;
	ret = mymap.insert ( NAMESPACE::pair<char,int>('z',500) );
	if (ret.second==false) {
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
	}

	// second insert function version (with hint position):
	NAMESPACE::map<char,int>::iterator it = mymap.begin();
	mymap.insert (it, NAMESPACE::pair<char,int>('b',300));  // max efficiency inserting
	mymap.insert (it, NAMESPACE::pair<char,int>('c',400));  // no max efficiency inserting

	// third insert function version (range insertion):
	NAMESPACE::map<char,int> anothermap;
	anothermap.insert(mymap.begin(), mymap.find('c'));

	// showing contents:
	std::cout << "mymap contains:\n";
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "anothermap contains:\n";
	for (it=anothermap.begin(); it!=anothermap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(element 'z' already existed with a value of 200\nmymap contains:\na => 100\nb => 300\nc => 400\nz => 200\nanothermap contains:\na => 100\nb => 300\n);
}

void map_erase(TestContainer& container)
{
	NAMESPACE::map<char,int> mymap;
	NAMESPACE::map<char,int>::iterator it;

	// insert some values:
	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;
	mymap['d']=40;
	mymap['e']=50;
	mymap['f']=60;
	// mymap.insert(NAMESPACE::make_pair('a', 10));
	// mymap.insert(NAMESPACE::make_pair('b', 20));
	// mymap.insert(NAMESPACE::make_pair('c', 30));
	// mymap.insert(NAMESPACE::make_pair('d', 40));
	// mymap.insert(NAMESPACE::make_pair('e', 50));
	// mymap.insert(NAMESPACE::make_pair('f', 60));

	it=mymap.find('b');
	mymap.erase (it);                   // erasing by iterator

	mymap.erase ('c');                  // erasing by key

	it=mymap.find ('e');
	mymap.erase ( it, mymap.end() );    // erasing by range

	// show content:
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(a => 10\nd => 40\n);
}

void map_swap(TestContainer& container)
{
	NAMESPACE::map<char,int> foo,bar;

	foo['x']=100;
	foo['y']=200;

	bar['a']=11;
	bar['b']=22;
	bar['c']=33;

	foo.swap(bar);

	std::cout << "foo contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "bar contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(foo contains:\na => 11\nb => 22\nc => 33\nbar contains:\nx => 100\ny => 200\n);
}

void map_clear(TestContainer& container)
{
	NAMESPACE::map<char,int> mymap;

	mymap['x']=100;
	mymap['y']=200;
	mymap['z']=300;

	std::cout << "mymap contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	mymap.clear();
	mymap['a']=1101;
	mymap['b']=2202;

	std::cout << "mymap contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(mymap contains:\nx => 100\ny => 200\nz => 300\nmymap contains:\na => 1101\nb => 2202\n);
}

void map_key_comp(TestContainer& container)
{
	NAMESPACE::map<char,int> mymap;

	NAMESPACE::map<char,int>::key_compare mycomp = mymap.key_comp();

	mymap['a']=100;
	mymap['b']=200;
	mymap['c']=300;

	std::cout << "mymap contains:\n";

	char highest = mymap.rbegin()->first;     // key value of last element

	NAMESPACE::map<char,int>::iterator it = mymap.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while ( mycomp((*it++).first, highest) );

	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(mymap contains:\na => 100\nb => 200\nc => 300\n\n);
}

void map_value_comp(TestContainer& container)
{
	NAMESPACE::map<char,int> mymap;

	mymap['x']=1001;
	mymap['y']=2002;
	mymap['z']=3003;

	std::cout << "mymap contains:\n";

	NAMESPACE::pair<char,int> highest = *mymap.rbegin();          // last element

	NAMESPACE::map<char,int>::iterator it = mymap.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while ( mymap.value_comp()(*it++, highest) );

//////////////////////////////////
	EXPECTED_OUTPUT(mymap contains:\nx => 1001\ny => 2002\nz => 3003\n);
}

void map_find(TestContainer& container)
{
	NAMESPACE::map<char,int> mymap;
	NAMESPACE::map<char,int>::iterator it;

	mymap['a']=50;
	mymap['b']=100;
	mymap['c']=150;
	mymap['d']=200;

	it = mymap.find('b');
	if (it != mymap.end())
		mymap.erase (it);

	// print content:
	std::cout << "elements in mymap:" << '\n';
	std::cout << "a => " << mymap.find('a')->second << '\n';
	std::cout << "c => " << mymap.find('c')->second << '\n';
	std::cout << "d => " << mymap.find('d')->second << '\n';
	if (mymap.find('b') == mymap.end())
		std::cout << "'b' not in mymap" << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(elements in mymap:\na => 50\nc => 150\nd => 200\n'b' not in mymap\n);
}

void map_count(TestContainer& container)
{
	NAMESPACE::map<char,int> mymap;
	char c;

	mymap ['a']=101;
	mymap ['c']=202;
	mymap ['f']=303;

	for (c='a'; c<'h'; c++)
	{
		std::cout << c;
		if (mymap.count(c)>0)
		std::cout << " is an element of mymap.\n";
		else 
		std::cout << " is not an element of mymap.\n";
	}

//////////////////////////////////
	EXPECTED_OUTPUT(a is an element of mymap.\nb is not an element of mymap.\nc is an element of mymap.\nd is not an element of mymap.\ne is not an element of mymap.\nf is an element of mymap.\ng is not an element of mymap.\n);
}

void map_lower_bound(TestContainer& container)
{
	NAMESPACE::map<char,int> mymap;
	NAMESPACE::map<char,int>::iterator itlow,itup;

	mymap['a']=20;
	mymap['b']=40;
	mymap['c']=60;
	mymap['d']=80;
	mymap['e']=100;

	itlow=mymap.lower_bound ('b');  // itlow points to b
	itup=mymap.upper_bound ('d');   // itup points to e (not d!)

	mymap.erase(itlow,itup);        // erases [itlow,itup)

	// print content:
	for (NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(a => 20\ne => 100\n);
}

void map_upper_bound(TestContainer& container)
{
	NAMESPACE::map<char,int> mymap;
	NAMESPACE::map<char,int>::iterator itlow,itup;

	mymap['a']=20;
	mymap['b']=40;
	mymap['c']=60;
	mymap['d']=80;
	mymap['e']=100;

	itlow=mymap.lower_bound ('b');  // itlow points to b
	itup=mymap.upper_bound ('d');   // itup points to e (not d!)

	mymap.erase(itlow,itup);        // erases [itlow,itup)

	// print content:
	for (NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(a => 20\ne => 100\n);
}

void map_equal_range(TestContainer& container)
{
	NAMESPACE::map<char,int> mymap;

	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;

	NAMESPACE::pair<NAMESPACE::map<char,int>::iterator,NAMESPACE::map<char,int>::iterator> ret;
	ret = mymap.equal_range('b');

	std::cout << "lower bound points to: '";
	std::cout << ret.first->first << "' => " << ret.first->second << '\n';

	std::cout << "upper bound points to: '";
	std::cout << ret.second->first << "' => " << ret.second->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(lower bound points to: 'b' => 20\nupper bound points to: 'c' => 30\n);
}

void map_lexicographical_compares(TestContainer& container)
{
		NAMESPACE::map<int, char> alice;
		alice.insert(NAMESPACE::make_pair(1, 'a'));
		alice.insert(NAMESPACE::make_pair(2, 'b'));
		alice.insert(NAMESPACE::make_pair(3, 'c'));
		NAMESPACE::map<int, char> bob;
		bob.insert(NAMESPACE::make_pair(7, 'Z'));
		bob.insert(NAMESPACE::make_pair(8, 'Y'));
		bob.insert(NAMESPACE::make_pair(9, 'X'));
		bob.insert(NAMESPACE::make_pair(10, 'W'));
		NAMESPACE::map<int, char> eve;
		eve.insert(NAMESPACE::make_pair(1, 'a'));
		eve.insert(NAMESPACE::make_pair(2, 'b'));
		eve.insert(NAMESPACE::make_pair(3, 'c'));
	
		std::cout << std::boolalpha;
	
		// Compare non equal containers
		std::cout << "alice == bob returns " << (alice == bob) << '\n';
		std::cout << "alice != bob returns " << (alice != bob) << '\n';
		std::cout << "alice < bob returns " << (alice < bob) << '\n';
		std::cout << "alice <= bob returns " << (alice <= bob) << '\n';
		std::cout << "alice > bob returns " << (alice > bob) << '\n';
		std::cout << "alice >= bob returns " << (alice >= bob) << '\n';
	
		std::cout << '\n';
	
		// Compare equal containers
		std::cout << "alice == eve returns " << (alice == eve) << '\n';
		std::cout << "alice != eve returns " << (alice != eve) << '\n';
		std::cout << "alice < eve returns " << (alice < eve) << '\n';
		std::cout << "alice <= eve returns " << (alice <= eve) << '\n';
		std::cout << "alice > eve returns " << (alice > eve) << '\n';
		std::cout << "alice >= eve returns " << (alice >= eve) << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(alice == bob returns false\nalice != bob returns true\nalice < bob returns true\nalice <= bob returns true\nalice > bob returns false\nalice >= bob returns false\n\nalice == eve returns true\nalice != eve returns false\nalice < eve returns false\nalice <= eve returns true\nalice > eve returns false\nalice >= eve returns true\n);
}

void avl_insert(TestContainer& container)
{
	int i;
	(void)i;
	ft::Tree<int> Tree;
	Tree.insert(28).first;
	// Tree.print2D();
	Tree.insert(76).first;
	// Tree.print2D();
	Tree.insert(3).first;
	// Tree.print2D();
	Tree.insert(93).first;
	// Tree.print2D();
	Tree.insert(96).first;
	// Tree.print2D();
	Tree.insert(30).first;
	// Tree.print2D();
	Tree.insert(49).first;
	// Tree.print2D();
	Tree.insert(29).first;
	// Tree.print2D();
	Tree.insert(20).first;
	// Tree.print2D();
	Tree.insert(21).first;
	// Tree.print2D();
	Tree.insert(27).first;
	// Tree.print2D();
	Tree.insert(7).first;
	// Tree.print2D();
	Tree.insert(34).first;
	// Tree.print2D();
	Tree.insert(82).first;
	// Tree.print2D();
	Tree.insert(9).first;
	// Tree.print2D();
	Tree.insert(24).first;
	// Tree.print2D();
	Tree.insert(26).first;
	// Tree.print2D();
	Tree.insert(31).first;
	// Tree.print2D();
	Tree.insert(74).first;
	// Tree.print2D();
	Tree.insert(39).first;
	// Tree.print2D();
	Tree.insert(85).first;
	// i = 10;
	// Tree.erase(Tree.find(i));
	// std::cout << RED << "erased: " << i << RESET << std::endl;
	// Tree.print2D();
	// i = 9;
	// Tree.erase(Tree.find(i));
	// std::cout << RED << "erased: " << i << RESET << std::endl;
	// Tree.print2D();
	// i = 3;
	// Tree.erase(Tree.find(i));
	// std::cout << RED << "erased: " << i << RESET << std::endl;
	// Tree.print2D();
	// i = 1;
	// Tree.erase(Tree.find(i));
	// std::cout << RED << "erased: " << i << RESET << std::endl;
	Tree.print2D();

//////////////////////////////////
	EXPECTED_OUTPUT(Tree:\n\n---------[E](93):2\n------------[96](E):1\n------[93](49):4\n---------------[85](82):1\n------------[82](76):2\n---------[76](93):3\n------------[74](76):1\n---[49](28):5\n------------[39](34):1\n---------[34](30):2\n------------[31](34):1\n------[30](49):3\n---------[29](30):1\n[28]():6\n---------[27](24):2\n------------[26](27):1\n------[24](20):3\n---------[21](24):1\n---[20](28):4\n------------[9](7):1\n---------[7](3):2\n------[3](20):3\n---------[RE](3):1\n);
}

void avl_erase(TestContainer& container)
{
	int i;
	(void)i;
	ft::Tree<int> Tree;
	Tree.insert(28).first;
	// Tree.print2D();
	Tree.insert(76).first;
	// Tree.print2D();
	Tree.insert(3).first;
	// Tree.print2D();
	Tree.insert(93).first;
	// Tree.print2D();
	Tree.insert(96).first;
	// Tree.print2D();
	Tree.insert(30).first;
	// Tree.print2D();
	Tree.insert(49).first;
	// Tree.print2D();
	Tree.insert(29).first;
	// Tree.print2D();
	Tree.insert(20).first;
	// Tree.print2D();
	Tree.insert(21).first;
	// Tree.print2D();
	Tree.insert(27).first;
	// Tree.print2D();
	Tree.insert(7).first;
	// Tree.print2D();
	Tree.insert(34).first;
	// Tree.print2D();
	Tree.insert(82).first;
	// Tree.print2D();
	Tree.insert(9).first;
	// Tree.print2D();
	Tree.insert(24).first;
	// Tree.print2D();
	Tree.insert(26).first;
	// Tree.print2D();
	Tree.insert(31).first;
	// Tree.print2D();
	Tree.insert(74).first;
	// Tree.print2D();
	Tree.insert(39).first;
	// Tree.print2D();
	Tree.insert(85).first;
	i = 3;
	Tree.erase(Tree.find(i));
	// Tree.print2D();
	i = 9;
	Tree.erase(Tree.find(i));
	// Tree.print2D();
	i = 93;
	Tree.erase(Tree.find(i));
	// Tree.print2D();
	i = 28;
	Tree.erase(Tree.find(i));
	i = 28;
	Tree.erase(Tree.find(i));
	i = 49;
	Tree.erase(Tree.find(i));
	i = 39;
	Tree.erase(Tree.find(i));
	i = 96;
	Tree.erase(Tree.find(i));
	i = 21;
	Tree.erase(Tree.find(i));
	i = 20;
	Tree.erase(Tree.find(i));
	i = 24;
	Tree.erase(Tree.find(i));
	Tree.print2D();

//////////////////////////////////
	EXPECTED_OUTPUT(Tree:\n\n------[E](85):1\n---[85](34):3\n---------[82](76):1\n------[76](85):2\n---------[74](76):1\n[34]():4\n---------[31](30):1\n------[30](27):2\n---------[29](30):1\n---[27](34):3\n---------[26](7):1\n------[7](27):2\n---------[RE](7):1\n);
}

void my_vector_test(TestContainer& container)
{
	NAMESPACE::vector<int> myvector;
	if (myvector.end() == myvector.begin())
		std::cout << "equal";
	if (myvector.rend() == myvector.rbegin())
		std::cout << "equal";
	std::cout << myvector.size();
	// std::cout << myvector.capacity();
	std::cout << myvector.empty();
	myvector.reserve(1);
	// std::cout << myvector.capacity();
	myvector.resize(0);
	// std::cout << myvector.capacity();
	myvector.clear();
	if (myvector.end() == myvector.begin())
		std::cout << "equal";
	if (myvector.rend() == myvector.rbegin())
		std::cout << "equal";
	myvector.insert(myvector.begin(), 9);
	std::cout << myvector[0];
	myvector.erase(myvector.begin());
	std::cout << myvector.size();
	// std::cout << myvector.capacity();
	std::cout << myvector.empty();
	myvector.insert(myvector.end(), 7);
	std::cout << myvector[0];
	std::cout << myvector.size();
	// std::cout << myvector.capacity();
	std::cout << myvector.empty();
	if (myvector.end() == myvector.begin() + 1)
		std::cout << "equal";
	myvector.pop_back();
	myvector.clear();
	std::cout << myvector.size();
	// std::cout << myvector.capacity() << "-"; // 1 but is 0
	std::cout << myvector.empty();
	myvector.resize(5);
	std::cout << myvector.size();
	// std::cout << myvector.capacity() << "-"; // 5 but is 8
	std::cout << myvector.empty();
	myvector.clear();
	std::cout << myvector.size();
	// std::cout << myvector.capacity() << "-"; // 5 but is 0
	std::cout << myvector.empty();
	myvector.assign(0, 5);
	std::cout << myvector.size();
	// std::cout << myvector.capacity() << "-"; // 5 but is 0
	std::cout << myvector.empty();
	myvector.assign(1, 6);
	std::cout << myvector.size();
	// std::cout << myvector.capacity() << "-"; // 5 but is 1
	std::cout << myvector.empty();
	std::cout << *myvector.begin();
	myvector.pop_back();
	std::cout << myvector.size();
	// std::cout << myvector.capacity() << "-"; // 5 but is 1
	std::cout << myvector.empty();
	myvector.push_back(3);
	myvector.reserve(0);
	std::cout << myvector.size();
	// std::cout << myvector.capacity() << "-"; // 5 but is 1
	std::cout << myvector.empty();
	myvector.push_back(4);
	std::cout << myvector.size();
	// std::cout << myvector.capacity() << "-"; // 5 but is 2
	std::cout << myvector.empty();
	NAMESPACE::vector<int> myvector2;

//////////////////////////////////
	EXPECTED_OUTPUT(equalequal0trueequalequal90true71falseequal0true5false0true0true1false60true1false2false);
}

void my_map_test(TestContainer& container)
{
	NAMESPACE::map<int, int> map;
	if (map.begin() == map.end())
		std::cout << "equal";
	if (map.rbegin() == map.rend())
		std::cout << "equal";
	std::cout << map.size();
	std::cout << map.empty();
	if (map.find(2) == map.end())
		std::cout << "not found";
	map.insert(NAMESPACE::make_pair(2, 2));
	std::cout << map.find(2)->first;
	map.erase(2);
	if (map.begin() == map.end())
		std::cout << "equal";
	if (map.rbegin() == map.rend())
		std::cout << "equal";
	std::cout << map.size();
	std::cout << map.empty();
	map.insert(NAMESPACE::make_pair(2, 2));
	map.erase(map.find(2));
	if (map.begin() == map.end())
		std::cout << "equal";
	if (map.rbegin() == map.rend())
		std::cout << "equal";
	std::cout << map.size();
	std::cout << map.empty();
	map.clear();
	if (map.begin() == map.end())
		std::cout << "equal";
	if (map.rbegin() == map.rend())
		std::cout << "equal";
	std::cout << map.size();
	std::cout << map.empty();
	NAMESPACE::map<int, int> map2 (map);
	if (map2.begin() == map2.end())
		std::cout << "equal";
	if (map2.rbegin() == map2.rend())
		std::cout << "equal";
	std::cout << map2.size();
	std::cout << map2.empty();
	map2.insert(NAMESPACE::make_pair(2, 2));
	map2.erase(map2.begin(), map2.end());
	if (map2.begin() == map2.end())
		std::cout << "equal";
	if (map2.rbegin() == map2.rend())
		std::cout << "equal";
	std::cout << map2.size();
	std::cout << map2.empty();

	for(int i = 0; i < BENCHMARK_NUMBER; ++i)
	{
		map2.insert(NAMESPACE::make_pair(i, i));
	}

	while (map2.empty() == false)
		map2.erase(map2.begin());

	for(int i = 0; i < BENCHMARK_NUMBER; ++i)
	{
		map2.insert(NAMESPACE::make_pair(i, i));
	}

	NAMESPACE::map<int, int>::iterator it;
	while (map2.size() > 1)
	{
		it = map2.end();
		--it;
		map2.erase(it);
	}

	NAMESPACE::map<int, int> map3;


//////////////////////////////////
	EXPECTED_OUTPUT(equalequal0truenot found2equalequal0trueequalequal0trueequalequal0trueequalequal0trueequalequal0true);
}