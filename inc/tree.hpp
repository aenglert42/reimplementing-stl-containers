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

		Node<T>* min_val_node(Node<T>* node)
		{
			Node<T>* current = node;

			while (current && current->_left_child != ft_nullptr)
				current = current->_left_child;
			return (current);
		}

		Node<T>* remove_node_with_child(Node<T>* node, Node<T>* child)
		{
			delete node;
			return (child);
		}

		Node<T>* remove_node_with_children(Node<T>* node)
		{
			Node<T>* tmp = min_val_node(node->_right_child);
			node->_content = tmp->_content;
			node->_right_child = erase(tmp->_content, node->_right_child);
			return (node);
		}

		Node<T>* remove_node(Node<T>* node)
		{
			if (node->_left_child == ft_nullptr && node->_right_child == ft_nullptr)
				return(ft_nullptr);
			else if (node->_left_child == ft_nullptr)
				return(remove_node_with_child(node, node->_right_child));
			else if (node->_right_child == ft_nullptr)
				return(remove_node_with_child(node, node->_left_child));
			else
				return(remove_node_with_children(node));
		}

		Node<T>* erase(T val, Node<T>* node)
		{
			if (node == ft_nullptr)
				return (node);
			else if (val < node->_content)
				node->_left_child = erase(val, node->_left_child);
			else if (val > node->_content)
				node->_right_child = erase(val, node->_right_child);
			else
				node = remove_node(node);
			return (node);
		}

		// Node<T>* find(T val)
		// {
		// 	if (_root == ft_nullptr)
		// 		return (_root);;
		// 	// else if (val < node->_content)
		// 	// {
		// 	// 	node->_left_child = insert(val, node->_left_child, node);
		// 	// 	node->_parent = parent;
		// 	// }
		// 	// else if (val > node->_content)
		// 	// {
		// 	// 	node->_right_child = insert(val, node->_right_child, node);
		// 	// 	node->_parent = parent;
		// 	// }
		// 	// return (node);
		// }

		// void remove_node(Node<T>* node)
		// {
		// 	if (node == ft_nullptr)
		// 		return ;
		// 	else if (node == _root)
		// 	{

		// 	}
		// 	else if (node->_left_child == ft_nullptr && node->_right_child == ft_nullptr)
		// 	{
		// 		remove_leave_node(node);
		// 	}
		// 	else if (node->_left_child == ft_nullptr)
		// 	{
		// 		remove_node_with_child(node, node->_right_child);
		// 	}
		// 	else if (node->_right_child == ft_nullptr)
		// 	{
		// 		remove_node_with_child(node, node->_left_child);
		// 	}
		// 	else
		// 	{

		// 	}
		// }

		// void remove_leave_node(Node<T>* node)
		// {
		// 	if (node->_parent->_left_child == node)
		// 		node->_parent->_left_child = ft_nullptr;
		// 	else
		// 		node->_parent->_right_child = ft_nullptr;
		// 	delete node;
		// }

		// void remove_node_with_child(Node<T>* node, Node<T>* child)
		// {
		// 	if (node->_parent->_left_child == node)
		// 		node->_parent->_left_child = child;
		// 	else
		// 		node->_parent->_right_child = child;
		// 	child->_parent = node->_parent;
		// 	delete node;
		// }

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

			void erase(T val)
			{
				// Node<T>* tmp = find(val);
				// if (tmp == ft_nullptr)
				// 	return ;
				// remove_node(tmp);
				_root = erase(val, _root);
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