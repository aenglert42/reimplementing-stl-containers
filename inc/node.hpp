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
		typedef const Node<content_type>*			const_pointer;
		typedef std::size_t							size_type;

		content_type _content;
		node_type* _parent;
		node_type* _left_child;
		node_type* _right_child;
		size_type _height;
		bool _is_terminator;

		Node (const content_type& val, node_type* parent) : _content(val), _parent(parent), _left_child(ft_nullptr), _right_child(ft_nullptr), _height(1), _is_terminator(false)
		{

		}

		// for _end_node and _rend_node
		Node () : _parent(ft_nullptr), _left_child(ft_nullptr), _right_child(ft_nullptr), _height(1), _is_terminator(true)
		{

		}

		~Node ()
		{
			_parent = ft_nullptr;
			_left_child = ft_nullptr;
			_right_child = ft_nullptr;
		}

		// Node &operator=(const Node& other)
		// {
		// 	if (this != &other)
		// 	{
		// 		_content = other._content;
		// 		_parent = other._parent;
		// 		_left_child = other._left_child;
		// 		_right_child = other._right_child;
		// 		_height = other._height;
		// 		_is_terminator = other._is_terminator; //AE make this const
		// 	}
		// 	return (*this);
		// }

		Node (const Node& other) : _content(other._content), _parent(other._parent), _left_child(other._left_child), _right_child(other._right_child), _height(other._height), _is_terminator(other._is_terminator)
		{

		}
	};
}