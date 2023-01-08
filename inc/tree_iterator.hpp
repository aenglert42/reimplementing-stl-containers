#pragma once

#include <iostream>
#include <memory> // std::allocator
#include "ft_nullptr.hpp" // ft_nullptr
#include "iterator.hpp"
#include "node.hpp"

namespace ft
{
	template <typename NT>
	NT* get_leftmost_node(NT* node)
	{
		NT* current = node;

		while (current != ft_nullptr && current->_left_child != ft_nullptr)
			current = current->_left_child;
		return (current);
	}

	template <typename NT>
	NT* get_rightmost_node(NT* node)
	{
		NT* current = node;

		while (current != ft_nullptr && current->_right_child != ft_nullptr)
			current = current->_right_child;
		return (current);
	}

	template <typename NT>
	NT* get_successor_node(NT* node)
	{
		if (node == ft_nullptr)
			return (ft_nullptr);
		if (node->_right_child != ft_nullptr)
			return (get_leftmost_node(node->_right_child));
		
		NT* current = node->_parent;
		while (current != ft_nullptr && node == current->_right_child)
		{
			node = current;
			current = current->_parent;
		}
		return (current);
	}

	template <typename NT>
	NT* get_predecessor_node(NT* node)
	{
		if (node == ft_nullptr)
			return (ft_nullptr);
		if (node->_left_child != ft_nullptr)
			return (get_rightmost_node(node->_left_child));
		
		NT* current = node->_parent;
		while (current != ft_nullptr && node == current->_left_child)
		{
			node = current;
			current = current->_parent;
		}
		return (current);
	}

	template <typename NT>
	bool has_successor_node(NT* node)
	{
		NT* tmp;
		if (node == ft_nullptr)
			return (false);
		if (node->_right_child != ft_nullptr)
		{
			tmp = get_leftmost_node(node->_right_child);
			if (tmp == ft_nullptr)
				return (false);
			else
				return (true);
		}
		
		tmp = node->_parent;
		while (tmp != ft_nullptr && node == tmp->_right_child)
		{
			node = tmp;
			tmp = tmp->_parent;
		}
		if (tmp == ft_nullptr)
			return (false);
		else
			return (true);
	}

	template <typename NT>
	bool has_predecessor_node(NT* node)
	{
		NT* tmp;
		if (node == ft_nullptr)
			return (false);
		if (node->_left_child != ft_nullptr)
		{
			tmp = get_rightmost_node(node->_left_child);
			if (tmp == ft_nullptr)
				return (false);
			else
				return (true);
		}
		
		tmp = node->_parent;
		while (tmp != ft_nullptr && node == tmp->_left_child)
		{
			node = tmp;
			tmp = tmp->_parent;
		}
		if (tmp == ft_nullptr)
			return (false);
		else
			return (true);
	}

	template <typename content_type, typename node_pointer>
	class TreeIterator
	{
		public:
	//MEMBER TYPES
			typedef ft::iterator<ft::bidirectional_iterator_tag, content_type>				iterator_type;
			typedef std::iterator<std::bidirectional_iterator_tag, content_type>				std_iterator_type;
			typedef typename ft::iterator_traits<iterator_type>::difference_type		difference_type;
			typedef typename ft::iterator_traits<iterator_type>::value_type				value_type;
			typedef typename ft::iterator_traits<iterator_type>::pointer				pointer;
			typedef typename ft::iterator_traits<iterator_type>::reference				reference;
			typedef typename std::iterator_traits<std_iterator_type>::iterator_category		iterator_category;
			// typedef Node<content_type>*												node_pointer;

	//MEMBER FUNCTIONS

			////constructor///////////////////////////////////////////////////////
				TreeIterator(void) : _ptr(ft_nullptr)
				{

				}

				TreeIterator(node_pointer ptr) : _ptr(ptr)
				{

				}

				TreeIterator(const TreeIterator& other) : _ptr(other._ptr) // AE base()?
				{

				}

			////non-const to const///////////////////////////////////////////////////////
				operator TreeIterator<const content_type, node_pointer>() const
				{
					return (TreeIterator<const content_type, node_pointer>(base()));
				}

			////destructor///////////////////////////////////////////////////////
				~TreeIterator(void)
				{

				}

			////base///////////////////////////////////////////////////////
				node_pointer base(void) const
				{
					return (_ptr);
				}

			////operator*///////////////////////////////////////////////////////
				reference operator*() const
				{
					return (_ptr->_content);
				}

			////operator++///////////////////////////////////////////////////////
				// (1)
					TreeIterator& operator++()
					{
						// if (has_successor_node(_ptr))
							_ptr = get_successor_node(_ptr);
						return *this;
					}

				// (2)	
					TreeIterator operator++(int)
					{
						TreeIterator tmp(*this);
						// if (has_successor_node(_ptr))
							_ptr = get_successor_node(_ptr);
						return tmp;
					}

			////operator--///////////////////////////////////////////////////////
				// (1)
					TreeIterator& operator--()
					{
						// if (has_predecessor_node(_ptr))
							_ptr = get_predecessor_node(_ptr);
						return *this;
					}

				// (2)	
					TreeIterator operator--(int)
					{
						TreeIterator tmp(*this);
						// if (has_predecessor_node(_ptr)) // AE is this correct? Or shoud I return something else?
							_ptr = get_predecessor_node(_ptr);
						return tmp;
					}
			
			////operator->///////////////////////////////////////////////////////
				pointer operator->() const
				{
					return (&_ptr->_content);
				}

				friend bool operator==(const TreeIterator& lhs,
								const TreeIterator& rhs)
				{
					return (lhs.base() == rhs.base());
				}

				friend bool operator!=(const TreeIterator& lhs,
								const TreeIterator& rhs)
				{
					return (lhs.base() != rhs.base());
				}

		private:
			node_pointer _ptr;
	};

}