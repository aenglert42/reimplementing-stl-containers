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
			typedef Alloc										allocator_type; //The fourth template parameter (Alloc) defaults to: allocator<value_type>
			typedef typename allocator_type::reference			reference; //allocator_type::reference	for the default allocator: value_type&
			typedef typename allocator_type::const_reference	const_reference; //allocator_type::const_reference	for the default allocator: const value_type&
			typedef typename allocator_type::pointer			pointer; //allocator_type::pointer	for the default allocator: value_type*
			typedef typename allocator_type::const_pointer		const_pointer; //allocator_type::const_pointer	for the default allocator: const value_type*
			typedef TreeIterator<value_type, Node<value_type>* >					iterator; //a bidirectional iterator to value_type	convertible to const_iterator
			typedef TreeIterator<const value_type, Node<value_type>* >				const_iterator; //a bidirectional iterator to const value_type	
			typedef ft::reverse_iterator<iterator>				reverse_iterator; //reverse_iterator<iterator>	
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator; //reverse_iterator<const_iterator>	
			typedef std::ptrdiff_t								difference_type; //a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
			typedef std::size_t									size_type; //an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t
	
			class value_compare //Nested function class to compare elements
			{
				public:
					value_compare() : _compare()
					{

					}

					value_compare(key_compare c) : _compare(c)
					{

					}

					value_compare(const value_compare& other) : _compare(other._compare)
					{

					}

					value_compare &operator=(const value_compare& other)
					{
						if (this != &other)
						{
							_compare = other._compare;
						}
						return (*this);
					}

					~value_compare()
					{

					}

					bool operator()(const value_type& lhs, const value_type& rhs) const
					{
						return (_compare(lhs.first, rhs.first));
					}

				private:
					key_compare _compare;
			};

	//PRIVATE MEMBER VARIABLES
		private:
			// size_type _size;
			value_compare _comp;
			allocator_type _alloc;
			Tree<value_type, key_type, value_compare> _tree;

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
			explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc), _tree(comp)
			{

			}

			// range (2)	
			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc), _tree()
			{
				while (first != last)
					insert(*first++);
			}

			// copy (3)	
			map (const map& x) : _comp(x._comp), _alloc(x._alloc), _tree(x._tree)
			{

			}

		////destructor///////////////////////////////////////////////////////
			// ~map()
			~map(void)
			{

			}

		////operator=///////////////////////////////////////////////////////
			// copy (1)	
			map& operator=(const map& x)
			{
				if (this != &x)
				{
					_comp = x._comp;
					// _alloc = x._alloc;
					_tree = x._tree;
				}
				return (*this);
			}

	//Iterators---------------------------------------------------------------
		////begin///////////////////////////////////////////////////////
			iterator begin()
			{
				return(_tree.begin());
			}

			const_iterator begin() const
			{
				return(_tree.begin());
			}

		////end///////////////////////////////////////////////////////
			iterator end()
			{
				return(_tree.end());
			}

			const_iterator end() const
			{
				return(_tree.end());
			}

		////rbegin///////////////////////////////////////////////////////
			reverse_iterator rbegin()
			{
				return (_tree.rbegin());
			}

			const_reverse_iterator rbegin() const
			{
				return (_tree.rbegin());
			}

		////rend///////////////////////////////////////////////////////
			reverse_iterator rend()
			{
				return (_tree.rend());
			}

			const_reverse_iterator rend() const
			{
				return (_tree.rend());
			}

	//Capacity---------------------------------------------------------------
		////empty///////////////////////////////////////////////////////
			bool empty() const
			{
				return (_tree.empty());
			}
			
		////size///////////////////////////////////////////////////////
			size_type size() const
			{
				return (_tree.size());
			}

		////max_size///////////////////////////////////////////////////////
			size_type max_size() const
			{
				return (_alloc.max_size());
			}

	//Element access---------------------------------------------------------------
		////operator[]///////////////////////////////////////////////////////
			mapped_type& operator[](const key_type& k)
			{
				value_type tmp = ft::make_pair(k, mapped_type());
				return ((*_tree.insert(tmp).first).second);
			}

		////at///////////////////////////////////////////////////////
			mapped_type& at (const key_type& k)
			{
				iterator tmp = find(k);
				if (tmp == end())
					throw std::out_of_range("map::at");
				return (tmp->second);
			}
			
			const mapped_type& at (const key_type& k) const
			{
				const_iterator tmp= find(k);
				if (tmp == end())
					throw std::out_of_range("map::at");
				return (tmp->second);
			}

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
			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
					_tree.insert(*first++);
			}

		////erase///////////////////////////////////////////////////////
			// (1)
			void erase(iterator position)
			{
				_tree.erase(position);
			}

			// (2)
			size_type erase(const key_type& k)
			{
				value_type tmp = ft::make_pair(k, mapped_type());
				return (_tree.erase(tmp));
			}

			// (3)
			void erase (iterator first, iterator last)
			{
				_tree.erase(first, last);
				// while (last != first) // AE fix endless loop (test erase_range, random)
				// {
				// 	iterator tmp = first;
				// 	++first;
				// 	erase(tmp);
				// }
				// // (void)first;
				// // (void)last;
			}

		////swap///////////////////////////////////////////////////////
			void swap (map& x) // AE this could be optimized by only swapping the tree content
			{
				map tmp (x);
				x = *this;
				*this = tmp;
			}

		////clear///////////////////////////////////////////////////////
			void clear()
			{
				_tree.clear();
			}

	//Observers---------------------------------------------------------------
		////key_comp///////////////////////////////////////////////////////
			key_compare key_comp() const
			{
				return(key_compare());
			}

		////value_comp///////////////////////////////////////////////////////
			value_compare value_comp() const
			{
				return(value_compare());
			}

	//Operations---------------------------------------------------------------
		////find///////////////////////////////////////////////////////
			iterator find(const key_type& k)
			{
				value_type tmp = ft::make_pair(k, mapped_type()); // AE this will not work if a class has no default constructor
				iterator ret = _tree.find(tmp);

				if (ret == iterator(ft_nullptr)) // AE this should be handled in tree already
					return (end());
				return (ret);
			}
			
			const_iterator find(const key_type& k) const
			{
				value_type tmp = ft::make_pair(k, mapped_type());
				const_iterator ret = _tree.find(tmp);

				if (ret == iterator(ft_nullptr)) // AE this should be handled in tree already
					return (end());
				return (ret);
			}

		////count///////////////////////////////////////////////////////
			size_type count (const key_type& k) const
			{
				value_type tmp = ft::make_pair(k, mapped_type()); // AE this will not work if a class has no default constructor
				return (_tree.count(tmp));
			}

		////lower_bound///////////////////////////////////////////////////////
			iterator lower_bound(const key_type& k)
			{
				value_type tmp = ft::make_pair(k, mapped_type());
				iterator ret = _tree.lower_bound(tmp);

				if (ret == iterator(ft_nullptr)) // AE this should be handled in tree already
					return (end());
				return (ret);
			}
			
			const_iterator lower_bound(const key_type& k) const
			{
				value_type tmp = ft::make_pair(k, mapped_type());
				const_iterator ret = _tree.lower_bound(tmp);

				if (ret == iterator(ft_nullptr)) // AE this should be handled in tree already
					return (end());
				return (ret);
			}

		////upper_bound///////////////////////////////////////////////////////
			iterator upper_bound(const key_type& k)
			{
				value_type tmp = ft::make_pair(k, mapped_type());
				iterator ret = _tree.upper_bound(tmp);

				if (ret == iterator(ft_nullptr)) // AE this should be handled in tree already
					return (end());
				return (ret);
			}
			
			const_iterator upper_bound(const key_type& k) const
			{
				value_type tmp = ft::make_pair(k, mapped_type());
				const_iterator ret = _tree.upper_bound(tmp);

				if (ret == iterator(ft_nullptr)) // AE this should be handled in tree already
					return (end());
				return (ret);
			}

		////equal_range///////////////////////////////////////////////////////
			pair<iterator,iterator> equal_range(const key_type& k)
			{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

			pair<const_iterator,const_iterator> equal_range(const key_type& k) const
			{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

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
			template< class Key, class T, class Compare, class Alloc >
			bool operator==( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs )
			{
				if (lhs.size() != rhs.size())
					return (false);
				return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
			}

			// (2)
			template< class Key, class T, class Compare, class Alloc >
			bool operator!=( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs )
			{
				return (!(lhs == rhs));
			}

			// (3)
			template< class Key, class T, class Compare, class Alloc >
			bool operator<( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs )
			{
				return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
			}

			// (4)
			template< class Key, class T, class Compare, class Alloc >
			bool operator<=( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs )
			{
				return (!(rhs < lhs));
			}

			// (5)
			template< class Key, class T, class Compare, class Alloc >
			bool operator>( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs )
			{
				return (rhs < lhs);
			}

			// (6)
			template< class Key, class T, class Compare, class Alloc >
			bool operator>=( const map<Key,T,Compare,Alloc>& lhs,
				const map<Key,T,Compare,Alloc>& rhs )
			{
				return (!(lhs < rhs));
			}

		////swap///////////////////////////////////////////////////////
			template< class Key, class T, class Compare, class Alloc >
			void swap( map<Key,T,Compare,Alloc>& lhs,
			map<Key,T,Compare,Alloc>& rhs )
			{
				lhs.swap(rhs);
			}
}