#pragma once

#include <iostream>
#include <memory> // std::allocator
#include "ft_nullptr.hpp" // ft_nullptr
// #include "algorithm.hpp"
// #include "type_traits.hpp"

// Colors and Printing
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RED "\033[31m"
#define BOLD "\033[1m"
#define UNDERLINED "\033[4m"

#define COUNT 3

namespace ft
{
	template <class T>
	struct Node
	{
		T _content;
		Node* _parent;
		Node* _left_child;
		Node* _right_child;

		Node (T val, Node<T>* parent) : _content(val), _parent(parent), _left_child(ft_nullptr), _right_child(ft_nullptr)
		{

		}
	};

	template <class T>
	class Tree
	{
		Node<T>* _root;

		Node<T>* insert(T val, Node<T>* node, Node<T>* parent)
		{
			if (node == ft_nullptr)
				node = new Node<T>(val, parent);
			else if (val < node->_content)
			{
				node->_left_child = insert(val, node->_left_child, node);
				node->_parent = parent;
			}
			else if (val > node->_content)
			{
				node->_right_child = insert(val, node->_right_child, node);
				node->_parent = parent;
			}
			return (node);
		}

		void print(Node<T>* node)
		{
			if (node == ft_nullptr)
				return;
			print(node->_left_child);
			std::cout << node->_content << " ";
			print(node->_right_child);
		}

		// Function to print binary tree in 2D
		// It does reverse inorder traversal
		void print2DUtil(Node<T>* root, int space)
		{
			// Base case
			if (root == NULL)
				return;
		
			// Increase distance between levels
			space += COUNT;
		
			// Process right child first
			print2DUtil(root->_right_child, space);
		
			// Print current node after space
			// count
			std::cout << std::endl;
			for (int i = COUNT; i < space; i++)
				std::cout << " ";
			std::cout << root->_content << "(";
			if (root->_parent != ft_nullptr)
				std::cout << root->_parent->_content;
			std::cout << ")";
		
			// Process left child
			print2DUtil(root->_left_child, space);
		}
		
		public:
			Tree(void) : _root(ft_nullptr)
			{

			}

			Tree(T val) : _root(ft_nullptr)
			{
				_root = insert(val, _root, _root);
			}

			void insert(T val)
			{
				_root = insert(val, _root, ft_nullptr);
			}

			void print(void)
			{
				std::cout << "Root: " << _root->_content << std::endl;
				print(_root);
				std::cout << std::endl;
			}

			// Wrapper over print2DUtil()
			void print2D(void)
			{
				// Pass initial space count as 0
				print2DUtil(_root, 0);
				std::cout << std::endl;
			}

			~Tree(void)
			{
				delete _root;
			}
	};

}