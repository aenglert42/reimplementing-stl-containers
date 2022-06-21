#pragma once

#include <iostream>
#include <memory> //std::allocator

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
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
			// typedef iterator					= /* implementation-defined */; //a random access iterator to value_type	convertible to const_iterator
			// typedef const_iterator			= /* implementation-defined */; //a random access iterator to const value_type	
			// typedef ft::reverse_iterator<iterator>				reverse_iterator; //reverse_iterator<iterator>	
			// typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator; //reverse_iterator<const_iterator>	
			// typedef difference_type			= /* implementation-defined */; //a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
			typedef std::size_t									size_type; //					= /* implementation-defined */; //an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t
			//why not typedef typename allocator_type::size_type size_type (wayback)? -> cplusplus.com
		private:
			size_type _size;
			size_type _capacity;
			allocator_type alloc;
			pointer array;
		public:
	//MEMBER FUNCTIONS

			void print(void) //remove
			{
				std::cout << "test" << std::endl;
			}
		////constructor///////////////////////////////////////////////////////
			// vector(void)
			// {
			// 	array = new T[1];
			// 	_capacity = 1;
			// 	current = 0;
			// }
			// default (1)	
			explicit vector (const allocator_type& alloc = allocator_type())
			{
				this->_size = 0;
				this->_capacity = 0;
				this->alloc = alloc;
				this->array = nullptr;
			}

			// fill (2)	
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			{
				this->_size = n;
				this->_capacity = this->_size;
				this->alloc = alloc;
				this->array = this->_alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
					this->array[i] = val;
			}

			// range (3)	
			// template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())

			// copy (4)	
			// vector (const vector& x)

		////destructor///////////////////////////////////////////////////////
			// ~vector()
			~vector(void)
			{
				if (this->array != nullptr)
				{
					for(size_type i = 0; i < this->_size; i++)
						this->alloc.destroy(this->array + i);
					this->alloc.deallocate(this->array, this->_capacity);
				}
			}

		////operator=///////////////////////////////////////////////////////
			// copy (1)	
			// vector& operator= (const vector& x)

	//Iterators---------------------------------------------------------------
		////begin///////////////////////////////////////////////////////
			// iterator begin()
			// const_iterator begin() const

		////end///////////////////////////////////////////////////////
			// iterator end()
			// const_iterator end() const

		////rbegin///////////////////////////////////////////////////////
			// reverse_iterator rbegin()
			// const_reverse_iterator rbegin() const

		////rend///////////////////////////////////////////////////////
			// reverse_iterator rend()
			// const_reverse_iterator rend() const

	//Capacity---------------------------------------------------------------
		////size///////////////////////////////////////////////////////
			size_type size() const
			{
				return (this->_size);
			}

		////max_size///////////////////////////////////////////////////////
			size_type max_size() const
			{
				return (this->alloc.max_size());
			}

		////resize///////////////////////////////////////////////////////
			// void resize (size_type n, value_type val = value_type())

		////capacity///////////////////////////////////////////////////////
			size_type capacity() const
			{
				return (this->_capacity);
			}

		////empty///////////////////////////////////////////////////////
			bool empty() const
			{
				if (this->_size == 0)
					return (true);
				return (false);
			}

		////reserve///////////////////////////////////////////////////////
			// void reserve (size_type n)

	//Element access---------------------------------------------------------------
		////operator[]///////////////////////////////////////////////////////
			reference operator[] (size_type n)
			{
				return (this->array[n]); //remove make function fo that
			}

			const_reference operator[] (size_type n) const
			{
				return (this->array[n]); //remove make function fo that
			}

		////at///////////////////////////////////////////////////////
			reference at (size_type n)
			{
				if (n > this->_size - 1)
					throw std::out_of_range("Catch out_of_range exception!");  //remove make function fo that
				return (this->array[n]);
			}

			const_reference at (size_type n) const
			{
				if (n > this->_size - 1)
					throw std::out_of_range("Catch out_of_range exception!");  //remove make function fo that
				return (this->array[n]);
			}

		////front///////////////////////////////////////////////////////
			reference front()
			{
				return (this->array[0]); //remove make function fo that
			}

			const_reference front() const
			{
				return (this->array[0]); //remove make function fo that
			}

		////back///////////////////////////////////////////////////////
			reference back()
			{
				return (this->array[this->_size - 1]); //remove make function fo that
			}

			const_reference back() const
			{
				return (this->array[this->_size - 1]); //remove make function fo that
			}

	//Modifiers---------------------------------------------------------------
		////assign///////////////////////////////////////////////////////
			// range (1)	
			// template <class InputIterator> void assign (InputIterator first, InputIterator last)

			// fill (2)	
			// void assign (size_type n, const value_type& val)

		////push_back///////////////////////////////////////////////////////
			// void push_back (const value_type& val)

		////pop_back///////////////////////////////////////////////////////
			// void pop_back()

		////insert///////////////////////////////////////////////////////
			// single element (1)	
			// iterator insert (iterator position, const value_type& val)

			// fill (2)	
			// void insert (iterator position, size_type n, const value_type& val)

			// range (3)	
			// template <class InputIterator> void insert (iterator position, InputIterator first, InputIterator last)

		////erase///////////////////////////////////////////////////////
			// iterator erase (iterator position)
			// iterator erase (iterator first, iterator last)

		////swap///////////////////////////////////////////////////////
			// void swap (vector& x)

		////clear///////////////////////////////////////////////////////
			// void clear()

	//Allocator---------------------------------------------------------------
		////get_allocator///////////////////////////////////////////////////////
			// allocator_type get_allocator() const

	//NON-MEMBER FUNCTION OVERLOADS
		////relational operators///////////////////////////////////////////////////////
			// (1)
			// template <class T, class Alloc> bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)

			// (2)
			// template <class T, class Alloc> bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)

			// (3)
			// template <class T, class Alloc> bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)

			// (4)
			// template <class T, class Alloc> bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)

			// (5)
			// template <class T, class Alloc> bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)

			// (6)
			// template <class T, class Alloc> bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)

		////swap///////////////////////////////////////////////////////
			// template <class T, class Alloc> void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)

			
	};


}