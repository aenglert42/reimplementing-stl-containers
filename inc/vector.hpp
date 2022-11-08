#pragma once

#include <iostream>
#include <memory> // std::allocator
#include "ft_nullptr.hpp" // ft_nullptr
#include "vector_iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"

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
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
	//MEMBER TYPES
			typedef T											value_type; //The first template parameter (T)	
			typedef Alloc										allocator_type; //The second template parameter (Alloc)	defaults to: allocator<value_type>
			typedef typename allocator_type::reference			reference; //allocator_type::reference	for the default allocator: value_type&
			typedef typename allocator_type::const_reference	const_reference; //allocator_type::const_reference	for the default allocator: const value_type&
			typedef typename allocator_type::pointer			pointer; //allocator_type::pointer	for the default allocator: value_type*
			typedef typename allocator_type::const_pointer		const_pointer; //allocator_type::const_pointer	for the default allocator: const value_type*
			typedef VectorIterator<value_type>					iterator; //a random access iterator to value_type	convertible to const_iterator
			typedef VectorIterator<const value_type>			const_iterator; //a random access iterator to const value_type	
			typedef ft::reverse_iterator<iterator>				reverse_iterator; //reverse_iterator<iterator>	
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator; //reverse_iterator<const_iterator>	
			typedef std::ptrdiff_t								difference_type; //a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
			typedef std::size_t									size_type; //					= /* implementation-defined */; //an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t
			//why not typedef typename allocator_type::size_type size_type (wayback)? -> cplusplus.com
	//PRIVATE MEMBER VARIABLES
		private:
			size_type _size;
			size_type _capacity;
			allocator_type _alloc;
			pointer _array;

	//PRIVATE MEMBER FUNCTIONS
			pointer my_alloc(size_type newCapacity)
			{
				return (_alloc.allocate(newCapacity));
			}

			void my_destroy(void)
			{
				for(size_type i = 0; i < _size; i++)
					_alloc.destroy(&_array[i]);
			}

			void my_dealloc(void)
			{
				my_destroy();
				_alloc.deallocate(_array, _capacity);
			}

			void my_realloc(void)
			{
				size_type newCapacity;
				
				if (_capacity == 0)
					newCapacity = 1;
				else
					newCapacity = _capacity * 2;
				pointer newArray = my_alloc(newCapacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&newArray[i], _array[i]);
				my_dealloc();
				_array = newArray;
				_capacity = newCapacity;
			}

			void my_realloc(size_type newCapacity)
			{
				if (newCapacity < _size)
					return ;
				pointer newArray = my_alloc(newCapacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&newArray[i], _array[i]);
				my_dealloc();
				_array = newArray;
				_capacity = newCapacity;
			}

		public:
	//PUBLIC MEMBER FUNCTIONS

			void print(void) // AE remove
			{
				std::cerr << "size: " << _size << std::endl;
				for (size_type i = 0; i < _size; i++)
					std::cerr << _array[i] << std::endl;
			}
		////constructor///////////////////////////////////////////////////////
			// default (1)	
			explicit vector (const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc), _array(ft_nullptr)
			{

			}

			// fill (2)	
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			{
				_size = n;
				_capacity = _size;
				_alloc = alloc;
				_array = _alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
					_array[i] = val;
			}

			// range (3)	
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
			{
				difference_type dist = ft::distance(first, last);
				_size = dist;
				_capacity = _size;
				_alloc = alloc;
				_array = _alloc.allocate(_size);
				for (difference_type i = 0; i < dist; ++i)
					_alloc.construct(_array + i, *first++);
			}

			// copy (4)	
			vector (const vector& x)
			{
				_size = 0;
				_capacity = 0;
				_alloc = allocator_type();
				_array = ft_nullptr;
				*this = x;
			}

		////destructor///////////////////////////////////////////////////////
			// ~vector()
			~vector(void)
			{
				if (_array != ft_nullptr)
				{
					my_dealloc();
				}
			}

		////operator=///////////////////////////////////////////////////////
			// copy (1)	
			vector& operator= (const vector& x)
			{
				if (*this == x)
					return (*this);
				for(size_type i = 0; i < _size; i++)
					_alloc.destroy(&_array[i]);
				if (_capacity > 0)
					_alloc.deallocate(_array, _capacity);
				_capacity = x._capacity;
				_size = x._size;
				_array = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_array[i], x._array[i]);
				return (*this);
			}

	//Iterators---------------------------------------------------------------
		////begin///////////////////////////////////////////////////////
			iterator begin()
			{
				return (iterator(_array));
			}

			const_iterator begin() const
			{
				return (const_iterator(_array));
			}

		////end///////////////////////////////////////////////////////
			iterator end()
			{
				return (iterator(_array + _size));
			}

			const_iterator end() const
			{
				return (const_iterator(_array + _size));
			}

		////rbegin///////////////////////////////////////////////////////
			reverse_iterator rbegin()
			{
				return (reverse_iterator(end()));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(end()));
			}

		////rend///////////////////////////////////////////////////////
			reverse_iterator rend()
			{
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(begin()));
			}

	//Capacity---------------------------------------------------------------
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

		////resize///////////////////////////////////////////////////////
			void resize (size_type n, value_type val = value_type())
			{
				while (n > size())
					push_back(val);
				while (n < size())
					pop_back();
			}

		////capacity///////////////////////////////////////////////////////
			size_type capacity() const
			{
				return (_capacity);
			}

		////empty///////////////////////////////////////////////////////
			bool empty() const
			{
				if (_size == 0)
					return (true);
				return (false);
			}

		////reserve///////////////////////////////////////////////////////
			void reserve (size_type n)
			{
				if (n > _capacity)
					my_realloc(n);
			}

	//Element access---------------------------------------------------------------
		////operator[]///////////////////////////////////////////////////////
			reference operator[](size_type n)
			{
				// if n >= size
				// errorhandling
				return (_array[n]); // AE remove make function for that
			}

			const_reference operator[](size_type n) const
			{
				// if n >= size
				// errorhandling
				return (_array[n]); // AE remove make function for that
			}

		////at///////////////////////////////////////////////////////
			reference at (size_type n)
			{
				if (n > _size - 1)
					throw std::out_of_range("Catch out_of_range exception!");  // AE remove make function for that
				return (_array[n]);
			}

			const_reference at (size_type n) const
			{
				if (n > _size - 1)
					throw std::out_of_range("Catch out_of_range exception!");  // AE remove make function for that
				return (_array[n]);
			}

		////front///////////////////////////////////////////////////////
			reference front()
			{
				return (_array[0]); // AE remove make function for that
			}

			const_reference front() const
			{
				return (_array[0]); // AE remove make function for that
			}

		////back///////////////////////////////////////////////////////
			reference back()
			{
				return (_array[_size - 1]); // AE remove make function for that
			}

			const_reference back() const
			{
				return (_array[_size - 1]); // AE remove make function for that
			}

		////data///////////////////////////////////////////////////////
			value_type* data()
			{
				return (_array);
			}

			const value_type* data() const
			{
				return (_array);
			}

	//Modifiers---------------------------------------------------------------
		////assign///////////////////////////////////////////////////////
			// range (1)	
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last,
				typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type = InputIterator())
			{
				my_destroy();
				size_type n = last - first;
				if (n > _capacity)
					my_realloc(n);
				for (size_type i = 0; i < n; ++i)
					push_back(*(first + i));
			}

			// fill (2)	
			void assign (size_type n, const value_type& val)
			{
				my_destroy();
				if (n > _capacity)
					my_realloc(_size + n);
				for (size_type i = 0; i < n; ++i)
					push_back(val);
			}

		////push_back///////////////////////////////////////////////////////
			void push_back (const value_type& val)
			{
				if (_size >= _capacity)
				{
					my_realloc();
				}
				_alloc.construct(&_array[_size], val);
				_size++;
			}

		////pop_back///////////////////////////////////////////////////////
			void pop_back()
			{
				if (_size > 0)
				{
					_alloc.destroy(&_array[_size]);
					_size--;
				}
			}

		////insert///////////////////////////////////////////////////////
			// single element (1)	
			iterator insert (iterator position, const value_type& val)
			{
				difference_type pos = position - begin();
				insert (position, 1, val);
				return (begin() + pos);
			}

			// fill (2)	
			void insert (iterator position, size_type n, const value_type& val)
			{
				size_type old_size = _size;
				difference_type offset = end() - position;

				if (_size + n >= _capacity)
					my_realloc(_size + n);
				for (size_type i = 0; i < n; ++i)
				{
					_alloc.construct(&_array[_size], val); // AE change this to something that doesnt need val
					_size++;
				}	
				for (difference_type i = 0; i < offset; ++i)
				{
					_array[_size - 1 - i] = _array[old_size - 1 - i];
				}
				for (size_type i = 0; i < n; ++i)
				{
					_array[old_size - offset + i] = val;
				}
			}

			// range (3)	
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type = InputIterator())
			{
				size_type n = last - first;
				size_type old_size = _size;
				difference_type offset = end() - position;

				if (_size + n >= _capacity)
					my_realloc(_size + n);
				for (size_type i = 0; i < n; ++i)
				{
					_alloc.construct(&_array[_size], *(first)); // AE change this to something that doesnt need val
					_size++;
				}	
				for (difference_type i = 0; i < offset; ++i)
				{
					_array[_size - 1 - i] = _array[old_size - 1 - i];
				}
				for (size_type i = 0; i < n; ++i)
				{
					_array[old_size - offset + i] = *(first + i);
				}
			}

		////erase///////////////////////////////////////////////////////
			iterator erase(iterator position)
			{
				return (erase(position, position + 1));
			}

			iterator erase(iterator first, iterator last)
			{
				size_type n = last - first;
				for (iterator it = first; it != end() - n; ++it)
				{
					*(it) = *(it + n);
				}
				// for (size_type i = 0; i < n; ++i)
				// {
				// 	*(first + i) = *(first + n + i);
				// }
				for (size_type i = 0; i < n; ++i)
				{
					_alloc.destroy(&_array[_size - 1 - i]); // AE what if size == 0
					// _array[_size - 1 - i] = _array[0];
				}
				_size -= n;
				return (last + 1);
			}

		////swap///////////////////////////////////////////////////////
			void swap (vector& x)
			{
				size_type tmp_size = _size;
				size_type tmp_capacity = _capacity;
				allocator_type tmp_alloc = _alloc;
				pointer tmp_array = _array;

				_size = x._size;
				_capacity = x._capacity;
				_alloc = x._alloc;
				_array = x._array;

				x._size = tmp_size;
				x._capacity = tmp_capacity;
				x._alloc = tmp_alloc;
				x._array = tmp_array;
			}

		////clear///////////////////////////////////////////////////////
			void clear()
			{
				my_destroy();
				_size = 0;
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
			template <class T, class Alloc>
			bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
			}

			// (2)
			template <class T, class Alloc>
			bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return !(lhs == rhs);
			}

			// (3)
			template <class T, class Alloc>
			bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return ft::lexicographical_compare(lhs.begin(), lhs.end(), // AE ft version
					  rhs.begin(), rhs.end());
			}

			// (4)
			template <class T, class Alloc>
			bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return !(rhs < lhs);
			}

			// (5)
			template <class T, class Alloc>
			bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return (rhs < lhs);
			}

			// (6)
			template <class T, class Alloc>
			bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				return !(lhs < rhs);
			}

		////swap///////////////////////////////////////////////////////
			template <class T, class Alloc>
			void swap (vector<T,Alloc>& lhs, vector<T,Alloc>& rhs)
			{
				lhs.swap(rhs);
			}
}