#pragma once

#include <iostream> //remove

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
	//MEMBER TYPES
		public:
			typedef T1 first_type;
			typedef T2 second_type;
		private:
			typedef std::allocator<first_type> alloctor_first;
			typedef std::allocator<second_type> alloctor_second;

			alloctor_first alloc_first;
			alloctor_second alloc_second;
	//MEMBER VARIABLES
		public:
			first_type	first;
			second_type	second;
	//MEMBER FUNCTIONS

		////constructor///////////////////////////////////////////////////////
			// default (1)	
			pair(void) : first(), second()
			{

			}

			// copy (2)	
			template<class U, class V>
			pair (const pair<U,V>& pr) : first(pr.first), second(pr.second)
			{

			}

			// initialization (3)	
			pair (const first_type& a, const second_type& b) : first(a), second(b)
			{

			}

		////operator=///////////////////////////////////////////////////////
			// copy (1)	
			pair& operator=(const pair& pr)
			{
				alloc_first.construct(&this->first, pr.first);
				alloc_second.construct(&this->second, pr.second);
				return (*this);
			}
	};
	//NON-MEMBER FUNCTION OVERLOADS
		////relational operators (pair)///////////////////////////////////////////////////////
			// (1)
			template <class T1, class T2>
			bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{
				return (lhs.first == rhs.first && lhs.second == rhs.second);
			}

			// (2)
			template <class T1, class T2>
			bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{
				return !(lhs == rhs);
			}

			// (3)
			template <class T1, class T2>
			bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{
				return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
			}

			// (4)
			template <class T1, class T2>
			bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{
				return !(rhs < lhs);
			}

			// (5)
			template <class T1, class T2>
			bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{
				return (rhs < lhs);
			}

			// (6)
			template <class T1, class T2>
			bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{
				return !(lhs < rhs);
			}	

	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}
}