#include "vector.hpp"
#include "tree.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>

#define BLUE "\033[34m"
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
	tree.insert(3);
	tree.insert(7);
	tree.insert(2);
	tree.insert(4);
	tree.insert(8);
	tree.insert(6);
	tree.insert(9);

	// ft::Tree<int> tree(10);

	// for (size_t i = 1; i <= 15; ++i)
	// 	tree.insert(i);

	tree.print2D();
	// pair
	ft::Tree<ft::pair<int, std::string> > pair_tree(ft::make_pair<int, std::string>(5, "five"));
	pair_tree.insert(ft::make_pair<int, std::string>(3, "three"));
	pair_tree.insert(ft::make_pair<int, std::string>(7, "seven"));
	pair_tree.insert(ft::make_pair<int, std::string>(2, "two"));
	pair_tree.print2D();

}