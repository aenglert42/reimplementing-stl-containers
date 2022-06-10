//MEMBER FUNCTIONS

	////constructor///////////////////////////////////////////////////////
		// default (1)	
		// explicit vector (const allocator_type& alloc = allocator_type());

		// fill (2)	
		// explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());

		// range (3)	
		// template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());

		// copy (4)	
		// vector (const vector& x);

	////destructor///////////////////////////////////////////////////////
		// ~vector();

	////operator=///////////////////////////////////////////////////////
		// copy (1)	
		// vector& operator= (const vector& x);

//Iterators---------------------------------------------------------------
	////begin///////////////////////////////////////////////////////
		// iterator begin();
		// const_iterator begin() const;

	////end///////////////////////////////////////////////////////
		// iterator end();
		// const_iterator end() const;

	////rbegin///////////////////////////////////////////////////////
		// reverse_iterator rbegin();
		// const_reverse_iterator rbegin() const;

	////rend///////////////////////////////////////////////////////
		// reverse_iterator rend();
		// const_reverse_iterator rend() const;

//Capacity---------------------------------------------------------------
	////size///////////////////////////////////////////////////////
		// size_type size() const;

	////max_size///////////////////////////////////////////////////////
		// size_type max_size() const;

	////resize///////////////////////////////////////////////////////
		// void resize (size_type n, value_type val = value_type());

	////capacity///////////////////////////////////////////////////////
		// size_type capacity() const;

	////empty///////////////////////////////////////////////////////
		// bool empty() const;

	////reserve///////////////////////////////////////////////////////
		// void reserve (size_type n);

//Element access---------------------------------------------------------------
	////operator[]///////////////////////////////////////////////////////
		// reference operator[] (size_type n);
		// const_reference operator[] (size_type n) const;

	////at///////////////////////////////////////////////////////
		// reference at (size_type n);
		// const_reference at (size_type n) const;

	////front///////////////////////////////////////////////////////
		// reference front();
		// const_reference front() const;

	////back///////////////////////////////////////////////////////
		// reference back();
		// const_reference back() const;

//Modifiers---------------------------------------------------------------
	////assign///////////////////////////////////////////////////////
		// range (1)	
		// template <class InputIterator> void assign (InputIterator first, InputIterator last);

		// fill (2)	
		// void assign (size_type n, const value_type& val);

	////puch_back///////////////////////////////////////////////////////
		// void push_back (const value_type& val);

	////pop_back///////////////////////////////////////////////////////
		// void pop_back();

	////insert///////////////////////////////////////////////////////
		// single element (1)	
		// iterator insert (iterator position, const value_type& val);

		// fill (2)	
		// void insert (iterator position, size_type n, const value_type& val);

		// range (3)	
		// template <class InputIterator> void insert (iterator position, InputIterator first, InputIterator last);

	////erase///////////////////////////////////////////////////////
		// iterator erase (iterator position);
		// iterator erase (iterator first, iterator last);

	////swap///////////////////////////////////////////////////////
		// void swap (vector& x);

	////clear///////////////////////////////////////////////////////
		// void clear();

//Allocator---------------------------------------------------------------
	////get_allocator///////////////////////////////////////////////////////
		// allocator_type get_allocator() const;

//NON-MEMBER FUNCTION OVERLOADS
	////relational operators///////////////////////////////////////////////////////
		// (1)
		// template <class T, class Alloc> bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

		// (2)
		// template <class T, class Alloc> bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

		// (3)
		// template <class T, class Alloc> bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

		// (4)
		// template <class T, class Alloc> bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

		// (5)
		// template <class T, class Alloc> bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

		// (6)
		// template <class T, class Alloc> bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	////swap///////////////////////////////////////////////////////
		// template <class T, class Alloc> void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);