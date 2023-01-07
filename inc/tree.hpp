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

			bool lhs_node_is_less_than_rhs_node(node_type* lhs, node_type* rhs)
			{
				if (lhs == rhs)
					return (false);
				else if (lhs == _end_node)
					return (false);
				else if (rhs == _end_node)
					return (true);
				return (_compare(lhs->_content, rhs->_content));
			}

			bool lhs_node_is_greater_than_rhs_node(node_type* lhs, node_type* rhs)
			{
				return (_compare(rhs->_content, lhs->_content));
			}

			bool lhs_node_is_equal_to_rhs_node(node_type* lhs, node_type* rhs)
			{
				return (!_compare(lhs->_content, rhs->_content) && !_compare(rhs->_content, lhs->_content));
			}

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

			// void update_parent(node_type* old_child, node_type* new_child)
			// {
			// 	if (old_child->_parent->_left_child == old_child)
			// 		old_child->_parent->_left_child = new_child;
			// 	else
			// 		old_child->_parent->_right_child = new_child;
			// }

			int check_balance(node_type* node)
			{
				if (node == ft_nullptr)
					return(0);
				return (get_height(node->_left_child) - get_height(node->_right_child));
			}

			size_type get_height(node_type* node)
			{
				if (node == ft_nullptr)
					return (0);
				return (node->_height);
			}

			void update_height(node_type* node)
			{
				if (node == ft_nullptr)
					return ;
				node->_height = 1 + std::max(get_height(node->_left_child), get_height(node->_right_child));
				update_height(node->_parent);
			}

			size_type calculate_height(node_type* node)
			{
				if (node == ft_nullptr)
					return (0);
				size_type left_height = calculate_height(node->_left_child);
				size_type right_height = calculate_height(node->_right_child);

				if (left_height > right_height)
					return (left_height + 1);
				return (right_height + 1);
			}

			void rotate_left(node_type* grandparent)
			{
				node_type* tmp = grandparent->_right_child;
				grandparent->_right_child = tmp->_left_child;
				tmp->_left_child = grandparent;

				if (grandparent->_right_child != ft_nullptr)
					grandparent->_right_child->_parent = grandparent;

				if (grandparent->_parent == ft_nullptr)
				{
					_root = tmp;
					tmp->_parent = ft_nullptr;
				}
				else
				{
					if (grandparent->_parent->_right_child == grandparent)
						grandparent->_parent->_right_child = tmp;
					else
						grandparent->_parent->_left_child = tmp;
					tmp->_parent = grandparent->_parent;
				}

				grandparent->_parent = tmp;
				update_height(grandparent);
			}

			void rotate_right(node_type* grandparent)
			{
				node_type* tmp = grandparent->_left_child;
				grandparent->_left_child = tmp->_right_child;
				tmp->_right_child = grandparent;

				if (grandparent->_left_child != ft_nullptr)
					grandparent->_left_child->_parent = grandparent;

				if (grandparent->_parent == ft_nullptr)
				{
					_root = tmp;
					tmp->_parent = ft_nullptr;
				}
				else
				{
					if (grandparent->_parent->_left_child == grandparent)
						grandparent->_parent->_left_child = tmp;
					else
						grandparent->_parent->_right_child = tmp;
					tmp->_parent = grandparent->_parent;
				}

				grandparent->_parent = tmp;
				update_height(grandparent);
			}

			void rebalance(node_type* node)
			{
				const int MAX_DEVIATION = 1;
				int balance_factor = check_balance(node);

				// node's left subtree is longer than node's right subtree
				if (balance_factor > MAX_DEVIATION)
				{
					balance_factor = check_balance(node->_left_child); // AE
					// child's left subtree is longer than child's right subtree
					if (balance_factor >= 0)
						rotate_right(node);
					// child's right subtree is longer than child's left subtree
					else
					{
						rotate_left(node->_left_child);
						rotate_right(node);
					}
				}
				// node's right subtree is longer than node's left subtree
				else if (balance_factor < -MAX_DEVIATION)
				{
					balance_factor = check_balance(node->_right_child);
					// child's left subtree is longer than child's right subtree
					if (balance_factor <= 0)
						rotate_left(node);
					// child's right subtree is longer than child's left subtree
					else
					{
						rotate_right(node->_right_child);
						rotate_left(node);
					}
				}
			}

			ft::pair<node_type*, bool> insert(const content_type& val, node_type* node, node_type* parent)
			{
				ft::pair<node_type*, bool> tmp;
				tmp.second = false;
				if (node == ft_nullptr)
				{
					node = my_new(val, parent);
					tmp.first = node;
					_size++;
					tmp.second = true;
					if (first_is_less_than_second(val, parent))
						parent->_left_child = node;
					else
						parent->_right_child = node;
					update_height(node);
				}
				else if (first_is_less_than_second(val, node))
				{
					tmp = insert(val, node->_left_child, node);
					rebalance(node);
				}
				else if (first_is_greater_than_second(val, node))
				{
					tmp = insert(val, node->_right_child, node);
					rebalance(node);
				}
				else
					tmp.first = node;
				return (tmp);
			}

			// node_type* update_node_pointers(node_type* old_node, node_type* tmp_node)
			// {
			// 	// AE nullcheck
			// 	node_type* new_node = my_new(tmp_node->_content, old_node->_parent); // AE change to alloc
			// 	if (old_node->_parent->_left_child == old_node)
			// 		old_node->_parent->_left_child = new_node;
			// 	else
			// 		old_node->_parent->_right_child = new_node;
			// 	new_node->_left_child = old_node->_left_child;
			// 	new_node->_right_child = old_node->_right_child;
			// 	new_node->_left_child->_parent = new_node;
			// 	new_node->_right_child->_parent = new_node;
			// 	my_delete(old_node);
			// 	return (new_node);
			// }

			// void swap_nodes(node_type* a, node_type* b)
			// {
			// 	node_type* tmp = a;


			// }

			node_type* remove_node_with_two_children(node_type* node)
			{
				node_type old = *node;
				// replace node's content with content of smallest node in right subtree
				// node_type* tmp = get_leftmost_node(node->_right_child);
				// or
				// replace node's content with content of greatest node in left subtree
				node_type* tmp = get_rightmost_node(node->_left_child);
				_allocator.destroy(node); // AE try to use swap_nodes instead
				_allocator.construct(node, node_type(tmp->_content, old._parent));
				node->_left_child = old._left_child;
				node->_right_child = old._right_child;
				node->_height = old._height;
				// node->_right_child = erase(tmp->_content, node->_right_child);
				// or
				node->_left_child = erase(tmp->_content, node->_left_child);
				// AE update height -> will be done in with one / without child
				return (node);
			}

			node_type* remove_node_with_one_child(node_type* node, node_type* child)
			{
				child->_parent = node->_parent;
				my_delete(node);
				_size--;
				update_height(child);
				return (child);
			}

			node_type* remove_node_without_children(node_type* node)
			{
				// AE maybe implement update parent function, nullcheck ?
				if (node->_parent->_left_child == node)
					node->_parent->_left_child = ft_nullptr;
				else
					node->_parent->_right_child = ft_nullptr;
				update_height(node->_parent);
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

			node_type* erase (const content_type& val, node_type* node)
			{
				if (node == ft_nullptr)
					return (ft_nullptr);
				else if (first_is_less_than_second(val, node))
					node->_left_child = erase(val, node->_left_child);
				else if (first_is_greater_than_second(val, node))
					node->_right_child = erase(val, node->_right_child);
				else
					node = remove_node(node);
				rebalance(node);
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

			void print_preorder(node_type* node)
			{
				if (node == ft_nullptr)
					return;
				std::cout << node->_content << " ";
				print_preorder(node->_left_child);
				print_preorder(node->_right_child);
			}

			void print_inorder(node_type* node)
			{
				if (node == ft_nullptr)
					return;
				print_inorder(node->_left_child);
				std::cout << node->_content << " ";
				print_inorder(node->_right_child);
			}

			void print_postorder(node_type* node)
			{
				if (node == ft_nullptr)
					return;
				print_postorder(node->_left_child);
				print_postorder(node->_right_child);
				std::cout << node->_content << " ";
			}

			// Function to print binary tree in 2D
			// It does reverse inorder traversal
			void print2DUtil(node_type* root, int space)
			{
				std::string end_node_name = "E";

				// Base case
				if (root == ft_nullptr)
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
				std::cout << "[";
				if (root == _end_node)
					std::cout << end_node_name;
				else
					std::cout << root->_content;
				std::cout << "]";
				std::cout << "(";
				if (root->_parent != _end_node && root->_parent != ft_nullptr)
					std::cout << root->_parent->_content;
				else if (root->_parent == _end_node)
					std::cout << end_node_name;
				std::cout << ")";
				std::cout << ":" << root->_height;
			
				// Process left child
				print2DUtil(root->_left_child, space);
			}
		
			void init_tree(void)
			{
				_end_node = _allocator.allocate(1);
				_allocator.construct(_end_node, node_type());
				_root = _end_node;
			}

			node_type* copy_tree(node_type* node, node_type* parent)
			{
				if (node == ft_nullptr)
					return (ft_nullptr);
				
				node_type* ret = my_new(node->_content, parent);
				ret->_right_child = copy_tree(node->_right_child, ret);
				ret->_left_child = copy_tree(node->_left_child, ret);
				return ret;
			}

		public:
			Tree(const value_compare& comp = value_compare()) : _size(0), _root(ft_nullptr), _end_node(ft_nullptr), _allocator(), _compare(comp)
			{
				init_tree();
			}

			Tree(const content_type& val) : _size(0), _root(ft_nullptr), _end_node(ft_nullptr), _allocator()
			{
				init_tree();
				insert(val, _root, ft_nullptr);
			}

			Tree (const Tree& other) : _size(other._size), _root(ft_nullptr), _end_node(ft_nullptr), _allocator(other._allocator)
			{
				init_tree();
				_root->_left_child = copy_tree(other._root->_left_child, _root); // AE after change to AVL tree _end_node _root or _root->_left_child
			}

			Tree& operator=(const Tree& other)
			{
				if (this != &other)
				{
					clear();
					_root->_left_child = copy_tree(other._root->_left_child, _root); // AE after change to AVL tree _end_node _root or _root->_left_child
					// _allocator = other._allocator;
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

			size_type size(void) const
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
				return (insert(val, _root, ft_nullptr));
			}

			iterator insert(iterator position, const content_type& val) // AE improve performance for benchmark (file stl_tree.h, function _M_get_insert_hint_unique_pos, line 2193)
			{
				(void)position;

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// old version
				iterator tmp = position;
				iterator next = position;
				++next;
				if (first_is_greater_than_second(val, tmp.base()) && first_is_less_than_second(val, next.base()))
				{
					// _root = insert(val, _root, ft_nullptr);
					// std::cout << YELLOW << "\nGOOD HINT!" << RESET << std::endl;
					return (insert(val, tmp.base(), tmp.base()->_parent).first);
				}
				else
				{
					// std::cout << YELLOW << "\nBAD HINT!" << RESET << std::endl;
					return (insert(val, _root, ft_nullptr).first);
				}
				// if (first_is_greater_than_second(val, position.base())) // AE this needs tuning
				// 	insert(val, position.base(), position.base()->_parent); // AE what if this would be first node? What happens with root / parent?
				// else
					// _root = insert(val, _root, ft_nullptr);
					// _root = insert(val, position.base(), position.base()->_parent);
				// return (find(val));

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// alternative ignore hint
				// return (insert(val, _root, ft_nullptr).first);

				/*
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// from stl

				
				if (position == end()) // end()
				{
					if (size() > 0 && _M_impl._M_key_compare(_S_key(_M_rightmost()), __k))
						return _Res(0, _M_rightmost());
					else
						return _M_get_insert_unique_pos(__k);
				}
				else if (_M_impl._M_key_compare(__k, _S_key(position._M_node)))
				{
					// First, try before...
					iterator before = position;
					if (position == begin()) // begin()
						return _Res(_M_leftmost(), _M_leftmost());
					else if (_M_impl._M_key_compare(_S_key((--before)._M_node), __k))
					{
						if (_S_right(before._M_node) == 0)
							return _Res(0, before._M_node);
						else
							return _Res(position._M_node, position._M_node);
					}
					else
						return _M_get_insert_unique_pos(__k);
				}
				else if (_M_impl._M_key_compare(_S_key(position._M_node), __k))
				{
					// ... then try after.
					iterator after = position;
					if (position._M_node == _M_rightmost())
						return _Res(0, _M_rightmost());
					else if (_M_impl._M_key_compare(__k, _S_key((++after)._M_node)))
					{
						if (_S_right(position._M_node) == 0)
							return _Res(0, position._M_node);
						else
							return _Res(after._M_node, after._M_node);
					}
					else
						return _M_get_insert_unique_pos(__k);
				}
				else // Equivalent keys.
					return _Res(position._M_node, 0);
				*/
			}

			void erase (iterator position)
			{
				if (position.base() != ft_nullptr && position != _end_node)
					erase(*position, _root);
			}

			size_type erase (const content_type& val)
			{
				size_type ret = 0;
				if (find(val) != ft_nullptr)
					ret = 1;
				erase(val, _root);
				return (ret);
			}

			void erase (iterator first, iterator last) // AE improve performance for benchmark
			{
				removeRange(_root, first.base(), last.base());
				erase(first);
			}

			node_type* removeRange(node_type* node, node_type* low, node_type* high)
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
				// if (!first_is_greater_than_second(low, node) && first_is_greater_than_second(high, node))
				bool is_greater_than_low = lhs_node_is_greater_than_rhs_node(node, low);
				bool is_less_than_high = lhs_node_is_less_than_rhs_node(node, high);
				if (is_greater_than_low && is_less_than_high)
				// if (!lhs_node_is_greater_than_rhs_node(low, node) && lhs_node_is_greater_than_rhs_node(high, node))
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

			node_type* upper_bound(const content_type& val, node_type* node, node_type* parent) const
			{
				if (node == ft_nullptr)
				{
					if (first_is_greater_than_second(val, parent))
						node = (get_successor_node(parent));
					else
						node = parent;
				}
				else if (first_equals_second(val, node))
					node = (get_successor_node(node));
				else if (first_is_less_than_second(val, node))
				{
					node = (upper_bound(val, node->_left_child, node));
				}
				else if (first_is_greater_than_second(val, node))
				{
					node = (upper_bound(val, node->_right_child, node));
				}
				return (node);
			}

			node_type* upper_bound(const content_type& val) const
			{
				if (empty())
					return (_end_node);
				return (upper_bound(val, _root->_left_child, ft_nullptr));
			}

			node_type* lower_bound(const content_type& val, node_type* node, node_type* parent) const
			{
				if (node == ft_nullptr)
				{
					if (first_is_greater_than_second(val, parent))
						node = (get_successor_node(parent));
					else
						node = parent;
				}
				else if (first_is_less_than_second(val, node))
				{
					node = (lower_bound(val, node->_left_child, node));
				}
				else if (first_is_greater_than_second(val, node))
				{
					node = (lower_bound(val, node->_right_child, node));
				}
				return (node);
			}

			node_type* lower_bound(const content_type& val) const
			{
				if (empty())
					return (_end_node);
				return (lower_bound(val, _root->_left_child, ft_nullptr));
			}

			bool empty() const
			{
				if (size() == 0)
					return (true);
				return (false);
			}

			void print_preorder(void)
			{
				std::cout << "Preorder:\n";
				if (empty())
					std::cout << "(empty)";
				else
					print_preorder(_root->_left_child);
				std::cout << std::endl;
			}

			void print_inorder(void)
			{
				std::cout << "Inorder:\n";
				if (empty())
					std::cout << "(empty)";
				else
					print_inorder(_root->_left_child);
				std::cout << std::endl;
			}

			void print_postorder(void)
			{
				std::cout << "Postorder:\n";
				if (empty())
					std::cout << "(empty)";
				else
					print_postorder(_root->_left_child);
				std::cout << std::endl;
			}

			// Wrapper over print2DUtil()
			void print2D(void)
			{
				std::cout << "Tree:\n";
				if (empty())
					std::cout << "(empty)";
				else
					print2DUtil(_root, 0);
				std::cout << std::endl;
			}
	};

}