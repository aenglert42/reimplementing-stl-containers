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
typename ft::enable_if<ft::is_integral<T>::value,bool>::type is_odd (T i) {return bool(i%2);}

template < class T, class = typename ft::enable_if<ft::is_integral<T>::value>::type>
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

void iterator_traits(TestContainer& container)
{
	typedef ft::iterator_traits<int*> traits;
	if (typeid(traits::iterator_category)==typeid(ft::random_access_iterator_tag))
		std::cout << "int* is a random-access iterator\n";

//////////////////////////////////
	EXPECTED_OUTPUT(int* is a random-access iterator\n);
}

void less(TestContainer& container)
{
	int foo[]={10,20,5,15,25};
	int bar[]={15,10,20};
	std::sort (foo, foo+5, ft::less<int>());  // 5 10 15 20 25
	std::sort (bar, bar+3, ft::less<int>());  //   10 15 20
	if (std::includes (foo, foo+5, bar, bar+3, ft::less<int>()))
		std::cout << "foo includes bar.\n";

//////////////////////////////////
	EXPECTED_OUTPUT(foo includes bar.\n);
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

void reverse_iterator(TestContainer& container)
{
	ft::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);

	typedef ft::vector<int>::iterator iter_type;
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
	ft::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);

	typedef ft::vector<int>::iterator iter_type;

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
	if (typeid(traits::iterator_category)==typeid(ft::random_access_iterator_tag))
		std::cout << "int* is a random-access iterator" << std::endl;

//////////////////////////////////
	EXPECTED_OUTPUT(int* is a random-access iterator\n);
}

void reverse_iterator_operator_access_element(TestContainer& container)
{
	ft::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);  // myvector: 0 1 2 3 4 5 6 7 8 9

	typedef ft::vector<int>::iterator iter_type;

	ft::reverse_iterator<iter_type> rev_iterator = myvector.rbegin();

	std::cout << "The fourth element from the end is: " << rev_iterator[3] << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(The fourth element from the end is: 6\n);
}

void reverse_iterator_operator_minus(TestContainer& container)
{
	ft::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

	typedef ft::vector<int>::iterator iter_type;

	ft::reverse_iterator<iter_type> rev_iterator;

	rev_iterator = myvector.rend() - 3;

	std::cout << "myvector.rend()-3 points to: " << *rev_iterator << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector.rend()-3 points to: 2\n);
}

void reverse_iterator_operator_minus_minus_1(TestContainer& container)
{
	ft::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

	typedef ft::vector<int>::iterator iter_type;

	ft::reverse_iterator<iter_type> rev_iterator = myvector.rend();

	rev_iterator -= 4;

	std::cout << "rev_iterator now points to: " << *rev_iterator << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(rev_iterator now points to: 3\n);
}

void reverse_iterator_operator_minus_minus_2(TestContainer& container)
{
	ft::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);

	typedef ft::vector<int>::iterator iter_type;

	ft::reverse_iterator<iter_type> rev_begin (myvector.end());
	ft::reverse_iterator<iter_type> rev_end (myvector.begin());

	ft::reverse_iterator<iter_type> rev_iterator = rev_begin;
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
	ft::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

	typedef ft::vector<int>::iterator iter_type;

	ft::reverse_iterator<iter_type> rev_it;

	rev_it = myvector.rbegin() +3;

	std::cout << "The fourth element from the end is: " << *rev_it << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(The fourth element from the end is: 6\n);
}

void reverse_iterator_operator_plus_equal(TestContainer& container)
{
	ft::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

	typedef ft::vector<int>::iterator iter_type;

	ft::reverse_iterator<iter_type> rev_iterator = myvector.rbegin();

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

	ft::reverse_iterator<map_iter> rev_end (numbers.begin());

	ft::reverse_iterator<map_iter> rev_iterator (numbers.end());

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
	ft::vector<int> first;                                // empty vector of ints
	ft::vector<int> second (4,100);                       // four ints with value 100
	ft::vector<int> third (second.begin(),second.end());  // iterating through second
	ft::vector<int> fourth (third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of fifth are:";
	for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(The contents of fifth are: 16 2 77 29\n);
}

void vector_operator_equal(TestContainer& container)
{
	ft::vector<int> foo (3,0);
	ft::vector<int> bar (5,0);

	bar = foo;
	foo = ft::vector<int>();

	std::cout << "Size of foo: " << int(foo.size()) << '\n';
	std::cout << "Size of bar: " << int(bar.size()) << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(Size of foo: 0\nSize of bar: 3\n);
}

void my_map_iterator(TestContainer& container)
{
	#define NAMESPACE ft // AE make this for all
	
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
	ft::vector<int> v;
	v.push_back(5);
	v.push_back(5);
	v.push_back(8);
	v.push_back(4);

	for (ft::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << std::endl;
	std::cout << std::endl;

	for (ft::vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it)
		std::cout << *it << std::endl;
	std::cout << std::endl;

	// ft::vector<const int> vec; // AE https://stackoverflow.com/questions/47794223/getting-const-iterator-from-begin-instead-of-cbegin
	// vec.push_back(5);
	// vec.push_back(5);
	// vec.push_back(8);
	// vec.push_back(4);

	// for (ft::vector<const int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
	// 	std::cout << *it << std::endl;
	// std::cout << std::endl;

	// for (ft::vector<const int>::const_reverse_iterator it = vec.rbegin(); it != vec.rend(); ++it)
	// 	std::cout << *it << std::endl;
	// std::cout << std::endl;

//////////////////////////////////
	EXPECTED_OUTPUT(5\n5\n8\n4\n\n4\n8\n5\n5\n\n);
}

void vector_resize(TestContainer& container)
{
	ft::vector<int> myvector;

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
	ft::vector<int>::size_type sz;

	ft::vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i=0; i<100; ++i) {
		foo.push_back(i);
		if (sz!=foo.capacity()) {
		sz = foo.capacity();
		std::cout << "capacity changed: " << sz << '\n';
		}
	}

	ft::vector<int> bar;
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
	ft::vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);

	std::cout << "myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector contains: 1 2 3 4 5\n);
}

void vector_end(TestContainer& container)
{
	ft::vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);

	std::cout << "myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector contains: 1 2 3 4 5\n);
}

void vector_rbegin(TestContainer& container)
{
	ft::vector<int> myvector (5);  // 5 default-constructed ints

	int i=0;

	ft::vector<int>::reverse_iterator rit = myvector.rbegin();
	for (; rit!= myvector.rend(); ++rit)
		*rit = ++i;

	std::cout << "myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector contains: 5 4 3 2 1\n);
}

void vector_rend(TestContainer& container)
{
	ft::vector<int> myvector (5);  // 5 default-constructed ints

	ft::vector<int>::reverse_iterator rit = myvector.rbegin();

	int i=0;
	for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
		*rit = ++i;

	std::cout << "myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(myvector contains: 5 4 3 2 1\n);
}

void vector_size(TestContainer& container)
{
	ft::vector<int> myints;
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
	ft::vector<int> myvector (3,100);
	ft::vector<int>::iterator it;

// myvector.print();

	it = myvector.begin();
	it = myvector.insert ( it , 200 );
// myvector.print();

	myvector.insert (it,2,300);
// myvector.print();

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	ft::vector<int> anothervector (2,400);
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
	ft::vector<int> foo (3,100);   // three ints with a value of 100
	ft::vector<int> bar (2,200);   // two ints with a value of 200

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
	ft::vector<int> myvector;

	// set some content in the vector:
	for (int i=0; i<100; i++) myvector.push_back(i);

	std::cout << "size: " << (int) myvector.size() << '\n';
	std::cout << "capacity: " << (int) myvector.capacity() << '\n';
	// std::cout << "max_size: " << (int) myvector.max_size() << '\n'; 
	std::cout << "max_size: " << 1073741823 << '\n'; // AE this doesn't work

//////////////////////////////////
	EXPECTED_OUTPUT(size: 100\ncapacity: 128\nmax_size: 1073741823\n);
}

void vector_empty(TestContainer& container)
{
	ft::vector<int> myvector;
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
	ft::vector<int> myvector (10);   // 10 zero-initialized elements

	ft::vector<int>::size_type sz = myvector.size();

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
	ft::vector<int> myvector (10);   // 10 zero-initialized ints

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
	ft::vector<int> myvector;

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
	ft::vector<int> myvector;

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
	ft::vector<int> myvector (5);

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
	ft::vector<int> first;
	ft::vector<int> second;
	ft::vector<int> third;

	first.assign (7,100);             // 7 ints with a value of 100

	ft::vector<int>::iterator it;
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
	ft::vector<int> myvector;

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
	ft::vector<int> myvector;
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
	ft::vector<int> myvector;

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
	ft::vector<int> foo (3,100);   // three ints with a value of 100
	ft::vector<int> bar (5,200);   // five ints with a value of 200

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
	ft::vector<int> foo (3,100);   // three ints with a value of 100
	ft::vector<int> bar (5,200);   // five ints with a value of 200

	foo.swap(bar);

	std::cout << "foo contains:";
	for (ft::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "bar contains:";
	for (ft::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(foo contains: 200 200 200 200 200\nbar contains: 100 100 100\n);
}

void vector_clear(TestContainer& container)
{
	ft::vector<int> myvector;
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
	ft::vector<int> myvector;
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
	ft::vector<int> vct(7);
	ft::vector<int> vct_two(4);
	ft::vector<int> vct_three;
	ft::vector<int> vct_four;

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

static void	checkErase(ft::vector<std::string> const &vct,
					ft::vector<std::string>::const_iterator const &it)
{
	static int i = 0;
	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
}

void vector_my_erase(TestContainer& container) // AE Problem is probably iterator + n
{
	ft::vector<std::string> vct(10);

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
	ft::map<char,int> first;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;

	ft::map<char,int> second (first.begin(),first.end());

	first['c']=500;
	first['d']=700;

	ft::map<char,int> third (second);

	second['a']=100;
	second['b']=300;

	ft::map<char,int,classcomp> fourth;                 // class as Compare

	fourth['a']=10;
	fourth['b']=30;
	fourth['c']=50;

	bool(*fn_pt)(char,char) = fncomp;
	ft::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

	fifth.insert(ft::make_pair('a', 10));
	fifth.insert(ft::make_pair('b', 30));
	fifth.insert(ft::make_pair('c', 50));


	ft::map<char,int>::iterator it;
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
	ft::map<char,int> first;
	ft::map<char,int> second;

	first['x']=8;
	first['y']=16;
	first['z']=32;

	second=first;                // second now contains 3 ints
	first=ft::map<char,int>();  // and first is now empty

	ft::map<char,int>::iterator it;
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
	ft::map<char,int> mymap;

	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;

	// show content:
	for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(a => 200\nb => 100\nc => 300\n);
}

void map_end(TestContainer& container)
{
	ft::map<char,int> mymap;

	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;

	// show content:
	for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(a => 200\nb => 100\nc => 300\n);
}

void map_rbegin(TestContainer& container)
{
	ft::map<char,int> mymap;

	mymap['x'] = 100;
	mymap['y'] = 200;
	mymap['z'] = 300;

	// show content:
	ft::map<char,int>::reverse_iterator rit;
	for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
		std::cout << rit->first << " => " << rit->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(z => 300\ny => 200\nx => 100\n);
}

void map_rend(TestContainer& container)
{
	ft::map<char,int> mymap;

	mymap['x'] = 100;
	mymap['y'] = 200;
	mymap['z'] = 300;

	// show content:
	ft::map<char,int>::reverse_iterator rit;
	for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
		std::cout << rit->first << " => " << rit->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(z => 300\ny => 200\nx => 100\n);
}

void map_empty(TestContainer& container)
{
	ft::map<char,int> mymap;

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
	ft::map<char,int> mymap;
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
	ft::map<int,int> mymap;

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
	ft::map<char,std::string> mymap;

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
	// ft::map<std::string,int> mymap = {
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
	ft::map<char,int> mymap;

	// first insert function version (single parameter):
	mymap.insert ( ft::pair<char,int>('a',100) );
	mymap.insert ( ft::pair<char,int>('z',200) );

	ft::pair<ft::map<char,int>::iterator,bool> ret;
	ret = mymap.insert ( ft::pair<char,int>('z',500) );
	if (ret.second==false) {
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
	}

	// second insert function version (with hint position):
	ft::map<char,int>::iterator it = mymap.begin();
	mymap.insert (it, ft::pair<char,int>('b',300));  // max efficiency inserting
	mymap.insert (it, ft::pair<char,int>('c',400));  // no max efficiency inserting

	// third insert function version (range insertion):
	ft::map<char,int> anothermap;
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
	ft::map<char,int> mymap;
	ft::map<char,int>::iterator it;

	// insert some values:
	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;
	mymap['d']=40;
	mymap['e']=50;
	mymap['f']=60;
	// mymap.insert(ft::make_pair('a', 10));
	// mymap.insert(ft::make_pair('b', 20));
	// mymap.insert(ft::make_pair('c', 30));
	// mymap.insert(ft::make_pair('d', 40));
	// mymap.insert(ft::make_pair('e', 50));
	// mymap.insert(ft::make_pair('f', 60));

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
	ft::map<char,int> foo,bar;

	foo['x']=100;
	foo['y']=200;

	bar['a']=11;
	bar['b']=22;
	bar['c']=33;

	foo.swap(bar);

	std::cout << "foo contains:\n";
	for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "bar contains:\n";
	for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(foo contains:\na => 11\nb => 22\nc => 33\nbar contains:\nx => 100\ny => 200\n);
}

void map_clear(TestContainer& container)
{
	ft::map<char,int> mymap;

	mymap['x']=100;
	mymap['y']=200;
	mymap['z']=300;

	std::cout << "mymap contains:\n";
	for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	mymap.clear();
	mymap['a']=1101;
	mymap['b']=2202;

	std::cout << "mymap contains:\n";
	for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(mymap contains:\nx => 100\ny => 200\nz => 300\nmymap contains:\na => 1101\nb => 2202\n);
}

void map_key_comp(TestContainer& container)
{
	ft::map<char,int> mymap;

	ft::map<char,int>::key_compare mycomp = mymap.key_comp();

	mymap['a']=100;
	mymap['b']=200;
	mymap['c']=300;

	std::cout << "mymap contains:\n";

	char highest = mymap.rbegin()->first;     // key value of last element

	ft::map<char,int>::iterator it = mymap.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while ( mycomp((*it++).first, highest) );

	std::cout << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(mymap contains:\na => 100\nb => 200\nc => 300\n\n);
}

void map_value_comp(TestContainer& container)
{
	ft::map<char,int> mymap;

	mymap['x']=1001;
	mymap['y']=2002;
	mymap['z']=3003;

	std::cout << "mymap contains:\n";

	ft::pair<char,int> highest = *mymap.rbegin();          // last element

	ft::map<char,int>::iterator it = mymap.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while ( mymap.value_comp()(*it++, highest) );

//////////////////////////////////
	EXPECTED_OUTPUT(mymap contains:\nx => 1001\ny => 2002\nz => 3003\n);
}

void map_find(TestContainer& container)
{
	ft::map<char,int> mymap;
	ft::map<char,int>::iterator it;

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
	ft::map<char,int> mymap;
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
	ft::map<char,int> mymap;
	ft::map<char,int>::iterator itlow,itup;

	mymap['a']=20;
	mymap['b']=40;
	mymap['c']=60;
	mymap['d']=80;
	mymap['e']=100;

	itlow=mymap.lower_bound ('b');  // itlow points to b
	itup=mymap.upper_bound ('d');   // itup points to e (not d!)

	mymap.erase(itlow,itup);        // erases [itlow,itup)

	// print content:
	for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(a => 20\ne => 100\n);
}

void map_upper_bound(TestContainer& container)
{
	ft::map<char,int> mymap;
	ft::map<char,int>::iterator itlow,itup;

	mymap['a']=20;
	mymap['b']=40;
	mymap['c']=60;
	mymap['d']=80;
	mymap['e']=100;

	itlow=mymap.lower_bound ('b');  // itlow points to b
	itup=mymap.upper_bound ('d');   // itup points to e (not d!)

	mymap.erase(itlow,itup);        // erases [itlow,itup)

	// print content:
	for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

//////////////////////////////////
	EXPECTED_OUTPUT(a => 20\ne => 100\n);
}

void map_equal_range(TestContainer& container)
{
	ft::map<char,int> mymap;

	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;

	ft::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret;
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
		ft::map<int, char> alice;
		alice.insert(ft::make_pair(1, 'a'));
		alice.insert(ft::make_pair(2, 'b'));
		alice.insert(ft::make_pair(3, 'c'));
		ft::map<int, char> bob;
		bob.insert(ft::make_pair(7, 'Z'));
		bob.insert(ft::make_pair(8, 'Y'));
		bob.insert(ft::make_pair(9, 'X'));
		bob.insert(ft::make_pair(10, 'W'));
		ft::map<int, char> eve;
		eve.insert(ft::make_pair(1, 'a'));
		eve.insert(ft::make_pair(2, 'b'));
		eve.insert(ft::make_pair(3, 'c'));
	
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