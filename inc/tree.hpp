#pragma once

#include <iostream>
#include <memory> // std::allocator
#include "ft_nullptr.hpp" // ft_nullptr
#include "node.hpp"
#include "tree_iterator.hpp"
#include "utils.hpp"
#include "functional.hpp"
// #include "algorithm.hpp"
// #include "type_traits.hpp"

// Colors and Printing
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RED "\033[31m"
#define BOLD "\033[1m"
#define UNDERLINED "\033[4m"

#define COUNT 3

namespace ft
{
	template <class content_type, // AE give key and map content_type to key
	class key_type = content_type,
	class Compare = ft::less<content_type> > // AE this will be sorted wrong for pair -> no, because will get overwritten by map
	// class GetKey = ft::identity<content_type>, identity returns what it gets via argument
	// class Alloc = typename std::allocator<content_type> > // AE build this in later
	class Tree
	{
		public:
			typedef Node<content_type>							node_type;
			// typedef typename node_type::key_type				key_type; // AE uncommenting this will make node<int> invalid
			// typedef typename node_type::value_type			value_type; // AE uncommenting this will make node<int> invalid
			typedef std::allocator<node_type>					allocator_type;
			typedef Compare										value_compare;
			// typedef TreeIterator<content_type>					iterator;
			typedef TreeIterator<content_type, node_type*>			iterator;
			// typedef TreeIterator<const content_type>				const_iterator;
			typedef TreeIterator<const content_type, node_type*>		const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef std::size_t									size_type;

		private:
			size_type _size;
			node_type* _root;
			node_type* _end_node;
			allocator_type _allocator;
			value_compare _compare;

			node_type* my_new(const content_type& val, node_type* parent)
			{
				node_type* node = _allocator.allocate(1);
				_allocator.construct(node, node_type(val, parent));
				return (node);
			}

			void my_delete(node_type* node)
			{
				if (node == ft_nullptr)
					return ;
				_allocator.destroy(node);
				_allocator.deallocate(node, 1);
			}

			bool first_is_less_than_second(const content_type& val, node_type* node) const
			{
				if (node == _end_node)
					return (true);
				return (_compare(val, node->_content));
			}

			bool first_equals_second(const content_type& val, node_type* node) const
			{
				bool less;
				bool greater;

				if (node == _end_node)
					return (false);
				less = _compare(val, node->_content);
				greater = _compare(node->_content, val);
				if (less == false && greater == false)
					return (true);
				return (false);
			}

			bool first_is_greater_than_second(const content_type& val, node_type* node) const
			{
				if (node == _end_node)
					return (false);
				return (_compare(node->_content, val));
			}

			node_type* insert(const content_type& val, node_type* node, node_type* parent)
			{
				if (node == ft_nullptr)
				{
					node = my_new(val, parent); // AE change to alloc
					// node = _allocator.allocate(1);
					// _allocator.construct(node, node_type(val, parent));
					_size++;
				}
				else if (first_is_less_than_second(val, node))
				{
					node->_left_child = insert(val, node->_left_child, node);
					node->_parent = parent;
				}
				else if (first_is_greater_than_second(val, node))
				{
					node->_right_child = insert(val, node->_right_child, node);
					node->_parent = parent;
				}
				return (node);
			}

			// void update_node_pointers(node_type* old_node, node_type* new_node)
			// {
			// 	// AE nullcheck
			// 	// tmp node
			// 	node_type tmp_node = *old_node;
			// 	_allocator.destroy(old_node);
			// 	_allocator.construct(old_node, node_type(new_node->_content, tmp_node->parent));

			// 	// if (old_node->_parent->_left_child == old_node)
			// 	// 	old_node->_parent->_left_child = new_node;
			// 	// else
			// 	// 	old_node->_parent->_right_child = new_node;
			// 	// new_node->_left_child = old_node->_left_child;
			// 	// new_node->_right_child = old_node->_right_child;
			// 	// new_node->_left_child->_parent = new_node;
			// 	// new_node->_right_child->_parent = new_node;
			// 	// my_delete(old_node);
			// 	// return (new_node);
			// }

			node_type* update_node_pointers(node_type* old_node, node_type* tmp_node)
			{
				// AE nullcheck
				node_type* new_node = my_new(tmp_node->_content, old_node->_parent); // AE change to alloc
				if (old_node->_parent->_left_child == old_node)
					old_node->_parent->_left_child = new_node;
				else
					old_node->_parent->_right_child = new_node;
				new_node->_left_child = old_node->_left_child;
				new_node->_right_child = old_node->_right_child;
				new_node->_left_child->_parent = new_node;
				new_node->_right_child->_parent = new_node;
				my_delete(old_node);
				return (new_node);
			}

			// node_type* remove_node_with_two_children(node_type* node)
			// {
			// 	node_type* tmp = get_leftmost_node(node->_right_child);
			// 	node = update_node_pointers(node, tmp);
			// 	node->_right_child = erase(tmp->_content, node->_right_child);
			// 	return (node);
			// }

			node_type* remove_node_with_two_children(node_type* node)
			{
				node_type old = *node;
				// node_type* tmp = get_successor_node(node);
				node_type* tmp = get_leftmost_node(node->_right_child);
				_allocator.destroy(node);
				_allocator.construct(node, node_type(tmp->_content, old._parent));
				node->_left_child = old._left_child;
				node->_right_child = old._right_child;
				node->_right_child = erase(tmp->_content, node->_right_child);
				return (node);
			}

			node_type* remove_node_with_one_child(node_type* node, node_type* child)
			{
				child->_parent = node->_parent;
				my_delete(node);
				_size--;
				return (child);
			}

			node_type* remove_node_without_children(node_type* node)
			{
				// AE maybe implement update parent function
				if (node->_parent->_left_child == node)
					node->_parent->_left_child = ft_nullptr;
				else
					node->_parent->_right_child = ft_nullptr;
				my_delete(node);
				_size--;
				return (ft_nullptr);
			}

			node_type* remove_node(node_type* node)
			{
				if (node->_left_child == ft_nullptr && node->_right_child == ft_nullptr)
					return(remove_node_without_children(node));
				else if (node->_left_child == ft_nullptr)
					return(remove_node_with_one_child(node, node->_right_child));
				else if (node->_right_child == ft_nullptr)
					return(remove_node_with_one_child(node, node->_left_child));
				else
					return(remove_node_with_two_children(node));
			}

			node_type* erase(const content_type& val, node_type* node)
			{
				if (node == ft_nullptr)
					return (ft_nullptr);
				else if (first_is_less_than_second(val, node))
					node->_left_child = erase(val, node->_left_child);
				else if (first_is_greater_than_second(val, node))
					node->_right_child = erase(val, node->_right_child);
				else
					node = remove_node(node);
				return (node);
			}

			void delete_from_node_downwards(node_type* node)
			{
				if (node == ft_nullptr)
					return ;
				if (node->_left_child != ft_nullptr)
					delete_from_node_downwards(node->_left_child);
				if (node->_right_child != ft_nullptr)
					delete_from_node_downwards(node->_right_child);

				// AE maybe implement update parent function
				if (node->_parent->_left_child == node)
					node->_parent->_left_child = ft_nullptr;
				else
					node->_parent->_right_child = ft_nullptr;
				my_delete(node);
				_size--;
			}

			void print(node_type* node)
			{
				if (node == ft_nullptr)
					return;
				print(node->_left_child);
				std::cout << node->_content << " ";
				print(node->_right_child);
			}

			// Function to print binary tree in 2D
			// It does reverse inorder traversal
			void print2DUtil(node_type* root, int space)
			{
				// Base case
				if (root == NULL)
					return;
			
				// Increase distance between levels
				space += COUNT;
			
				// Process right child first
				print2DUtil(root->_right_child, space);
			
				// Print current node after space
				// count
				std::cout << std::endl;
				for (int i = COUNT; i < space; i++)
					std::cout << " ";
				std::cout << root->_content << "(";
				if (root->_parent != ft_nullptr)
					std::cout << root->_parent->_content;
				std::cout << ")";
			
				// Process left child
				print2DUtil(root->_left_child, space);
			}
		
			void init_tree(void)
			{
				_end_node = _allocator.allocate(1);
				_allocator.construct(_end_node, node_type());
				_root = _end_node;
			}

		public:
			Tree(const value_compare& comp = value_compare()) : _size(0), _root(ft_nullptr), _end_node(ft_nullptr), _allocator(), _compare(comp)
			{
				init_tree();
			}

			Tree(const content_type& val) : _size(0), _root(ft_nullptr), _end_node(ft_nullptr), _allocator()
			{
				init_tree();
				_root = insert(val, _root, _root);
			}

			Tree (const Tree& other) : _size(0), _root(ft_nullptr), _end_node(ft_nullptr), _allocator(other._allocator)
			{
				const_iterator first = other.begin();
				const_iterator last = other.end();

				init_tree();
				while (first != last)
					insert(*first++);
			}

			Tree& operator=(const Tree& other)
			{
				if (this != &other)
				{
					const_iterator first = other.begin();
					const_iterator last = other.end();

					clear();
					while (first != last)
						insert(*first++);
					_allocator = other._allocator;
					_compare = other._compare;
					_size = other._size;
				}
				return (*this);
			}

			~Tree(void)
			{
				clear();
				my_delete(_end_node);
				_root = ft_nullptr;
				_end_node = ft_nullptr;
			}

			size_type get_size(void) const
			{
				return (_size);
			}

			iterator begin()
			{
				return(iterator(get_leftmost_node(_root)));
			}

			const_iterator begin() const
			{
				return(const_iterator(get_leftmost_node(_root)));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(end()));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(end()));
			}

			iterator end()
			{
				return(iterator(get_rightmost_node(_root)));
			}

			const_iterator end() const
			{
				return(const_iterator(get_rightmost_node(_root)));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(begin()));
			}

			ft::pair<iterator,bool> insert(const content_type& val)
			{
				bool key_is_new = true;
				node_type* tmp = find(val); // AE have insert function that returns node* on success or ft_nullptr
				_root = insert(val, _root, ft_nullptr);
				if (tmp != ft_nullptr)
					key_is_new = false;
				else
					tmp = find(val);
				return (ft::make_pair(tmp, key_is_new));
			}

			iterator insert(iterator position, const content_type& val)
			{
				(void)position;
				// if (first_is_greater_than_second(val, position.base())) // AE this needs tuning
				// 	insert(val, position.base(), position.base()->_parent); // AE what if this would be first node? What happens with root / parent?
				// else
					_root = insert(val, _root, ft_nullptr);
				return (find(val));
			}

			void erase(node_type* node)
			{
				if (node != ft_nullptr)
					_root = erase(*node, _root); // problem if node = end()?
			}

			void erase(iterator position)
			{
				if (position.base() != ft_nullptr)
					_root = erase(*position, _root); // problem if position = end()?
			}

			size_type erase(const content_type& val)
			{
				size_type ret = 0;
				if (find(val) != ft_nullptr)
					ret = 1;
				_root = erase(val, _root);
				return (ret);
			}

			void erase (iterator first, iterator last)
			{
				_root = removeRange(_root, *first, *last);
			}

			node_type* removeRange(node_type* node, const content_type low, const content_type high)
			{

				// Base case
				if (node == ft_nullptr)
					return ft_nullptr;

				// First fix the left and right subtrees of node
				node->_left_child = removeRange(node->_left_child, low, high);
				node->_right_child = removeRange(node->_right_child, low, high);

				// Now fix the node.
				// if given node is in Range then delete it
				// if (node->data >= low && node->data <= high)
				if (!first_is_greater_than_second(low, node) && first_is_greater_than_second(high, node))
					return remove_node(node);

				// Root is out of range
				return node;
			}

			void clear(void)
			{
				delete_from_node_downwards(_end_node->_left_child);
			}

			node_type* find(const content_type& val) const // AE look for key_type instead of content_type
			{
				node_type* tmp = _root;
				while (tmp != ft_nullptr && !first_equals_second(val, tmp))
				{
					if (first_is_less_than_second(val, tmp))
						tmp = tmp->_left_child;
					else
						tmp = tmp->_right_child;
				}
				return (tmp);
			}

			size_type count(const content_type& val) const // AE look for key_type instead of content_type
			{
				node_type* tmp = _root;
				while (tmp != ft_nullptr && !first_equals_second(val, tmp))
				{
					if (first_is_less_than_second(val, tmp))
						tmp = tmp->_left_child;
					else
						tmp = tmp->_right_child;
				}
				if (tmp == ft_nullptr)
					return (0);
				return (1);
			}

			node_type* lower_bound(const content_type& val) const
			{
				node_type* tmp = get_leftmost_node(_root);
				while (tmp != ft_nullptr && (!first_is_less_than_second(val, tmp) && !first_equals_second(val, tmp)))
				{
					tmp = get_successor_node(tmp);
				}
				return (tmp);
				// node_type* tmp = get_leftmost_node(_root);
				// while (tmp != ft_nullptr && (!first_is_less_than_second(val, tmp) && !first_equals_second(val, tmp)))
				// {
				// 	if (first_is_less_than_second(val, tmp))
				// 		tmp = tmp->_left_child;
				// 	else
				// 		tmp = tmp->_right_child;
				// }
				// return (tmp);
			}

			node_type* upper_bound(const content_type& val) const
			{
				node_type* tmp = get_leftmost_node(_root);
				while (tmp != ft_nullptr && !first_is_less_than_second(val, tmp))
				{
					tmp = get_successor_node(tmp);
				}
				return (tmp);
				// node_type* tmp = _end_node->_left_child;
				// while (tmp != ft_nullptr && !first_is_less_than_second(val, tmp))
				// {
				// 	if (first_is_less_than_second(val, tmp))
				// 		tmp = tmp->_left_child;
				// 	else
				// 		tmp = tmp->_right_child;
				// }
				// return (tmp);
			}

			void print(void)
			{
				std::cout << "Root: ";
				if (_root == ft_nullptr)
					std::cout << "(empty)" << std::endl;
				else
				{
					std::cout << _root->_content << std::endl;
					print(_root);
				}
				std::cout << std::endl;
			}

			// Wrapper over print2DUtil()
			void print2D(void)
			{
				// Pass initial space count as 0
				print2DUtil(_root, 0);
				std::cout << std::endl;
			}
	};

}