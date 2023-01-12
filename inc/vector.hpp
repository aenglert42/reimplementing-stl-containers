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
				if (!empty())
					my_destroy();
				if (_array != ft_nullptr)
				{
					_alloc.deallocate(_array, _capacity);
					_array = ft_nullptr;
				}
				_capacity = 0;
			}

			void my_realloc(void)
			{
				size_type newCapacity;
				
				if (_capacity == 0)
					newCapacity = 1;
				else
					newCapacity = _capacity * 2;
				if (newCapacity > max_size())
					throw std::length_error("cannot create ft::vector larger than max_size()");
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
				if (newCapacity > max_size())
					throw std::length_error("cannot create ft::vector larger than max_size()");
				pointer newArray = my_alloc(newCapacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&newArray[i], _array[i]);
				my_dealloc();
				_array = newArray;
				_capacity = newCapacity;
			}

			size_type check_against_max_size(size_type n)
			{
				if (n > max_size())
					throw std::length_error("cannot create ft::vector larger than max_size()");
				return (n);
			}

			template <class InputIterator>
			void range_push_back(InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					push_back(*first);
					++first;
				}
			}

		public:
	//PUBLIC MEMBER FUNCTIONS

		#ifdef DEBUG
			void print(void)
			{
				std::cerr << "size: " << _size << std::endl;
				for (size_type i = 0; i < _size; i++)
					std::cerr << _array[i] << std::endl;
			}
		#endif

		////constructor///////////////////////////////////////////////////////
			// default (1)	
			explicit vector (const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc), _array(ft_nullptr)
			{

			}

			// fill (2)	
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc), _array(ft_nullptr)
			{
				check_against_max_size(n);
				for (size_type i = 0; i < n; ++i)
					push_back(val);
			}

			// range (3)	
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) : _size(0), _capacity(0), _alloc(alloc), _array(ft_nullptr)
			{
				range_push_back(first,last);
			}

			// copy (4)	
			vector (const vector& x) : _size(x._size), _capacity(x._capacity), _alloc(x._alloc), _array(ft_nullptr)
			{
				if (_capacity == 0)
					return ;
				_array = my_alloc(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_array[i], x._array[i]);
			}

		////destructor///////////////////////////////////////////////////////
			// ~vector()
			~vector(void)
			{
				clear();
			}

		////operator=///////////////////////////////////////////////////////
			// copy (1)	
			vector& operator= (const vector& x)
			{
				if (*this == x)
					return (*this);
				my_dealloc();
				_capacity = x._capacity;
				_array = my_alloc(_capacity);
				_size = x._size;
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
					insert(end(), n - size(), val);
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
				check_against_max_size(n);
				if (n > _capacity)
					my_realloc(n);
			}

	//Element access---------------------------------------------------------------
		////operator[]///////////////////////////////////////////////////////
			reference operator[](size_type n)
			{
				return (_array[n]);
			}

			const_reference operator[](size_type n) const
			{
				return (_array[n]);
			}

		////at///////////////////////////////////////////////////////
			reference at (size_type n)
			{
				if (_size == 0 || n > _size - 1)
					throw std::out_of_range("Catch out_of_range exception!");
				return (_array[n]);
			}

			const_reference at (size_type n) const
			{
				if (_size == 0 || n > _size - 1)
					throw std::out_of_range("Catch out_of_range exception!");
				return (_array[n]);
			}

		////front///////////////////////////////////////////////////////
			reference front()
			{
				return (_array[0]);
			}

			const_reference front() const
			{
				return (_array[0]);
			}

		////back///////////////////////////////////////////////////////
			reference back()
			{
				return (_array[_size - 1]);
			}

			const_reference back() const
			{
				return (_array[_size - 1]);
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
			void assign(InputIterator first, InputIterator last,
				typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type = InputIterator())
			{
				my_destroy();
				_size = 0;
				range_push_back(first, last);
			}

			// fill (2)	
			void assign(size_type n, const value_type& val)
			{
				my_destroy();
				_size = 0;
				if (n > _capacity)
					my_realloc(n);
				for (size_type i = 0; i < n; ++i)
					push_back(val);
			}

		////push_back///////////////////////////////////////////////////////
			void push_back(const value_type& val)
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
				if (empty())
					return ;
				_alloc.destroy(&_array[_size - 1]);
				_size--;
			}

		////insert///////////////////////////////////////////////////////
			// single element (1)	
			iterator insert (iterator position, const value_type& val)
			{
				difference_type pos = position - begin();

				if (_size >= _capacity)
					my_realloc();
				_alloc.construct(_array + _size, value_type());
				_size++;
				for (iterator tmp = (end() - 1); tmp != iterator(_array + pos); --tmp)
					*tmp = *(tmp - 1);
				*(_array + pos) = val;
				return (_array + pos);
			}

			// fill (2)	
			void insert (iterator position, size_type n, const value_type& val)
			{
				size_type new_size = _size + n;
				check_against_max_size(new_size);

				vector tmp (position, end());
				erase(position, end());
				for (size_type i = 0; i < n; ++i)
					push_back(val);
				range_push_back(tmp.begin(), tmp.end());
			}

			// range (3)	
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type = InputIterator())
			{
				vector tmp (position, end());
				erase(position, end());
				range_push_back(first, last);
				range_push_back(tmp.begin(), tmp.end());
			}

		////erase///////////////////////////////////////////////////////
			iterator erase(iterator position)
			{
				for (iterator tmp = position; tmp + 1 != end(); ++tmp)
					*tmp = *(tmp + 1);
				pop_back();
				return (position);
			}

			iterator erase(iterator first, iterator last)
			{
				size_type n = last - first;
				
				for (iterator it = first; it != end() - n; ++it)
					*(it) = *(it + n);

				for (size_type i = 0; i < n; ++i)
					_alloc.destroy(&_array[_size - 1 - i]);
				_size -= n;
				return (first);
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
				my_dealloc();
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
				return ft::lexicographical_compare(lhs.begin(), lhs.end(),
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