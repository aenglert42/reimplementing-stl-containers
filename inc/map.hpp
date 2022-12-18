#pragma once

#include <iostream>
#include <memory> // std::allocator
#include "ft_nullptr.hpp" // ft_nullptr
// #include "vector_iterator.hpp"
#include "functional.hpp" // less
#include "utils.hpp" // pair
#include "algorithm.hpp"
#include "type_traits.hpp"
#include "tree.hpp"

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
	template < class Key, // map::key_type
	class T, // map::mapped_type
	class Compare = ft::less<Key>, // map::key_compare
	class Alloc = typename std::allocator<ft::pair<const Key,T> > > // map::allocator_type
	class map
	{
		public:
	//MEMBER TYPES
			typedef Key											key_type; //The first template parameter (Key)	
			typedef T											mapped_type; //The second template parameter (T)
			typedef pair<const key_type,mapped_type>			value_type;
			typedef Compare										key_compare; //The third template parameter (Compare)
			// typedef ?										value_compare; //Nested function class to compare elements
			typedef Alloc										allocator_type; //The fourth template parameter (Alloc) defaults to: allocator<value_type>
			typedef typename allocator_type::reference			reference; //allocator_type::reference	for the default allocator: value_type&
			typedef typename allocator_type::const_reference	const_reference; //allocator_type::const_reference	for the default allocator: const value_type&
			typedef typename allocator_type::pointer			pointer; //allocator_type::pointer	for the default allocator: value_type*
			typedef typename allocator_type::const_pointer		const_pointer; //allocator_type::const_pointer	for the default allocator: const value_type*
			typedef TreeIterator<Node<value_type> >				iterator; //a bidirectional iterator to value_type	convertible to const_iterator
			typedef TreeIterator<const Node<value_type> >		const_iterator; //a bidirectional iterator to const value_type	
			typedef ft::reverse_iterator<iterator>				reverse_iterator; //reverse_iterator<iterator>	
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator; //reverse_iterator<const_iterator>	
			typedef std::ptrdiff_t								difference_type; //a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
			typedef std::size_t									size_type; //an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t
	
			// template <class Key, class T, class Compare, class Alloc>
			// class map<Key,T,Compare,Alloc>::value_compare
			// {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
			// 	friend class map;
			// 	protected:
			// 	Compare comp;
			// 	value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
			// 	public:
			// 	typedef bool result_type;
			// 	typedef value_type first_argument_type;
			// 	typedef value_type second_argument_type;
			// 	bool operator() (const value_type& x, const value_type& y) const
			// 	{
			// 		return comp(x.first, y.first);
			// 	}
			// }
	
	//PRIVATE MEMBER VARIABLES
		private:
			size_type _size;
			// value_compare _compare;
			allocator_type _alloc;
			Tree<value_type> _tree;

	//PRIVATE MEMBER FUNCTIONS

		public:
	//PUBLIC MEMBER FUNCTIONS

			void print(void) // AE remove
			{
				_tree.print();
			}

			void print2D(void) // AE remove
			{
				_tree.print2D();
			}
		////constructor///////////////////////////////////////////////////////
			
			// empty (1)	
			// explicit map (const key_compare& comp = key_compare(),
			// 	const allocator_type& alloc = allocator_type())
			// {

			// }

			// range (2)	
			// template <class InputIterator>  map (InputIterator first, InputIterator last,
			// 	const key_compare& comp = key_compare(),
			// 	const allocator_type& alloc = allocator_type())
			// {

			// }

			// copy (3)	
			// map (const map& x)
			// {

			// }

		////destructor///////////////////////////////////////////////////////
			// ~map()
			// ~map(void)
			// {

			// }

		////operator=///////////////////////////////////////////////////////
			// copy (1)	
			// map& operator= (const map& x)
			// {

			// }

	//Iterators---------------------------------------------------------------
		////begin///////////////////////////////////////////////////////
			iterator begin()
			{
				return(_tree.begin());
			}

			// const_iterator begin() const
			// {
				
			// }

		////end///////////////////////////////////////////////////////
			iterator end()
			{
				return(_tree.end());
			}

			// const_iterator end() const
			// {
				
			// }

		////rbegin///////////////////////////////////////////////////////
			// reverse_iterator rbegin()
			// {
			// 	return (reverse_iterator(end()));
			// }

			// const_reverse_iterator rbegin() const
			// {
			// 	return (const_reverse_iterator(end()));
			// }

		////rend///////////////////////////////////////////////////////
			// reverse_iterator rend()
			// {
			// 	return (reverse_iterator(begin()));
			// }

			// const_reverse_iterator rend() const
			// {
			// 	return (const_reverse_iterator(begin()));
			// }

	//Capacity---------------------------------------------------------------
		////empty///////////////////////////////////////////////////////
			bool empty() const
			{
				if (_size == 0)
					return (true);
				return (false);
			}
			
		////size///////////////////////////////////////////////////////
			size_type size() const
			{
				return (_size);
			}

		////max_size///////////////////////////////////////////////////////
			size_type max_size() const
			{
				return (_alloc.max_size());
			}

	//Element access---------------------------------------------------------------
		////operator[]///////////////////////////////////////////////////////
			// mapped_type& operator[](const key_type& k)
			// {

			// }

		////at///////////////////////////////////////////////////////
			// mapped_type& at (const key_type& k)
			// {

			// }
			
			// const mapped_type& at (const key_type& k) const
			// {

			// }

	//Modifiers---------------------------------------------------------------
		////insert///////////////////////////////////////////////////////
			// single element (1)	
			ft::pair<iterator,bool> insert(const value_type& val)
			{
				return (_tree.insert(val));
			}

			// with hint (2)
			iterator insert(iterator position, const value_type& val)
			{
				return (_tree.insert(position, val));
			}

			// range (3)
			// template <class InputIterator>  void insert(InputIterator first, InputIterator last)
			// {

			// }

		////erase///////////////////////////////////////////////////////
			// (1)
			// void erase(iterator position)
			// {

			// }

			// (2)
			size_type erase(const key_type& k)
			{
				_tree.erase(k);
				return (9); // AE remove
			}

			// (3)
			// void erase (iterator first, iterator last)
			// {

			// }

		////swap///////////////////////////////////////////////////////
			// void swap (map& x)
			// {

			// }

		////clear///////////////////////////////////////////////////////
			// void clear()
			// {

			// }

	//Observers---------------------------------------------------------------
		////key_comp///////////////////////////////////////////////////////
			// key_compare key_comp() const
			// {

			// }

		////value_comp///////////////////////////////////////////////////////
			// value_compare value_comp() const
			// {

			// }

	//Operations---------------------------------------------------------------
		////find///////////////////////////////////////////////////////
			iterator find (const key_type& k)
			{
				return (_tree.find(k));
			}
			
			// const_iterator find (const key_type& k) const
			// {

			// }

		////count///////////////////////////////////////////////////////
			// size_type count (const key_type& k) const
			// {
				
			// }

		////lower_bound///////////////////////////////////////////////////////
			// iterator lower_bound (const key_type& k)
			// {
				
			// }
			
			// const_iterator lower_bound (const key_type& k) const
			// {

			// }

		////upper_bound///////////////////////////////////////////////////////
			// iterator upper_bound (const key_type& k)
			// {
				
			// }
			
			// const_iterator upper_bound (const key_type& k) const
			// {

			// }

		////equal_range///////////////////////////////////////////////////////
			// pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			// {
				
			// }
			
			// pair<iterator,iterator> equal_range (const key_type& k)
			// {

			// }

	//Allocator---------------------------------------------------------------
		////get_allocator///////////////////////////////////////////////////////
			allocator_type get_allocator() const
			{
				return (_alloc);
			}
	};

	//NON-MEMBER FUNCTION OVERLOADS
		////relational operators///////////////////////////////////////////////////////
			// (1)
			// template< class Key, class T, class Compare, class Alloc >
			// bool operator==( const map<Key,T,Compare,Alloc>& lhs,
			// 	const map<Key,T,Compare,Alloc>& rhs )
			// {

			// }

			// (2)
			// template< class Key, class T, class Compare, class Alloc >
			// bool operator!=( const map<Key,T,Compare,Alloc>& lhs,
			// 	const map<Key,T,Compare,Alloc>& rhs )
			// {

			// }

			// (3)
			// template< class Key, class T, class Compare, class Alloc >
			// bool operator<( const map<Key,T,Compare,Alloc>& lhs,
			// 	const map<Key,T,Compare,Alloc>& rhs )
			// {
				
			// }

			// (4)
			// template< class Key, class T, class Compare, class Alloc >
			// bool operator<=( const map<Key,T,Compare,Alloc>& lhs,
			// 	const map<Key,T,Compare,Alloc>& rhs )
			// {

			// }

			// (5)
			// template< class Key, class T, class Compare, class Alloc >
			// bool operator>( const map<Key,T,Compare,Alloc>& lhs,
			// 	const map<Key,T,Compare,Alloc>& rhs )
			// {
				
			// }

			// (6)
			// template< class Key, class T, class Compare, class Alloc >
			// bool operator>=( const map<Key,T,Compare,Alloc>& lhs,
			// 	const map<Key,T,Compare,Alloc>& rhs )
			// {
				
			// }

		////swap///////////////////////////////////////////////////////
			// template< class Key, class T, class Compare, class Alloc >
			// void swap( map<Key,T,Compare,Alloc>& lhs,
			// map<Key,T,Compare,Alloc>& rhs )
			// {
			// 	lhs.swap(rhs);
			// }
}