#include <iostream>
#include <sstream>		// std::stringstream
#include <type_traits> //remove

/* ###################################### PAIR ###################################### */


// // check to see if assignation operator of std::pair deletes potential old ptr in pair.second, or not
// int main(void)
// {
//     int *one = new int(1);
//     int *two = new int(2);
//     int *three = new int(3);
//     std::pair<char, int *>  paerle;
//     std::pair<char, int *>  paerle2;

//     paerle = std::make_pair('a', one);
//     paerle2 = std::make_pair('b', two);
//     std::cout << *(paerle.second) << std::endl;
//     std::cout << paerle.first << std::endl;

//     paerle = paerle2;
//     // paerle.second = two;
//     std::cout << *(paerle.second) << std::endl;
//     std::cout << paerle.first << std::endl;
//     std::cout << *one << std::endl;

//     paerle = std::make_pair('c', three);
//     std::cout << *(paerle.second) << std::endl;
//     std::cout << paerle.first << std::endl;

// }
// // ===> RESULT: No! Just assigns new values, but doesn't delete anything.


/* ---------------------------------------------------------------------------------- */
// /* test FT::PAIR implementation */
// // CONSTRUCTORS
// #include <string>       // std::string
// #include <iostream>     // std::cout

// #include "utils.hpp"      // ft::pair, ft::make_pair

// int main () {
// 	std::stringstream stream;
// 	ft::pair <std::string,double> product1;                     // default constructor
// 	ft::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
// 	ft::pair <std::string,double> product3 (product2);          // copy constructor

// 	product1 = ft::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)

// 	product2.first = "shoes";                  // the type of first is string
// 	product2.second = 39.90;                   // the type of second is double

// 	stream.clear();
// 	stream.str("");
// 	stream << "The price of " << product1.first << " is $" << product1.second;
// 	std::cout << stream.str();
// 	if (stream.str() == "The price of lightbulbs is $0.99")
// 		std::cout << "\t OK";
// 	std::cout << std::endl;
// 	stream.clear();
// 	stream.str("");
// 	stream << "The price of " << product2.first << " is $" << product2.second;
// 	std::cout << stream.str();
// 	if (stream.str() == "The price of shoes is $39.9")
// 		std::cout << "\t\t OK";
// 	std::cout << std::endl;
// 	stream.clear();
// 	stream.str("");
// 	stream << "The price of " << product3.first << " is $" << product3.second;
// 	std::cout << stream.str();
// 	if (stream.str() == "The price of tomatoes is $2.3")
// 		std::cout << "\t\t OK";
// 	std::cout << std::endl;
// 	return 0;
// }

// // Output: ***********************
// // The price of lightbulbs is $0.99
// // The price of shoes is $39.9
// // The price of tomatoes is $2.3

/* ---------------------------------------------------------------------------------- */
// // pair::operator= example
// #include <string>       // std::string
// #include <iostream>     // std::cout

// #include "utils.hpp"      // ft::pair, ft::make_pair

// int main () {
//   ft::pair <std::string,int> planet, homeplanet;

//   planet = ft::make_pair("Earth",6371);

//   homeplanet = planet;

//   std::cout << "Home planet: " << homeplanet.first << '\n';
//   std::cout << "Planet size: " << homeplanet.second << '\n';
//   return 0;
// }

// // Output: ***********************
// // Home planet: Earth
// // Planet size: 6371

/* ---------------------------------------------------------------------------------- */
// // // pair relational operators
// #include <iostream>     // std::cout

// #include "utils.hpp"      // ft::pair, ft::make_pair

// int main ()
// {
//   ft::pair<int,char> foo (10,'z');
//   ft::pair<int,char> bar (90,'a');

//   if (foo==bar) std::cout << "foo and bar are equal\n";
//   if (foo!=bar) std::cout << "foo and bar are not equal\n";
//   if (foo< bar) std::cout << "foo is less than bar\n";
//   if (foo> bar) std::cout << "foo is greater than bar\n";
//   if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
//   if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

//   return 0;
// }

// // Output: ***********************
// // foo and bar are not equal
// // foo is less than bar
// // foo is less than or equal to bar

/* ---------------------------------------------------------------------------------- */
// // make_pair example
// #include <iostream>     // std::cout

// #include "utils.hpp"      // ft::pair, ft::make_pair

// int main ()
// {
//   ft::pair <int,int> foo;
//   ft::pair <int,int> bar;

//   foo = ft::make_pair (10,20);
//   bar = ft::make_pair (10.5,'A'); // ok: implicit conversion from pair<double,char>

//   std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
//   std::cout << "bar: " << bar.first << ", " << bar.second << '\n';

//   return 0;
// }

// Output: ***********************
// foo: 10, 20
// bar: 10, 65

/* ###################################### TYPE_TRAITS ###################################### */

// // check SFINAE
// template <class T>
// struct is_pointer
// {
//   template <class U>
//   static char is_ptr(U *);

//   template <class X, class Y>
//   static char is_ptr(Y X::*);

//   template <class U>
//   static char is_ptr(U (*)());

//   static double is_ptr(...);

//   static T t;
//   enum { value = sizeof(is_ptr(t)) == sizeof(char) };
// };

// struct Foo {
//   int bar;
// };

// int main(void)
// {
//   typedef int * IntPtr;
//   typedef int Foo::* FooMemberPtr;
//   typedef int (*FuncPtr)();
//   typedef int one;
//   typedef char  *two;

//   char a = 'a';
//   two two_two = &a;

//   printf("%c, %c\n", a, *two_two);              // prints a, a
//   printf("%d\n",is_pointer<IntPtr>::value);        // prints 1
//   printf("%d\n",is_pointer<FooMemberPtr>::value);  // prints 1
//   printf("%d\n",is_pointer<FuncPtr>::value);       // prints 1
//   printf("%d\n",is_pointer<one>::value);       // prints 0
//   printf("%d\n",is_pointer<two>::value);       // prints 1
// }

// // Output: ***********************
// // a, a
// // 1
// // 1
// // 1
// // 0
// // 1

/* ---------------------------------------------------------------------------------- */
// // is_integral example
// #include <iostream>

// #include "ft_type_traits.hpp"

// int main()
// {
//   std::cout << std::boolalpha;
//   std::cout << "is_integral:" << std::endl;
//   std::cout << "char: " << ft::is_integral<char>::value << std::endl;
//   std::cout << "int: " << ft::is_integral<int>::value << std::endl;
//   std::cout << "float: " << ft::is_integral<float>::value << std::endl;
//   std::cout << "double: " << ft::is_integral<double>::value << std::endl;
//   return 0;
// }

// // Output: ***********************
// // is_integral:
// // char: true
// // int: true
// // float: false
// // double: false

/* ---------------------------------------------------------------------------------- */
// // enable_if example: two ways of using enable_if
// #include <iostream>

// #include "ft_type_traits.hpp"

// // 1. the return type (bool) is only valid if T is an integral type:
// template <class T>
// typename ft::enable_if<std::is_integral<T>::value,bool>::type
//   is_odd (T i) {return bool(i%2);}

// // 2. the second template argument is only valid if T is an integral type:
// template < class T,
//            class = typename ft::enable_if<std::is_integral<T>::value>::type> // some C++11 magic!
// bool is_even (T i) {return !bool(i%2);}

// int main() {

//   short int i = 1;    // code does not compile if type of i is not integral

//   std::cout << std::boolalpha;
//   std::cout << "i is odd: " << is_odd(i) << std::endl;
//   std::cout << "i is even: " << is_even(i) << std::endl;

//   return 0;
// }

// // Output: ***********************
// // i is odd: true
// // i is even: false

/* ###################################### ALGORITHMS ###################################### */

// equal algorithm example
// #include <iostream>     // std::cout
// #include <vector>       // std::vector

// #include "ft_algorithm.hpp"    // ft::equal

// bool mypredicate (int i, int j) {
//   return (i==j);
// }

// int main () {
//   int myints[] = {20,40,60,80,100};               //   myints: 20 40 60 80 100
//   std::vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

//   // using default comparison:
//   if ( ft::equal (myvector.begin(), myvector.end(), myints) )
//     std::cout << "The contents of both sequences are equal.\n";
//   else
//     std::cout << "The contents of both sequences differ.\n";

//                                                    //   myints: 20 40 60 80 100
//   myvector[3]=81;                                 // myvector: 20 40 60 81 100

//   // using predicate comparison:
//   if ( ft::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
//     std::cout << "The contents of both sequences are equal.\n";
//   else
//     std::cout << "The contents of both sequences differ.\n";

//   return 0;
// }

// // Output: ***********************
// // The contents of both sequences are equal.
// // The contents of both sequence differ.


/* ---------------------------------------------------------------------------------- */
// // lexicographical_compare example
// #include <iostream>     // std::cout, std::boolalpha
// #include <cctype>       // std::tolower

// #include "ft_algorithm.hpp"    // ft::equal

// // a case-insensitive comparison function:
// bool mycomp (char c1, char c2)
// { return std::tolower(c1)<std::tolower(c2); }

// int main () {
//   char foo[]="Apple";
//   char bar[]="apartment";

//   std::cout << std::boolalpha;

//   std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

//   std::cout << "Using default comparison (operator<): ";
//   std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9);
//   std::cout << '\n';

//   std::cout << "Using mycomp as comparison object: ";
//   std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
//   std::cout << '\n';

//   return 0;
// }

// // Output: ***********************
// // Comparing foo and bar lexicographically (foo<bar):
// // Using default comparison (operator<): true
// // Using mycomp as comparison object: false

/* ###################################### ITERATOR_TRAITS ###################################### */

// // iterator_traits example
// #include <iostream>     // std::cout
// #include <typeinfo>     // typeid
// // #include <iterator>     // std::iterator_traits

// #include "ft_iterator.hpp"
// int main() {
//   typedef ft::iterator_traits<int*> traits;
//   if (typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag))
//     std::cout << "int* is a random-access iterator" << std::endl;
//   return 0;
// }

// // Output: ***********************
// // int* is a random-access iterator


/* ###################################### REVERSE_ITERATOR ##################################### */

// // reverse_iterator example
// #include <iostream>     // std::cout
// #include <vector>       // std::vector

// #include "inc/utils/iterator.hpp"

// int main () {
//   std::vector<int> myvector;
//   for (int i=0; i<10; i++) myvector.push_back(i);

//   typedef std::vector<int>::iterator iter_type;
//                                                          // ? 0 1 2 3 4 5 6 7 8 9 ?
//   iter_type from (myvector.begin());                     //   ^
//                                                          //         ------>
//   iter_type until (myvector.end());                      //                       ^
//                                                          //
//   ft::reverse_iterator<iter_type> rev_until (from);     // ^
//                                                          //         <------
//   ft::reverse_iterator<iter_type> rev_from (until);     //                     ^

//   std::cout << "myvector:";
//   while (rev_from != rev_until)
//     std::cout << ' ' << *rev_from++;
//   std::cout << '\n';

//   return 0;
// }

// // Output: ***********************
// // myvector: 9 8 7 6 5 4 3 2 1 0
