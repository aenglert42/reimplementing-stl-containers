#include "vector.hpp"
#include "tree.hpp"
#include "utils.hpp"
#include "map.hpp"
#include "ft_nullptr.hpp" // ft_nullptr
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <limits>

#define MAXRAM (std::numeric_limits<int>::max())
#define MAXSIZE ((std::size_t)MAXRAM / sizeof(int))
#define PRINT_TIME(t)                                                                              \
	{                                                                                              \
		std::cout << t.get_time() << "ms" << std::endl;                                            \
	}

#define PRINT_SUM()                                                                                \
	{                                                                                              \
		std::cout << sum << "ms" << std::endl;                                                     \
	}

#define SETUP                                                                                      \
	srand(64);                                                                                     \
	volatile int x = 0;                                                                            \
	(void)x;                                                                                       \
	long sum = 0;                                                                                  \
	(void)sum;

#define BLOCK_OPTIMIZATION(v)                                                                      \
	{                                                                                              \
		if (v[0] == 64) {                                                                          \
			x = x + 64;                                                                            \
		}                                                                                          \
	}

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define BOLD "\033[1m"
#define UNDERLINED "\033[4m"
#define RESET "\033[0m"

#include <sys/time.h>

class timer
{
public:
    timer();

public:
    long get_time();
    void reset();

private:
    struct timeval stamp;
};

timer::timer()
{
    reset();
}

long timer::get_time()
{
    struct timeval now;
    struct timeval diff;

    gettimeofday(&now, NULL);
    timersub(&now, &stamp, &diff);

    return diff.tv_sec * 1000 + diff.tv_usec / 1000;
}

void timer::reset()
{
    gettimeofday(&stamp, NULL);
}

void my_leaks(void)
{
	std::cerr << BLUE;
	#if defined(__APPLE__)
	system("leaks containers_ft | grep leaked");
	#endif
	std::cerr << RESET;
}

struct Vector3
{
	float x, y, z;
	int* block;

	Vector3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		block = new int[3];
		block[0] = 0;
		block[1] = 0;
		block[2] = 0;
	};

	Vector3(float scalar) : x(scalar), y(scalar), z(scalar)
	{
		block = new int[3];
		block[0] = 0;
		block[1] = 0;
		block[2] = 0;
	};

	Vector3(float x, float y, float z) : x(x), y(y), z(z)
	{
		block = new int[3];
		block[0] = 0;
		block[1] = 0;
		block[2] = 0;
	};

	Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z)
	{
		block = new int[3];
		block[0] = other.block[0];
		block[1] = other.block[1];
		block[2] = other.block[2];
		// std::cout << "Copy\n";
	};

	~Vector3()
	{
		// std::cout << "Destroy\n";
		delete[] block;
	};

	void setBlock(int one, int two, int three)
	{
		block[0] = one;
		block[1] = two;
		block[2] = three;
	};

	Vector3& operator=(const Vector3& other)
	{
		// std::cout << "Assign\n";
		block[0] = other.block[0];
		block[1] = other.block[1];
		block[2] = other.block[2];
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}


};

std::ostream& operator<<(std::ostream& out, const Vector3& vector3)
{
	out << "x:" << vector3.x << " y:" << vector3.y << " z:" << vector3.z << " " << vector3.block[0] << vector3.block[1] << vector3.block[2];
	return (out);
}

int main(void)
{
	#if defined(__APPLE__)
	atexit(my_leaks);
	#endif
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> vector
	/*
	// constructor
	ft::vector<int> v;
	v.push_back(5);
	v.push_back(5);
	v.push_back(8);
	v.push_back(4);
	v.print();
	std::cout << std::endl;

	ft::vector<std::string> v2;
	v2.push_back("A");
	v2.push_back("B");
	v2.push_back("C");
	v2.print();
	std::cout << std::endl;

	ft::vector<Vector3> v3;
	Vector3* vec = new Vector3(2.0f);
	vec->setBlock(6, 6, 6);
	Vector3 vex;
	vex = *vec;
	v3.push_back(Vector3(1.0f));
	v3.push_back(*vec);
	vec->setBlock(5, 5, 5);
	delete vec;
	v3.push_back(vex);
	v3.push_back(Vector3());
	v3.push_back(Vector3(2, 3, 4));
	v3.push_back(Vector3(5, 7, 1));
	v3.push_back(Vector3(8, 0, 2));
	v3.print();
	std::cout << std::endl;

	for (ft::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << std::endl;
	std::cout << std::endl;

	for (ft::vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it)
		std::cout << *it << std::endl;
	std::cout << std::endl;
	*/

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> tree
	/*
	// int
	ft::Tree<int> tree(5);
	tree.insert(9);
	tree.insert(3);
	tree.insert(7);
	tree.insert(2);
	tree.insert(4);
	tree.insert(8);
	tree.insert(6);
	tree.insert(7);
	tree.insert(5);
	// tree.erase(7);
	// tree.erase(8);
	// tree.erase(9);
	tree.erase(5);
	tree.erase(3);

	// ft::Tree<int> tree(10);

	// for (size_t i = 1; i <= 15; ++i)
	// 	tree.insert(i);

	tree.print2D();
	std::cout << BLUE;
	std::cout << tree.find(2)->_content << std::endl;
	tree.pre(6);
	tree.post(6);
	ft::Tree<int>::iterator it = tree.begin();
	ft::Tree<int>::iterator it2(it);
	// ++it;
	// ++it;
	// ++it;
	// it2--;
	// it2--;
	std::cout << it2->_content << std::endl;
	std::cout << "begin: " << it->_content << std::endl;
	std::cout << RESET;
	// pair
	// ft::Tree<ft::pair<std::string, int> > pair_tree(ft::make_pair<std::string, int>("5", 5));
	// pair_tree.insert(ft::make_pair<std::string, int>("9", 9));
	// pair_tree.insert(ft::make_pair<std::string, int>("3", 3));
	// pair_tree.insert(ft::make_pair<std::string, int>("7", 7));
	// pair_tree.insert(ft::make_pair<std::string, int>("2", 2));
	// pair_tree.insert(ft::make_pair<std::string, int>("4", 4));
	// pair_tree.insert(ft::make_pair<std::string, int>("8", 8));
	// pair_tree.insert(ft::make_pair<std::string, int>("6", 6));
	// pair_tree.insert(ft::make_pair<std::string, int>("7", 7));
	// pair_tree.insert(ft::make_pair<std::string, int>("5", 5));
	// // pair_tree.erase("5");
	// pair_tree.print2D();
	*/

	/*
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> map
	ft::map<std::string, int> myMap;
	// ft::pair<int, std::string> tmpPair;
	// tmpPair = ft::make_pair(3, "3");
	// myMap.insert(tmpPair);
	myMap.insert(ft::make_pair<std::string, int>("3", 3));
	myMap.insert(ft::make_pair<std::string, int>("5", 5));
	myMap.insert(ft::make_pair<std::string, int>("1", 1));
	ft::map<std::string, int>::iterator mapit = myMap.begin();
	(void)mapit;
	// mapit--;
	std::cout << mapit->_content << std::endl;
	mapit = myMap.end();
	// myMap.erase(1);
	// myMap.print();
	*/

	/*
	// std::map::iterator test: once it is < begin() or > end() --> undefined behaviour
	std::cout << RED;
	std::map<std::string, int> stdMap;
	stdMap.insert(std::make_pair<std::string, int>("3", 3));
	stdMap.insert(std::make_pair<std::string, int>("5", 5));
	stdMap.insert(std::make_pair<std::string, int>("1", 1));
	stdMap.insert(std::make_pair<std::string, int>("6", 6));
	stdMap.insert(std::make_pair<std::string, int>("8", 8));
	std::map<std::string, int>::iterator stdit = stdMap.end();
	stdit--;
	std::cout << "8 " << stdit->first << std::endl;
	stdit++;
	stdit++;
	stdit++;
	stdit++;
	stdit++;
	stdit--;
	stdit--;
	stdit--;
	stdit--;
	stdit--;
	std::cout << "8 " << stdit->first << std::endl;
	stdit++;
	stdit++;
	stdit++;
	stdit++;
	stdit++;
	stdit--;
	stdit--;
	stdit--;
	stdit--;
	stdit--;
	std::cout << "8 " << stdit->first << std::endl;
	stdit++;
	stdit++;
	stdit++;
	stdit++;
	stdit++;
	stdit--;
	stdit--;
	stdit--;
	stdit--;
	stdit--;
	stdit--;
	std::cout << "6 " << stdit->first << std::endl;
	// end+1
	std::cout << stdit->first << std::endl;
	stdit++;
	std::cout << stdit->first << std::endl;
	// end+2
	stdit++;
	// end+3
	stdit++;
	stdit++;
	stdit++;
	stdit--;
	std::cout << stdit->first << std::endl;
	stdit--;
	std::cout << stdit->first << std::endl;
	stdit--;
	stdit--;
	stdit--;
	stdit--;
	// std::cout << stdit->first << std::endl;
	stdit++;
	std::cout << stdit->first << std::endl;
	std::cout << YELLOW;
	// std::map::iterator test: erase ivalidates iterators pointing to it
	stdit = stdMap.end();
	std::cout << "delete 3" << std::endl;
	stdMap.erase("3");
	stdit--;
	std::cout << "it: " << stdit->first << std::endl;
	stdit--;
	std::cout << "it: " << stdit->first << std::endl;
	std::cout << RESET;
	*/

	// Test for iterator old
	/*
	ft::Node<int> testNode;
	ft::Node<ft::pair<std::string, int> > testNode2;

	ft::Tree<int> testTree;
	ft::Tree<ft::pair<std::string, int> > testTree2;
	testTree2.insert(ft::make_pair<std::string, int>("9", 9));
	testTree2.insert(ft::make_pair<std::string, int>("3", 3));
	testTree2.insert(ft::make_pair<std::string, int>("7", 7));
	testTree2.insert(ft::make_pair<std::string, int>("2", 2));
	testTree2.insert(ft::make_pair<std::string, int>("4", 4));
	testTree2.insert(ft::make_pair<std::string, int>("8", 8));
	testTree2.insert(ft::make_pair<std::string, int>("6", 6));
	testTree2.insert(ft::make_pair<std::string, int>("7", 7));
	testTree2.insert(ft::make_pair<std::string, int>("5", 5));
	testTree2.print2D();


	ft::map<std::string, int> testMap;
	testMap.insert(ft::make_pair<std::string, int>("3", 3));
	testMap.insert(ft::make_pair<std::string, int>("5", 5));
	ft::pair<ft::map<std::string, int>::iterator, bool> ret = testMap.insert(ft::make_pair<std::string, int>("1", 1));
	std::cout << "found: " << ret.second << std::endl;
	// std::cout << "key: " << ret.first->_content << "found: " << ret.second << std::endl;
	ret = testMap.insert(ft::make_pair<std::string, int>("1", 1));
	std::cout << "found: " << ret.second << std::endl;
	testMap.print();
	ft::map<std::string, int>::iterator testit = testMap.end();
	(void)testit;
	testit++;
	testit--;
	testit--;
	testit--;
	testit--;
	testit++;
	testit++;
	testit++;
	testit++;
	testit++;
	testit++;
	testit--;
	// testit++;
	std::cout << testit->_content << std::endl;
	testMap.insert(testit, ft::make_pair<std::string, int>("2", 2));
	testMap.insert(testit, ft::make_pair<std::string, int>("8", 8));
	testMap.print();
	testMap.print2D();

// ft::pair comparison test primary first secondary second
	ft::pair<std::string, int> strint1 = ft::make_pair("abc", 123);
	ft::pair<std::string, int> strint2 = ft::make_pair("abc", 123);
	ft::pair<std::string, int> strint3 = ft::make_pair("abf", 123);
	ft::pair<std::string, int> strint4 = ft::make_pair("abc", 124);
	ft::pair<std::string, int> strint5 = ft::make_pair("abc", 122);

	if (strint1 < strint2)
		std::cout << "1 < 2" << std::endl;
	if (strint1 < strint3)
		std::cout << "1 < 3" << std::endl;
	if (strint1 < strint4)
		std::cout << "1 < 4" << std::endl;
	if (strint1 < strint5)
		std::cout << "1 < 5" << std::endl;
	if (strint3 < strint4)
		std::cout << "3 < 4" << std::endl;
	*/

	// Test for iterator new
	/*
	std::map<std::string, int> STD;
	STD.insert(std::make_pair("5", 5));
	STD.insert(std::make_pair("1", 1));
	STD.insert(std::make_pair("8", 8));
	std::map<std::string, int>::iterator STDit = STD.begin();
	std::cout << "STD: " << STDit->first << std::endl;
	STD.insert(STDit, std::make_pair("4", 4));
	STDit++;
	std::cout << "STD: " << STDit->first << std::endl;
	STD.insert(STDit, std::make_pair("2", 2));
	STDit = STD.find("5");
	std::cout << "STD: " << STDit->first << std::endl;
	STD.erase("5");

	ft::map<std::string, int> FT;
	FT.insert(ft::make_pair("5", 5));
	FT.insert(ft::make_pair("1", 1));
	FT.insert(ft::make_pair("8", 8));
	ft::map<std::string, int>::iterator FTit = FT.begin();
	std::cout << "FT: " << FTit->first << std::endl;
	FT.insert(FTit, ft::make_pair("4", 4));
	FT.insert(FTit, ft::make_pair("6", 6));
	FTit++;
	std::cout << "FT: " << FTit->first << std::endl;
	FT.insert(FTit, ft::make_pair("2", 2));
	std::cout << RED;
	FT.print2D();
	std::cout << RESET;
	std::cout << "erased 4? " << FT.erase("4") << std::endl;
	std::cout << "erased 4? " << FT.erase("4") << std::endl;
	FT.print2D();
	FTit = FT.begin();
	FT.erase(FTit);
	std::cout << "erased 1" << std::endl;
	FT.print2D();
	FTit = FT.begin();
	std::cout << "FT: " << FTit->first << std::endl;
	FTit++;
	std::cout << "FT: " << FTit->first << std::endl;
	FTit++;
	std::cout << "FT: " << FTit->first << std::endl;
	FT.print2D();
	FT.erase(FTit, FT.end());
	FT.print2D();
	FT.clear();
	FT.print2D();
	*/

	// const Test

	std::map<std::string, int> cstdMap;
	cstdMap.insert(std::make_pair("2", 2));
	// std::map<const std::string, int> stdMapConstNon(cstdMap);
	// std::map<std::string, const int> stdMapNonConst(cstdMap);
	// std::map<const std::string, const int> stdMapConstConst(cstdMap);
	// const std::map<const std::string, int> stdConstMapConstNon(cstdMap);
	// const std::map<std::string, const int> stdConstMapNonConst(cstdMap);
	const std::map<std::string, int> stdConstMapNonNon(cstdMap);
	// const std::map<const std::string, const int> stdConstMapConstConst(cstdMap);
	std::map<std::string, int>::const_iterator stdConstMapConstIt = stdConstMapNonNon.begin();
	// std::map<std::string, int>::iterator stdConstMapIt = stdConstMapConstIt;
	// (void)stdConstMapIt;
	std::map<std::string, int>::iterator stdMapIt = cstdMap.begin();
	std::map<std::string, int>::const_iterator stdMapConstIt = cstdMap.begin();
	(void)stdConstMapConstIt;
	(void)stdMapIt;
	(void)stdMapConstIt;

	// int i = 2;
	// const int* ptr = &i;
	// ptr++;
	// *ptr = 1;

	// int i2 = 2;
	// int* const ptr2 = &i2;
	// ptr2++;
	// *ptr2 = 1;

	ft::map<std::string, int> ftMap;
	ftMap.insert(ft::make_pair("2", 2));
	// // ft::map<const std::string, int> ftMapConstNon(ftMap);
	// // ft::map<std::string, const int> ftMapNonConst(ftMap);
	// // ft::map<const std::string, const int> ftMapConstConst(ftMap);
	// // const ft::map<const std::string, int> ftConstMapConstNon(ftMap);
	// // const ft::map<std::string, const int> ftConstMapNonConst(ftMap);
	const ft::map<std::string, int> ftConstMapNonNon(ftMap);
	// // const ft::map<const std::string, const int> ftConstMapConstConst(ftMap);
	ft::map<std::string, int>::iterator ftMapIt = ftMap.begin();
	ft::map<std::string, int>::const_iterator ftConstMapConstIt = ftConstMapNonNon.begin();
	(void)ftConstMapConstIt;
	(void)ftMapIt;
	ft::map<std::string, int>::const_iterator ftMapConstIt = ftMap.begin();
	(void)ftMapConstIt;


	ft::map<int, std::string> ftEMap;
	ftEMap.insert(ft::make_pair(2, "2"));
	ftEMap.insert(ft::make_pair(5, "5"));
	ftEMap.insert(ft::make_pair(-1, "-1"));
	ftEMap.insert(ft::make_pair(-5, "-5"));
	ftEMap.insert(ft::make_pair(1, "1"));
	ftEMap.print2D();

	ft::map<int, std::string>::iterator ftbegin = ftEMap.begin();
	// ftbegin++;
	std::cout << "ftbegin: " << ftbegin->first << std::endl;
	ft::map<int, std::string>::iterator ftend = ftbegin;

	// ftend++;
	// ftend++;
	// ftend++;
	// std::cout << "ftend: " << ftend->first << std::endl;
	ftend = ftEMap.end();

	ftEMap.erase(ftbegin, ftend);
	ftEMap.print2D();


	{
		ft::vector<int> ftVector;

		ftVector.push_back(2);
		ftVector.push_back(5);
		ftVector.push_back(-1);

		std::cout << "Size: " << ftVector.rend() - ftVector.rbegin() << std::endl;
		std::cout << "Size: " << ftVector.rbegin() - ftVector.rend() << std::endl;
		std::cout << "Size: " << ftVector.end() - ftVector.begin() << std::endl;
		std::cout << "Size: " << ftVector.begin() - ftVector.end() << std::endl;

		std::vector<int> stdVector;

		stdVector.push_back(2);
		stdVector.push_back(5);
		stdVector.push_back(-1);

		std::cout << "Size: " << stdVector.rend() - stdVector.rbegin() << std::endl;
		std::cout << "Size: " << stdVector.rbegin() - stdVector.rend() << std::endl;
		std::cout << "Size: " << stdVector.end() - stdVector.begin() << std::endl;
		std::cout << "Size: " << stdVector.begin() - stdVector.end() << std::endl;
	}



	{
		#define NAMESPACE ft

		SETUP;

		NAMESPACE::map<int, int> data;

		for (std::size_t i = 0; i < MAXSIZE / 2; ++i) {
			data.insert(NAMESPACE::make_pair(rand(), rand()));
		}

		timer t;

		{
			NAMESPACE::map<int, int> m;
			for (int i = 0; i < 5; ++i) {
				m = data;
			}
		}

		PRINT_TIME(t);
	}
}