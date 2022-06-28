#pragma once

#include <iostream> //remove
// #include <iterator>

namespace ft
{
// iterator_traits https://cplusplus.com/reference/iterator/iterator_traits/

	// struct input_iterator_tag
	// {

	// };

	// struct output_iterator_tag
	// {

	// };

	// struct forward_iterator_tag : public input_iterator_tag
	// {

	// };

	// struct bidirectional_iterator_tag : public forward_iterator_tag
	// {

	// };

	// struct random_access_iterator_tag : public bidirectional_iterator_tag
	// {

	// };

	//try to use structs instead of typedefs once ft::iterator is working
	typedef std::input_iterator_tag input_iterator_tag;
	typedef std::output_iterator_tag output_iterator_tag;
	typedef std::forward_iterator_tag forward_iterator_tag;
	typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
	typedef std::random_access_iterator_tag random_access_iterator_tag;

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
			typedef ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef T*										pointer;
			typedef T&										reference;
			typedef random_access_iterator_tag				iterator_category;
	};

	template <class T>
	class iterator_traits<const T*>
	{
		public:
			typedef ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef const T*								pointer;
			typedef const T&								reference;
			typedef random_access_iterator_tag				iterator_category;
	};

// iterator https://cplusplus.com/reference/iterator/iterator/
	template <class Category, class T, class Distance = ptrdiff_t,
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
	//MEMBER TYPES

	//MEMBER FUNCTIONS

		////constructor///////////////////////////////////////////////////////
			// default (1)
			// reverse_iterator()


			// initialization (2)
			// explicit reverse_iterator (iterator_type it)



			// copy (3)
			// template <class Iter>
			// reverse_iterator (const reverse_iterator<Iter>& rev_it)


		////base///////////////////////////////////////////////////////
			// iterator_type base() const


		////operator*///////////////////////////////////////////////////////
		// reference operator*() const

		////operator+///////////////////////////////////////////////////////
		// reverse_iterator operator+ (difference_type n) const
		
		////operator++///////////////////////////////////////////////////////
			// (1)
			// reverse_iterator& operator++()

			// (2)	
			// reverse_iterator  operator++(int)
		
		////operator+=///////////////////////////////////////////////////////
		// reverse_iterator& operator+= (difference_type n)
		
		////operator-///////////////////////////////////////////////////////
		// reverse_iterator operator- (difference_type n) const
		
		////operator--///////////////////////////////////////////////////////
		// reverse_iterator& operator--()

		// reverse_iterator  operator--(int)
		
		////operator-=///////////////////////////////////////////////////////
		// reverse_iterator& operator-= (difference_type n)
		
		////operator->///////////////////////////////////////////////////////
		// pointer operator->() const

		////operator[]///////////////////////////////////////////////////////
		// reference operator[] (difference_type n) const


	//NON-MEMBER FUNCTION OVERLOADS
		////relational operators///////////////////////////////////////////////////////
			// (1)
			// template <class Iterator>
			// bool operator== (const reverse_iterator<Iterator>& lhs,
			// 				const reverse_iterator<Iterator>& rhs)

			// (2)
			// template <class Iterator>
			// bool operator!= (const reverse_iterator<Iterator>& lhs,
			// 				const reverse_iterator<Iterator>& rhs)


			// (3)
			// template <class Iterator>
			// bool operator<  (const reverse_iterator<Iterator>& lhs,
			// 				const reverse_iterator<Iterator>& rhs)


			// (4)
			// template <class Iterator>
			// bool operator<= (const reverse_iterator<Iterator>& lhs,
			// 				const reverse_iterator<Iterator>& rhs)


			// (5)
			// template <class Iterator>
			// bool operator>  (const reverse_iterator<Iterator>& lhs,
			// 				const reverse_iterator<Iterator>& rhs);


			// (6)
			// template <class Iterator>
			// bool operator>= (const reverse_iterator<Iterator>& lhs,
			// 				const reverse_iterator<Iterator>& rhs);


		////operator+ (reverse_iterator)///////////////////////////////////////////////////////
			// template <class Iterator>
			// reverse_iterator<Iterator> operator+ (
			// 			typename reverse_iterator<Iterator>::difference_type n,
			// 			const reverse_iterator<Iterator>& rev_it)

		////operator (reverse_iterator)///////////////////////////////////////////////////////
			// template <class Iterator>
			// typename reverse_iterator<Iterator>::difference_type operator- (
			// 	const reverse_iterator<Iterator>& lhs,
			// 	const reverse_iterator<Iterator>& rhs)
}