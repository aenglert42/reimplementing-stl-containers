#pragma once

#include <iostream>
#include <memory> // std::allocator
#include "ft_nullptr.hpp" // ft_nullptr
#include "iterator.hpp"

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
					return (_ptr);
				}

			////operator*///////////////////////////////////////////////////////
				reference operator*() const
				{
					return (*_ptr);
				}

			////operator+///////////////////////////////////////////////////////
				VectorIterator operator+(difference_type n) const
				{
					return (VectorIterator(_ptr + n));
				}
			
			////operator++///////////////////////////////////////////////////////
				// (1)
					VectorIterator& operator++()
					{
						_ptr++;
						return *this;
					}

				// (2)	
					VectorIterator operator++(int)
					{
						VectorIterator tmp(*this);
						++_ptr;
						return tmp;
					}
			
			////operator+=///////////////////////////////////////////////////////
				VectorIterator& operator+=(difference_type n)
				{
					_ptr += n;
					return (*this);
				}
			
			////operator-///////////////////////////////////////////////////////
				// (1)
					difference_type operator-(const VectorIterator& other) const
					{
						return (_ptr - other._ptr);
					}

				// (2)
					VectorIterator operator-(difference_type n) const
					{
						return (VectorIterator(_ptr - n));
					}

			////operator--///////////////////////////////////////////////////////
				// (1)
					VectorIterator& operator--()
					{
						_ptr--;
						return *this;
					}

				// (2)	
					VectorIterator& operator--(int)
					{
						VectorIterator tmp(*this);
						--_ptr;
						return tmp;
					}
			
			////operator-=///////////////////////////////////////////////////////
				VectorIterator& operator-=(difference_type n)
				{
					_ptr -= n;
					return (*this);
				}
			
			////operator->///////////////////////////////////////////////////////
				pointer operator->() const
				{
					return (_ptr);
				}

			////operator[]///////////////////////////////////////////////////////
				reference operator[] (difference_type n) const
				{
					return (*(_ptr + n));
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
					
				// (3)
					template <class Iterator>
					bool operator<(const VectorIterator<Iterator>& lhs,
									const VectorIterator<Iterator>& rhs)
					{
						return (lhs.base() < rhs.base());
					}

				// (4)
					template <class Iterator>
					bool operator<=(const VectorIterator<Iterator>& lhs,
									const VectorIterator<Iterator>& rhs)
					{
						return (lhs.base() <= rhs.base());
					}

				// (5)
					template <class Iterator>
					bool operator>(const VectorIterator<Iterator>& lhs,
									const VectorIterator<Iterator>& rhs)
					{
						return (lhs.base() > rhs.base());
					}

				// (6)
					template <class Iterator>
					bool operator>=(const VectorIterator<Iterator>& lhs,
									const VectorIterator<Iterator>& rhs)
					{
						return (lhs.base() >= rhs.base());
					}

			////operator+///////////////////////////////////////////////////////
				template <class Iterator>
				VectorIterator<Iterator> operator+(
							typename VectorIterator<Iterator>::difference_type n,
							const VectorIterator<Iterator>& rev_it)
				{
					return (VectorIterator<Iterator>(rev_it.base() + n));
				}

			////operator-///////////////////////////////////////////////////////
				template <class Iterator>
				typename VectorIterator<Iterator>::difference_type operator-(
					const VectorIterator<Iterator>& lhs,
					const VectorIterator<Iterator>& rhs)
				{
					return (lhs.base() + rhs.base());
				}
}