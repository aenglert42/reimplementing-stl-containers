#pragma once

#include <iostream>
#include <memory> // std::allocator
#include "ft_nullptr.hpp" // ft_nullptr

// Colors and Printing
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RED "\033[31m"
#define BOLD "\033[1m"
#define UNDERLINED "\033[4m"

namespace ft
{
	template <class node_type>
	struct Node
	{
		node_type _content;
		Node* _parent;
		Node* _left_child;
		Node* _right_child;

		Node (const node_type& val, Node<node_type>* parent) : _content(val), _parent(parent), _left_child(ft_nullptr), _right_child(ft_nullptr)
		{

		}
	};
}