#pragma once

#include <iostream> //remove
// #include <iterator>
#include <cstddef> // ptrdiff_t

namespace ft
{
// iterator_traits https://cplusplus.com/reference/iterator/iterator_traits/

	struct input_iterator_tag
	{

	};

	struct output_iterator_tag
	{

	};

	struct forward_iterator_tag : public input_iterator_tag
	{

	};

	struct bidirectional_iterator_tag : public forward_iterator_tag
	{

	};

	struct random_access_iterator_tag : public bidirectional_iterator_tag
	{

	};

	template <class Iterator>
	class iterator_traits
	{
		public:
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	class iterator_traits<T*>
	{
		public:
			typedef std::ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef T*										pointer;
			typedef T&										reference;
			typedef random_access_iterator_tag				iterator_category;
	};

	template <class T>
	class iterator_traits<const T*>
	{
		public:
			typedef std::ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef const T*								pointer;
			typedef const T&								reference;
			typedef random_access_iterator_tag				iterator_category;
	};

// iterator https://cplusplus.com/reference/iterator/iterator/
	template <class Category, class T, class Distance = std::ptrdiff_t,
			class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T											value_type;
		typedef Distance									difference_type;
		typedef Pointer										pointer;
		typedef Reference									reference;
		typedef Category									iterator_category;
	};

// reverse_iterator
	
	template <class Iterator>
	class reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
											typename iterator_traits<Iterator>::value_type,
											typename iterator_traits<Iterator>::difference_type,
											typename iterator_traits<Iterator>::pointer,
											typename iterator_traits<Iterator>::reference>
	{
		protected:
			Iterator current;

		public:
	//MEMBER TYPES
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

	//MEMBER FUNCTIONS

			////constructor///////////////////////////////////////////////////////
				// default (1)
				reverse_iterator() : current()
				{

				}


				// initialization (2)
				explicit reverse_iterator (iterator_type it) : current(it)
				{

				}

				// copy (3)
				template <class Iter>
				reverse_iterator (const reverse_iterator<Iter>& rev_it) : current(rev_it.base())
				{

				}


			////base///////////////////////////////////////////////////////
			iterator_type base() const
			{
				return (current);
			}


			////operator*///////////////////////////////////////////////////////
			reference operator*() const
			{
				iterator_type tmp = current;
				return *--tmp;
			}

			////operator+///////////////////////////////////////////////////////
			reverse_iterator operator+(difference_type n) const
			{
				return (reverse_iterator(current - n));
			}
			
			////operator++///////////////////////////////////////////////////////
				// (1)
				reverse_iterator& operator++()
				{
					--current;
					return (*this);
				}

				// (2)	
				reverse_iterator  operator++(int)
				{
					reverse_iterator tmp(*this);
					--current;
					return tmp;
				}
			
			////operator+=///////////////////////////////////////////////////////
			reverse_iterator& operator+=(difference_type n)
			{
				current -= n;
				return (*this);
			}
			
			////operator-///////////////////////////////////////////////////////
			reverse_iterator operator-(difference_type n) const
			{
				return (reverse_iterator(current + n));
			}
			
			////operator--///////////////////////////////////////////////////////
				// (1)	
				reverse_iterator& operator--()
				{
					++current;
					return (*this);
				}

				// (2)	
				reverse_iterator  operator--(int)
				{
					reverse_iterator tmp(*this);
					++current;
					return (tmp);
				}
			
			////operator-=///////////////////////////////////////////////////////
			reverse_iterator& operator-=(difference_type n)
			{
				current += n;
				return (*this);
			}
			
			////operator->///////////////////////////////////////////////////////
			pointer operator->() const
			{
				return (&(operator*())); //CHECK
			}

			////operator[]///////////////////////////////////////////////////////
			reference operator[] (difference_type n) const
			{
				return (*(*this + n));
			}
	};
	
	//NON-MEMBER FUNCTION OVERLOADS
			////relational operators///////////////////////////////////////////////////////
				// (1)
				template <class Iterator>
				bool operator==(const reverse_iterator<Iterator>& lhs,
								const reverse_iterator<Iterator>& rhs)
				{
					return (lhs.base() == rhs.base());
				}

				// (2)
				template <class Iterator>
				bool operator!=(const reverse_iterator<Iterator>& lhs,
								const reverse_iterator<Iterator>& rhs)
				{
					return (lhs.base() != rhs.base());
				}

				// (3)
				template <class Iterator>
				bool operator<(const reverse_iterator<Iterator>& lhs,
								const reverse_iterator<Iterator>& rhs)
				{
					return (lhs.base() > rhs.base());
				}

				// (4)
				template <class Iterator>
				bool operator<=(const reverse_iterator<Iterator>& lhs,
								const reverse_iterator<Iterator>& rhs)
				{
					return (lhs.base() >= rhs.base());
				}

				// (5)
				template <class Iterator>
				bool operator>(const reverse_iterator<Iterator>& lhs,
								const reverse_iterator<Iterator>& rhs)
				{
					return (lhs.base() < rhs.base());
				}

				// (6)
				template <class Iterator>
				bool operator>=(const reverse_iterator<Iterator>& lhs,
								const reverse_iterator<Iterator>& rhs)
				{
					return (lhs.base() <= rhs.base());
				}

			////operator+ (reverse_iterator)///////////////////////////////////////////////////////
				template <class Iterator>
				reverse_iterator<Iterator> operator+(
							typename reverse_iterator<Iterator>::difference_type n,
							const reverse_iterator<Iterator>& rev_it)
				{
					return (reverse_iterator<Iterator>(rev_it.base() - n));
				}

			////operator- (reverse_iterator)///////////////////////////////////////////////////////
				template <class Iterator>
				typename reverse_iterator<Iterator>::difference_type operator-(
					const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
				{
					return (lhs.base() - rhs.base());
				}

			////distance///////////////////////////////////////////////////////
				template <class InputIterator>
				typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
				{
					typename iterator_traits<InputIterator>::difference_type result = 0;
					while (first != last)
					{
						++first;
						++result;
					}
					return (result);
				}
}