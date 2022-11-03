#pragma once

#include <iostream>
#include <memory> // std::allocator
#include "ft_nullptr.hpp" // ft_nullptr
#include "ft_iterator.hpp"

namespace ft
{
	template <typename T>
	class VectorIterator
	{
		public:
	//MEMBER TYPES
			typedef iterator<random_access_iterator_tag, T>							iterator_type;
			typedef typename iterator_traits<iterator_type>::difference_type		difference_type;
			typedef typename iterator_traits<iterator_type>::value_type				value_type;
			typedef typename iterator_traits<iterator_type>::pointer				pointer;
			typedef typename iterator_traits<iterator_type>::reference				reference;
			typedef typename iterator_traits<iterator_type>::iterator_category		iterator_category;

	//MEMBER FUNCTIONS

			////constructor///////////////////////////////////////////////////////
				VectorIterator(void) : _ptr(ft_nullptr)
				{

				}

				VectorIterator(pointer ptr) : _ptr(ptr)
				{

				}

				VectorIterator(const VectorIterator& other) : _ptr(other._ptr) // AE base()?
				{

				}

			////destructor///////////////////////////////////////////////////////
				~VectorIterator(void)
				{

				}

			////base///////////////////////////////////////////////////////
				pointer base(void) const
				{
					return (this->_ptr);
				}

			////operator*///////////////////////////////////////////////////////
				reference operator*() const
				{
					return (*this->_ptr);
				}

			////operator+///////////////////////////////////////////////////////

			
			////operator++///////////////////////////////////////////////////////
				// (1)
					VectorIterator& operator++()
					{
						this->_ptr++;
						return *this;
					}

				// (2)	
					VectorIterator operator++(int)
					{
						VectorIterator tmp(*this);
						++this->_ptr;
						return tmp;
					}
			
			////operator+=///////////////////////////////////////////////////////

			
			////operator-///////////////////////////////////////////////////////
				// (1)
					difference_type operator-(const VectorIterator& other) const
					{
						return (this->_ptr - other._ptr);
					}

				// (2)
					VectorIterator operator-(difference_type n) const
					{
						return (VectorIterator(this->_ptr - n));
					}

			////operator--///////////////////////////////////////////////////////
				// (1)
					VectorIterator& operator--()
					{
						this->_ptr--;
						return *this;
					}

				// (2)	
					VectorIterator& operator--(int)
					{
						VectorIterator tmp(*this);
						--this->_ptr;
						return tmp;
					}
			
			////operator-=///////////////////////////////////////////////////////

			
			////operator->///////////////////////////////////////////////////////
				pointer operator->() const
				{
					return (this->_ptr);
				}

			////operator[]///////////////////////////////////////////////////////
				reference operator[] (difference_type n) const
				{
					return (*(this->_ptr + n));
				}

		private:
			pointer _ptr;
	};

	//NON-MEMBER FUNCTION OVERLOADS
			////relational operators///////////////////////////////////////////////////////
				// (1)
					template <class Iterator>
					bool operator==(const VectorIterator<Iterator>& lhs,
									const VectorIterator<Iterator>& rhs)
					{
						return (lhs.base() == rhs.base());
					}

				// (2)
					template <class Iterator>
					bool operator!=(const VectorIterator<Iterator>& lhs,
									const VectorIterator<Iterator>& rhs)
					{
						return (lhs.base() != rhs.base());
					}

			////operator+///////////////////////////////////////////////////////

			////operator-///////////////////////////////////////////////////////
}