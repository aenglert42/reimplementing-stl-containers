#include "vector.hpp"
#include "tree.hpp"
#include "utils.hpp"
#include "map.hpp"
#include <iostream>
#include <string>
#include <map>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define BOLD "\033[1m"
#define UNDERLINED "\033[4m"
#define RESET "\033[0m"

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
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> tree
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

	// std::map::iterator test: min = begin(), max = end(), end -1 = last
	std::cout << RED;
	std::map<std::string, int> stdMap;
	stdMap.insert(std::make_pair<std::string, int>("3", 3));
	stdMap.insert(std::make_pair<std::string, int>("5", 5));
	stdMap.insert(std::make_pair<std::string, int>("1", 1));
	std::map<std::string, int>::iterator stdit = stdMap.end();
	stdit--;
	std::cout << stdit->first << std::endl;
	stdit++;
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
}