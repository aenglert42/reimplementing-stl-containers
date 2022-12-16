#pragma once

#include <iostream>
#include <memory> // std::allocator
#include "ft_nullptr.hpp" // ft_nullptr
#include "iterator.hpp"
#include "node.hpp"

namespace ft
{
	template <typename T>
	Node<T>* get_leftmost_node(Node<T>* node)
	{
		Node<T>* current = node;

		while (current != ft_nullptr && current->_left_child != ft_nullptr)
			current = current->_left_child;
		return (current);
	}

	template <typename T>
	Node<T>* get_rightmost_node(Node<T>* node)
	{
		Node<T>* current = node;

		while (current != ft_nullptr && current->_right_child != ft_nullptr)
			current = current->_right_child;
		return (current);
	}

	template <typename T>
	Node<T>* get_successor_node(Node<T>* node)
	{
		if (node == ft_nullptr)
			return (ft_nullptr);
		if (node->_right_child != ft_nullptr)
			return (get_leftmost_node(node->_right_child));
		
		Node<T>* current = node->_parent;
		while (current != ft_nullptr && node == current->_right_child)
		{
			node = current;
			current = current->_parent;
		}
		return (current);
	}

	template <typename T>
	Node<T>* get_predecessor_node(Node<T>* node)
	{
		if (node == ft_nullptr)
			return (ft_nullptr);
		if (node->_left_child != ft_nullptr)
			return (get_rightmost_node(node->_left_child));
		
		Node<T>* current = node->_parent;
		while (current != ft_nullptr && node == current->_left_child)
		{
			node = current;
			current = current->_parent;
		}
		return (current);
	}

	// template <typename T>
	// bool has_successor_node(Node<T>* node)
	// {
	// 	Node<T>* tmp;
	// 	if (node == ft_nullptr)
	// 		return (false);
	// 	if (node->_right_child != ft_nullptr)
	// 	{
	// 		tmp = get_leftmost_node(node->_right_child);
	// 		if (tmp == ft_nullptr)
	// 			return (false);
	// 		else
	// 			return (true);
	// 	}
		
	// 	tmp = node->_parent;
	// 	while (tmp != ft_nullptr && node == tmp->_right_child)
	// 	{
	// 		node = tmp;
	// 		tmp = tmp->_parent;
	// 	}
	// 	if (tmp == ft_nullptr)
	// 		return (false);
	// 	else
	// 		return (true);
	// }

	// template <typename T>
	// bool has_predecessor_node(Node<T>* node)
	// {
	// 	Node<T>* tmp;
	// 	if (node == ft_nullptr)
	// 		return (false);
	// 	if (node->_left_child != ft_nullptr)
	// 	{
	// 		tmp = get_rightmost_node(node->_left_child);
	// 		if (tmp == ft_nullptr)
	// 			return (false);
	// 		else
	// 			return (true);
	// 	}
		
	// 	tmp = node->_parent;
	// 	while (tmp != ft_nullptr && node == tmp->_left_child)
	// 	{
	// 		node = tmp;
	// 		tmp = tmp->_parent;
	// 	}
	// 	if (tmp == ft_nullptr)
	// 		return (false);
	// 	else
	// 		return (true);
	// }

	template <typename Tree>
	class TreeIterator
	{
		public:
	//MEMBER TYPES
			typedef iterator<bidirectional_iterator_tag, Tree>							iterator_type;
			typedef typename iterator_traits<iterator_type>::difference_type		difference_type;
			typedef typename iterator_traits<iterator_type>::value_type				value_type;
			typedef typename iterator_traits<iterator_type>::pointer				pointer;
			typedef typename iterator_traits<iterator_type>::reference				reference;
			typedef typename iterator_traits<iterator_type>::iterator_category		iterator_category;

	//MEMBER FUNCTIONS

			////constructor///////////////////////////////////////////////////////
				TreeIterator(void) : _ptr(ft_nullptr)
				{

				}

				TreeIterator(pointer ptr) : _ptr(ptr)
				{

				}

				TreeIterator(const TreeIterator& other) : _ptr(other._ptr) // AE base()?
				{

				}

			////non-const to const///////////////////////////////////////////////////////
				operator TreeIterator<const Tree>() const
				{
					return (TreeIterator<const Tree>(base()));
				}

			////destructor///////////////////////////////////////////////////////
				~TreeIterator(void)
				{

				}

			////base///////////////////////////////////////////////////////
				pointer base(void) const
				{
					return (_ptr);
				}

			////operator*///////////////////////////////////////////////////////
				reference operator*() const
				{
					return (*_ptr);
				}

			// ////operator+///////////////////////////////////////////////////////
			// 	TreeIterator operator+(difference_type n) const
			// 	{
			// 		return (TreeIterator(_ptr + n));
			// 	}
			
			////operator++///////////////////////////////////////////////////////
				// (1)
					TreeIterator& operator++()
					{
						_ptr = get_successor_node(_ptr);
						return *this;
					}

				// (2)	
					TreeIterator operator++(int)
					{
						TreeIterator tmp(*this);
						_ptr = get_successor_node(_ptr);
						return tmp;
					}
			
			// ////operator+=///////////////////////////////////////////////////////
			// 	TreeIterator& operator+=(difference_type n)
			// 	{
			// 		_ptr += n;
			// 		return (*this);
			// 	}
			
			// ////operator-///////////////////////////////////////////////////////
			// 	// (1)
			// 		difference_type operator-(const TreeIterator& other) const
			// 		{
			// 			return (_ptr - other._ptr);
			// 		}

			// 	// (2)
			// 		TreeIterator operator-(difference_type n) const
			// 		{
			// 			return (TreeIterator(_ptr - n));
			// 		}

			////operator--///////////////////////////////////////////////////////
				// (1)
					TreeIterator& operator--()
					{
						_ptr = get_predecessor_node(_ptr);
						return *this;
					}

				// (2)	
					TreeIterator operator--(int)
					{
						TreeIterator tmp(*this);
						_ptr = get_predecessor_node(_ptr);
						return tmp;
					}
			
			// ////operator-=///////////////////////////////////////////////////////
			// 	TreeIterator& operator-=(difference_type n)
			// 	{
			// 		_ptr -= n;
			// 		return (*this);
			// 	}
			
			////operator->///////////////////////////////////////////////////////
				pointer operator->() const
				{
					return (_ptr);
				}

			// ////operator[]///////////////////////////////////////////////////////
			// 	reference operator[] (difference_type n) const
			// 	{
			// 		return (*(_ptr + n));
			// 	}

		private:
			pointer _ptr;
	};

	//NON-MEMBER FUNCTION OVERLOADS
			////relational operators///////////////////////////////////////////////////////
				// (1)
					template <class Iterator1, class Iterator2>
					bool operator==(const TreeIterator<Iterator1>& lhs,
									const TreeIterator<Iterator2>& rhs)
					{
						return (lhs.base() == rhs.base());
					}

				// (2)
					template <class Iterator1, class Iterator2>
					bool operator!=(const TreeIterator<Iterator1>& lhs,
									const TreeIterator<Iterator2>& rhs)
					{
						return (lhs.base() != rhs.base());
					}
					
				// // (3)
				// 	template <class Iterator1, class Iterator2>
				// 	bool operator<(const TreeIterator<Iterator1>& lhs,
				// 					const TreeIterator<Iterator2>& rhs)
				// 	{
				// 		return (lhs.base() < rhs.base());
				// 	}

				// // (4)
				// 	template <class Iterator1, class Iterator2>
				// 	bool operator<=(const TreeIterator<Iterator1>& lhs,
				// 					const TreeIterator<Iterator2>& rhs)
				// 	{
				// 		return (lhs.base() <= rhs.base());
				// 	}

				// // (5)
				// 	template <class Iterator1, class Iterator2>
				// 	bool operator>(const TreeIterator<Iterator1>& lhs,
				// 					const TreeIterator<Iterator2>& rhs)
				// 	{
				// 		return (lhs.base() > rhs.base());
				// 	}

				// // (6)
				// 	template <class Iterator1, class Iterator2>
				// 	bool operator>=(const TreeIterator<Iterator1>& lhs,
				// 					const TreeIterator<Iterator2>& rhs)
				// 	{
				// 		return (lhs.base() >= rhs.base());
				// 	}

			// ////operator+///////////////////////////////////////////////////////
			// 	template <class Iterator>
			// 	TreeIterator<Iterator> operator+(
			// 		typename TreeIterator<Iterator>::difference_type n,
			// 		const TreeIterator<Iterator>& rev_it)
			// 	{
			// 		return (TreeIterator<Iterator>(rev_it.base() + n));
			// 	}

			// ////operator-///////////////////////////////////////////////////////
			// 	template <class Iterator>
			// 	typename TreeIterator<Iterator>::difference_type operator-(
			// 		const TreeIterator<Iterator>& lhs,
			// 		const TreeIterator<Iterator>& rhs)
			// 	{
			// 		return (lhs.base() + rhs.base());
			// 	}
}