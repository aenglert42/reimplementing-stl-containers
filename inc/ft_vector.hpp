#pragma once

#include <iostream>
#include <memory> // std::allocator
#include "ft_nullptr.hpp" // ft_nullptr
#include "ft_iterator.hpp"

namespace ft
{
////////////////VectorIterator
	template <typename T> //AE can I change T to iterator?
	class VectorIterator
	{
		public:
			typedef iterator<random_access_iterator_tag, T>							iterator_type;
			typedef typename iterator_traits<iterator_type>::difference_type		difference_type;
			typedef typename iterator_traits<iterator_type>::value_type				value_type;
			typedef typename iterator_traits<iterator_type>::pointer				pointer;
			typedef typename iterator_traits<iterator_type>::reference				reference;
			typedef typename iterator_traits<iterator_type>::iterator_category		iterator_category;

			VectorIterator(void) : _ptr(ft_nullptr)
			{

			}

			VectorIterator(pointer ptr) : _ptr(ptr)
			{

			}

			VectorIterator(const VectorIterator& other) : _ptr(other._ptr) // AE base()?
			{

			}

			~VectorIterator(void)
			{

			}

			VectorIterator& operator++()
			{
				this->_ptr++;
				return *this;
			}

			VectorIterator& operator++(int)
			{
				VectorIterator tmp(*this);
				++this->_ptr;
				return tmp;
			}

			VectorIterator& operator--()
			{
				this->_ptr--;
				return *this;
			}

			VectorIterator& operator--(int)
			{
				VectorIterator tmp(*this);
				--this->_ptr;
				return tmp;
			}

			reference operator[] (difference_type n) const
			{
				return (*(this->_ptr + n));
			}

			pointer operator->() const
			{
				return (this->_ptr);
			}
		
			reference operator*() const
			{
				return (*this->_ptr);
			}

			// pointer base(void) const
			// {

			// }

		private:
			pointer _ptr;
	};

	template <class Iterator>
	bool operator==(const VectorIterator<Iterator>& lhs,
					const VectorIterator<Iterator>& rhs)
	{
		return (*lhs == *rhs);
	}

	template <class Iterator>
	bool operator!=(const VectorIterator<Iterator>& lhs,
					const VectorIterator<Iterator>& rhs)
	{
		return (*lhs != *rhs);
	}

////////////////Vector
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

			pointer myAlloc(size_type newCapacity)
			{
				return (this->alloc.allocate(newCapacity));
			}

			void myDestroy(void)
			{
				for(size_type i = 0; i < this->_size; i++)
					this->alloc.destroy(&this->array[i]);
			}

			void myDealloc(void)
			{
				myDestroy();
				this->alloc.deallocate(this->array, this->_capacity);
			}

			void myRealloc(size_type newCapacity)
			{
				if (newCapacity < this->_size)
					return ;
				pointer newArray = myAlloc(newCapacity);
				for (size_type i = 0; i < this->_size; i++)
					this->alloc.construct(&newArray[i], this->array[i]);
				myDealloc();
				this->array = newArray;
				this->_capacity = newCapacity;
			}

		public:
	//MEMBER FUNCTIONS

			void print(void) //remove
			{
				std::cout << "size: " << this->size() << std::endl;
				for (size_type i = 0; i < this->size(); i++)
					std::cout << array[i] << std::endl;
			}
		////constructor///////////////////////////////////////////////////////
			// default (1)	
			explicit Vector (const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), alloc(alloc), array(ft_nullptr)
			{

			}

			// fill (2)	
			explicit Vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())// : _size(n), _capacity(_size), alloc(alloc)
			{
				this->_size = n;
				this->_capacity = this->_size;
				this->alloc = alloc;
				this->array = this->_alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
					this->array[i] = val;
			}

			// range (3)	
			// template <class InputIterator>
			// Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())

			// copy (4)	
			Vector (const Vector& x)// :_size(0), _capacity(0), alloc(allocator_type()), array(ft_nullptr)
			{
				this->_size = 0;
				this->_capacity = 0;
				this->alloc = allocator_type();
				this->array = ft_nullptr;
				*this = x;
			}

		////destructor///////////////////////////////////////////////////////
			// ~Vector()
			~Vector(void)
			{
				if (this->array != ft_nullptr)
				{
					// for(size_type i = 0; i < this->_size; i++)
					// 	this->alloc.destroy(&this->array[i]);
					// this->alloc.deallocate(this->array, this->_capacity);
					myDealloc();
				}
			}

		////operator=///////////////////////////////////////////////////////
			// copy (1)	
			Vector& operator= (const Vector& x)
			{
				if (*this == x)
					return (*this);
				for(size_type i = 0; i < this->_size; i++)
					this->alloc.destroy(&this->array[i]);
				if (this->_capacity > 0)
					this->alloc.deallocate(this->array, this->_capacity);
				this->_capacity = x._capacity;
				this->_size = x._size;
				this->array = this->alloc.allocate(this->_capacity);
				for (size_type i = 0; i < this->_size; i++)
					this->alloc.construct(&this->array[i], x.array[i]);
				return (*this);
			}

	//Iterators---------------------------------------------------------------
		////begin///////////////////////////////////////////////////////
			iterator begin()
			{
				return (iterator(this->array));
			}
			// const_iterator begin() const

		////end///////////////////////////////////////////////////////
			iterator end()
			{
				return (iterator(this->array + this->_size));
			}
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
				// if n >= size
				// errorhandling
				return (this->array[n]); // AE remove make function for that
			}

			const_reference operator[] (size_type n) const
			{
				// if n >= size
				// errorhandling
				return (this->array[n]); // AE remove make function for that
			}

		////at///////////////////////////////////////////////////////
			reference at (size_type n)
			{
				if (n > this->_size - 1)
					throw std::out_of_range("Catch out_of_range exception!");  // AE remove make function for that
				return (this->array[n]);
			}

			const_reference at (size_type n) const
			{
				if (n > this->_size - 1)
					throw std::out_of_range("Catch out_of_range exception!");  // AE remove make function for that
				return (this->array[n]);
			}

		////front///////////////////////////////////////////////////////
			reference front()
			{
				return (this->array[0]); // AE remove make function for that
			}

			const_reference front() const
			{
				return (this->array[0]); // AE remove make function for that
			}

		////back///////////////////////////////////////////////////////
			reference back()
			{
				return (this->array[this->_size - 1]); // AE remove make function for that
			}

			const_reference back() const
			{
				return (this->array[this->_size - 1]); // AE remove make function for that
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
				if (this->_size >= this->_capacity)
				{
					if (this->_capacity == 0)
						this->myRealloc(1);
					else
						this->myRealloc(this->_capacity * 2);
				}
				this->alloc.construct(&this->array[this->_size], val);
				this->_size++;
			}

		////pop_back///////////////////////////////////////////////////////
			void pop_back()
			{
				if (this->_size > 0)
				{
					this->alloc.destroy(&this->array[this->_size]);
					this->_size--;
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
				myDestroy();
				this->_size = 0;
			}

	//Allocator---------------------------------------------------------------
		////get_allocator///////////////////////////////////////////////////////
			// allocator_type get_allocator() const

	//NON-MEMBER FUNCTION OVERLOADS
		////relational operators///////////////////////////////////////////////////////
			// (1)
			// template <class T, class Alloc>
			// bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)

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

			
	};


}