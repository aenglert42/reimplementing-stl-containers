#pragma once

#include <iostream>
#include <memory> // std::allocator
#include "ft_nullptr.hpp" // ft_nullptr
#include "ft_vector_iterator.hpp"
#include "ft_algorithm.hpp"
#include "ft_type_traits.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class Vector
	{
		public:
	//MEMBER TYPES
			// using value_type				= T; //The first template parameter (T)	
			// using allocator_type			= Allocator; //The second template parameter (Alloc)	defaults to: allocator<value_type>
			// using reference					= value_type&; //allocator_type::reference	for the default allocator: value_type&
			// using const_reference			= const value_type&; //allocator_type::const_reference	for the default allocator: const value_type&
			// using pointer					= typename allocator_traits<Allocator>::pointer; //allocator_type::pointer	for the default allocator: value_type*
			// using const_pointer				= typename allocator_traits<Allocator>::const_pointer; //allocator_type::const_pointer	for the default allocator: const value_type*
			// using iterator					= /* implementation-defined */; //a random access iterator to value_type	convertible to const_iterator
			// using const_iterator			= /* implementation-defined */; //a random access iterator to const value_type	
			// using reverse_iterator			= std::reverse_iterator<iterator>; //reverse_iterator<iterator>	
			// using const_reverse_iterator	= std::reverse_iterator<const_iterator>; //reverse_iterator<const_iterator>	
			// using difference_type			= /* implementation-defined */; //a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
			// using size_type					= /* implementation-defined */; //an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t

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
		private:
			size_type _size;
			size_type _capacity;
			allocator_type _alloc;
			pointer _array;

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
	//MEMBER FUNCTIONS

			void print(void) // AE remove
			{
				std::cout << "size: " << size() << std::endl;
				for (size_type i = 0; i < size(); i++)
					std::cout << _array[i] << std::endl;
			}
		////constructor///////////////////////////////////////////////////////
			// default (1)	
			explicit Vector (const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc), _array(ft_nullptr)
			{

			}

			// fill (2)	
			explicit Vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
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
			Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
			{
				difference_type dist = std::distance(first, last);
				_size = dist;
				_capacity = _size;
				_alloc = alloc;
				_array = _alloc.allocate(_size);
				for (difference_type i = 0; i < dist; ++i)
					_alloc.construct(_array + i, *first++);
			}

			// copy (4)	
			Vector (const Vector& x)
			{
				_size = 0;
				_capacity = 0;
				_alloc = allocator_type();
				_array = ft_nullptr;
				*this = x;
			}

		////destructor///////////////////////////////////////////////////////
			// ~Vector()
			~Vector(void)
			{
				if (_array != ft_nullptr)
				{
					my_dealloc();
				}
			}

		////operator=///////////////////////////////////////////////////////
			// copy (1)	
			Vector& operator= (const Vector& x)
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
				// if (n > size())
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
			// void reserve (size_type n)

	//Element access---------------------------------------------------------------
		////operator[]///////////////////////////////////////////////////////
			reference operator[] (size_type n)
			{
				// if n >= size
				// errorhandling
				return (_array[n]); // AE remove make function for that
			}

			const_reference operator[] (size_type n) const
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

	//Modifiers---------------------------------------------------------------
		////assign///////////////////////////////////////////////////////
			// range (1)	
			// template <class InputIterator>
			// void assign (InputIterator first, InputIterator last)

			// fill (2)	
			// void assign (size_type n, const value_type& val)

		////push_back///////////////////////////////////////////////////////
			void push_back (const value_type& val)
			{
				if (_size >= _capacity)
				{
					if (_capacity == 0)
						my_realloc(1);
					else
						my_realloc(_capacity * 2);
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
			// iterator insert (iterator position, const value_type& val)

			// fill (2)	
			// void insert (iterator position, size_type n, const value_type& val)

			// range (3)	
			// template <class InputIterator>
			// void insert (iterator position, InputIterator first, InputIterator last)

		////erase///////////////////////////////////////////////////////
			// iterator erase (iterator position)
			// iterator erase (iterator first, iterator last)

		////swap///////////////////////////////////////////////////////
			// void swap (Vector& x)

		////clear///////////////////////////////////////////////////////
			void clear()
			{
				my_destroy();
				_size = 0;
			}

	//Allocator---------------------------------------------------------------
		////get_allocator///////////////////////////////////////////////////////
			// allocator_type get_allocator() const
	};

	//NON-MEMBER FUNCTION OVERLOADS
		////relational operators///////////////////////////////////////////////////////
			// (1)
			template <class T, class Alloc>
			bool operator==(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
			{
				return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
			}

			// (2)
			// template <class T, class Alloc>
			// bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)

			// (3)
			// template <class T, class Alloc>
			// bool operator<  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)

			// (4)
			// template <class T, class Alloc>
			// bool operator<= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)

			// (5)
			// template <class T, class Alloc>
			// bool operator>  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)

			// (6)
			// template <class T, class Alloc>
			// bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)

		////swap///////////////////////////////////////////////////////
			// template <class T, class Alloc>
			// void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y)

			


}