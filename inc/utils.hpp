#pragma once

#include <iostream> //remove

namespace ft
{
	template <class first_type, class second_type>
	struct pair
	{
		private:
			typedef std::allocator<first_type> alloctor_first;
			typedef std::allocator<second_type> alloctor_second;

			alloctor_first alloc_first;
			alloctor_second alloc_second;
		
		public:
			first_type	first;
			second_type	second;

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

			// destructor
			~pair()
			{

			}

			// assign
			pair&	operator=( const pair& pr )
			{
				alloc_first.construct(&this->first, pr.first);
				alloc_second.construct(&this->second, pr.second);
				return (*this);
			}
	};

	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}
}