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
	template <class content_type>
	struct Node
	{
		typedef Node<content_type>					node_type;
		typedef Node<content_type>*					pointer;
		typedef const Node<content_type>*					const_pointer;
		// typedef typename content_type::first_type	key_type; // AE uncommenting this will make node<int> invalid
		// typedef typename content_type::second_type	value_type; // AE uncommenting this will make node<int> invalid
		// typedef std::allocator<node_type>			allocator_type;
		typedef std::size_t									size_type;

		content_type _content;
		node_type* _parent;
		node_type* _left_child;
		node_type* _right_child;
		size_type _height;

		Node (const content_type& val, node_type* parent) : _content(val), _parent(parent), _left_child(ft_nullptr), _right_child(ft_nullptr), _height(1)
		{

		}

		// for _end_node
		Node () : _content(content_type()), _parent(ft_nullptr), _left_child(ft_nullptr), _right_child(ft_nullptr), _height(1) //AE remove?
		{

		}

		~Node ()
		{
			_parent = ft_nullptr;
			_left_child = ft_nullptr;
			_right_child = ft_nullptr;
		}
	};
}