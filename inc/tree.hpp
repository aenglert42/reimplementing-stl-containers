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
	template <class content_type,
	class key_type = content_type,
	class Compare = ft::less<content_type> >
	// class GetKey = ft::identity<content_type>, identity returns what it gets via argument

	class Tree
	{
		public:
			typedef Node<content_type>								node_type;
			typedef std::allocator<node_type>						allocator_type;
			typedef Compare											value_compare;
			typedef TreeIterator<content_type, node_type*>			iterator;
			typedef TreeIterator<const content_type, node_type*>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef std::size_t										size_type;

		private:
			size_type _size;
			node_type* _root;
			node_type* _end_node;
			node_type* _rend_node;
			allocator_type _allocator;
			value_compare _compare;

			bool lhs_node_is_less_than_rhs_node (node_type* lhs, node_type* rhs)
			{
				if (lhs == rhs)
					return (false);
				else if (lhs == _end_node)
					return (false);
				else if (rhs == _end_node)
					return (true);
				else if (lhs == _rend_node)
					return (true);
				else if (rhs == _rend_node)
					return (false);
				return (_compare(lhs->_content, rhs->_content));
			}

			bool lhs_node_is_greater_than_rhs_node (node_type* lhs, node_type* rhs)
			{
				return (lhs_node_is_less_than_rhs_node(rhs, lhs));
			}

			bool lhs_node_is_equal_to_rhs_node (node_type* lhs, node_type* rhs)
			{
				return (!lhs_node_is_less_than_rhs_node(lhs, rhs) && !lhs_node_is_less_than_rhs_node(rhs, lhs));
			}

			node_type* my_new (const content_type& val, node_type* parent)
			{
				node_type* node = _allocator.allocate(1);
				_allocator.construct(node, node_type(val, parent));
				return (node);
			}

			void my_delete (node_type* node)
			{
				if (node == ft_nullptr)
					return ;
				_allocator.destroy(node);
				_allocator.deallocate(node, 1);
			}

			bool first_is_less_than_second (const content_type& val, node_type* node) const
			{
				if (node == _end_node)
					return (true);
				else if (node == _rend_node)
					return (false);
				return (_compare(val, node->_content));
			}

			bool first_equals_second (const content_type& val, node_type* node) const
			{
				bool less;
				bool greater;

				if (node == _end_node || node == _rend_node)
					return (false);
				less = _compare(val, node->_content);
				greater = _compare(node->_content, val);
				if (less == false && greater == false)
					return (true);
				return (false);
			}

			bool first_is_greater_than_second (const content_type& val, node_type* node) const
			{
				if (node == _end_node)
					return (false);
				else if (node == _rend_node)
					return (true);
				return (_compare(node->_content, val));
			}

			int check_balance (node_type* node)
			{
				if (node == ft_nullptr)
					return(0);
				return (get_height(node->_left_child) - get_height(node->_right_child));
			}

			size_type get_height (node_type* node)
			{
				if (node == ft_nullptr)
					return (0);
				return (node->_height);
			}

			void update_height (node_type* node)
			{
				if (node == ft_nullptr)
					return ;
				node->_height = 1 + std::max(get_height(node->_left_child), get_height(node->_right_child));
				update_height(node->_parent);
			}

			size_type calculate_height (node_type* node)
			{
				if (node == ft_nullptr)
					return (0);
				size_type left_height = calculate_height(node->_left_child);
				size_type right_height = calculate_height(node->_right_child);

				if (left_height > right_height)
					return (left_height + 1);
				return (right_height + 1);
			}

			void rotate_left (node_type* grandparent)
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

			void rotate_right (node_type* grandparent)
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

			void rebalance_all (node_type* node)
			{
				if (node == ft_nullptr)
					return ;
				rebalance(node);
				rebalance_all(node->_parent);
			}

			void rebalance (node_type* node)
			{
				const int MAX_DEVIATION = 1;
				int balance_factor = check_balance(node);

				// node's left subtree is longer than node's right subtree
				if (balance_factor > MAX_DEVIATION)
				{
					balance_factor = check_balance(node->_left_child);
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

			ft::pair<node_type*, bool> insert_util (const content_type& val, node_type* node, node_type* parent)
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
					rebalance_all(node);
				}
				else if (first_is_less_than_second(val, node))
				{
					tmp = insert_util(val, node->_left_child, node);
					// rebalance(node);
				}
				else if (first_is_greater_than_second(val, node))
				{
					tmp = insert_util(val, node->_right_child, node);
					// rebalance(node);
				}
				else
					tmp.first = node;
				return (tmp);
			}

			node_type* find_util (const content_type& val) const // AE look for key_type instead of content_type
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

			void swap_nodes (node_type* a, node_type* b)
			{
				if (a == ft_nullptr || b == ft_nullptr)
					return ;

				node_type tmp (*a);

				a->_parent = b->_parent;
				if (a->_parent != ft_nullptr)
				{
					if (a->_parent->_left_child == b)
						a->_parent->_left_child = a;
					else
						a->_parent->_right_child = a;
				}
				else
				{
					_root = a;
				}

				a->_left_child = b->_left_child;
				if (a->_left_child == a)
					a->_left_child = b;
				if (a->_left_child != ft_nullptr)
					a->_left_child->_parent = a;

				a->_right_child = b->_right_child;
				if (a->_right_child == a)
					a->_right_child = b;
				if (a->_right_child != ft_nullptr)
					a->_right_child->_parent = a;
				a->_height = b->_height;
				a->_is_terminator = b->_is_terminator;

				b->_parent = tmp._parent;
				if (b->_parent != ft_nullptr)
				{
					if (b->_parent->_left_child == a)
						b->_parent->_left_child = b;
					else
						b->_parent->_right_child = b;
				}
				else
				{
					_root = b;
				}

				b->_left_child = tmp._left_child;
				if (b->_left_child == b)
					b->_left_child = a;
				if (b->_left_child != ft_nullptr)
					b->_left_child->_parent = b;

				b->_right_child = tmp._right_child;
				if (b->_right_child == b)
					b->_right_child = a;
				if (b->_right_child != ft_nullptr)
					b->_right_child->_parent = b;
				b->_height = tmp._height;
				b->_is_terminator = tmp._is_terminator;
			}

			size_type remove_node_with_two_children (node_type* node)
			{
				// replace node with smallest node in right subtree
				// or
				// replace node with greatest node in left subtree
				node_type* tmp = get_rightmost_node(node->_left_child);
				swap_nodes(node, tmp);
				return (remove_node(node)); // AE check if this is a problem cause not recursive -> problem if more nodes need to be removed?
			}

			size_type remove_node_with_one_child (node_type* node, node_type* child)
			{
				if (node->_parent != ft_nullptr)
				{
					if (node->_parent->_left_child == node)
						node->_parent->_left_child = child;
					else
						node->_parent->_right_child = child;
				}
				else
					_root = child;
				child->_parent = node->_parent;
				my_delete(node);
				_size--;
				update_height(child);
				rebalance_all(child);
				return (1);
			}

			size_type remove_node_without_children (node_type* node)
			{
				if (node == ft_nullptr)
					return (0);
				if (node->_parent->_left_child == node)
					node->_parent->_left_child = ft_nullptr;
				else
					node->_parent->_right_child = ft_nullptr;
				update_height(node->_parent);
				rebalance_all(node->_parent);
				my_delete(node);
				_size--;
				return (1);
			}

 			size_type remove_node (node_type* node)
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

			size_type erase (const content_type& val, node_type* node)
			{
				size_type ret = 0;
				if (node == ft_nullptr)
					return (ret);
				else if (first_is_less_than_second(val, node))
					ret = erase(val, node->_left_child);
				else if (first_is_greater_than_second(val, node))
					ret = erase(val, node->_right_child);
				else
					ret = remove_node(node);
				return (ret);
			}

			void print_preorder (node_type* node)
			{
				if (node == ft_nullptr)
					return;
				std::cout << node->_content << " ";
				print_preorder(node->_left_child);
				print_preorder(node->_right_child);
			}

			void print_inorder (node_type* node)
			{
				if (node == ft_nullptr)
					return;
				print_inorder(node->_left_child);
				std::cout << node->_content << " ";
				print_inorder(node->_right_child);
			}

			void print_postorder (node_type* node)
			{
				if (node == ft_nullptr)
					return;
				print_postorder(node->_left_child);
				print_postorder(node->_right_child);
				std::cout << node->_content << " ";
			}

			// Function to print binary tree in 2D
			// It does reverse inorder traversal
			void print2D_util (node_type* root, int space)
			{
				std::string space_sign = "-";
				std::string end_node_name = "E";
				std::string rend_node_name = "RE";

				// Base case
				if (root == ft_nullptr)
					return;
			
				// Increase distance between levels
				space += COUNT;
			
				// Process right child first
				print2D_util(root->_right_child, space);
			
				// Print current node after space
				// count
				std::cout << std::endl;
				for (int i = COUNT; i < space; i++)
					std::cout << space_sign;
				std::cout << "[";
				if (root == _end_node)
					std::cout << end_node_name;
				else if (root == _rend_node)
					std::cout << rend_node_name;
				else
					std::cout << root->_content;
				std::cout << "]";
				std::cout << "(";
				if (root->_parent != _end_node && root->_parent != _rend_node && root->_parent != ft_nullptr)
					std::cout << root->_parent->_content;
				else if (root->_parent == _end_node)
					std::cout << end_node_name;
				else if (root->_parent == _rend_node)
					std::cout << rend_node_name;
				std::cout << ")";
				std::cout << ":" << root->_height;
			
				// Process left child
				print2D_util(root->_left_child, space);
			}
		
			void init_tree (void)
			{
				_end_node = _allocator.allocate(1);
				_allocator.construct(_end_node, node_type());
				_root = _end_node;
				_rend_node = _allocator.allocate(1);
				_allocator.construct(_rend_node, node_type());
				_end_node->_left_child = _rend_node;
				_rend_node->_parent = _end_node;
				_end_node->_height = 2;
			}

			node_type* upper_bound_util (const content_type& val, node_type* node, node_type* parent) const
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
					node = (upper_bound_util(val, node->_left_child, node));
				}
				else if (first_is_greater_than_second(val, node))
				{
					node = (upper_bound_util(val, node->_right_child, node));
				}
				return (node);
			}

			node_type* lower_bound_util (const content_type& val, node_type* node, node_type* parent) const
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
					node = (lower_bound_util(val, node->_left_child, node));
				}
				else if (first_is_greater_than_second(val, node))
				{
					node = (lower_bound_util(val, node->_right_child, node));
				}
				return (node);
			}

			void remove_range (node_type* node, node_type* low, node_type* high)
			{
				// Base case
				if (node == ft_nullptr)
					return ;

				// First fix the left and right subtrees of node
				remove_range(node->_left_child, low, high);
				remove_range(node->_right_child, low, high);

				// Now fix the node.
				// if given node is in Range then delete it
				bool is_greater_than_low = lhs_node_is_greater_than_rhs_node(node, low);
				bool is_less_than_high = lhs_node_is_less_than_rhs_node(node, high);
				if (is_greater_than_low && is_less_than_high)
					remove_node(node);
			}

		public:
			Tree (const value_compare& comp = value_compare()) : _size(0), _root(ft_nullptr), _end_node(ft_nullptr), _rend_node(ft_nullptr), _allocator(), _compare(comp)
			{
				init_tree();
			}

			Tree (const content_type& val) : _size(0), _root(ft_nullptr), _end_node(ft_nullptr), _rend_node(ft_nullptr), _allocator()
			{
				init_tree();
				insert_util(val, _root, ft_nullptr);
			}

			Tree (const Tree& other) : _size(0), _root(ft_nullptr), _end_node(ft_nullptr), _rend_node(ft_nullptr), _allocator(other._allocator)
			{
				init_tree();
				insert(other.begin(), other.end());
			}

			Tree& operator= (const Tree& other)
			{
				if (this != &other)
				{
					clear();
					insert(other.begin(), other.end());
					_compare = other._compare;
				}
				return (*this);
			}

			~Tree (void)
			{
				clear();
				my_delete(_end_node);
				my_delete(_rend_node);
				_root = ft_nullptr;
				_end_node = ft_nullptr;
				_rend_node = ft_nullptr;
			}

			size_type size (void) const
			{
				return (_size);
			}

			iterator begin ()
			{
				iterator tmp (_rend_node);
				return(++tmp);
			}

			const_iterator begin () const
			{
				const_iterator tmp (_rend_node);
				return(++tmp);
			}

			reverse_iterator rbegin ()
			{
				return (reverse_iterator(end()));
			}

			const_reverse_iterator rbegin () const
			{
				return (const_reverse_iterator(end()));
			}

			iterator end ()
			{
				return(iterator(_end_node));
			}

			const_iterator end () const
			{
				return(const_iterator(_end_node));
			}

			reverse_iterator rend ()
			{
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator rend () const
			{
				return (const_reverse_iterator(begin()));
			}

			ft::pair<iterator,bool> insert (const content_type& val)
			{
				return (insert_util(val, _root, ft_nullptr));
			}

			iterator insert (iterator position, const content_type& val)
			{
				node_type* current = position.base();
				iterator before = position;
				--before;
				if (first_is_less_than_second(val, current) && first_is_greater_than_second(val, before.base()))
					return (insert_util(val, current, current->_parent).first);
				iterator after = position;
				++after;
				if (first_is_greater_than_second(val, current) && first_is_less_than_second(val, after.base()))
					return (insert_util(val, current, current->_parent).first);

				return (insert_util(val, _root, ft_nullptr).first);
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				// // old version
				// while (first != last)
				// 	insert(*first++);

				iterator hint = iterator(_root);
				while (first != last)
					hint = insert(*first++).first;
			}

			void erase (iterator position)
			{
				if (position.base() != ft_nullptr && position != _end_node && position != _rend_node)
					remove_node(position.base());
			}

			size_type erase (const content_type& val)
			{
				return (erase(val, _root));
			}

			void erase (iterator first, iterator last)
			{
				while (first != last)
					erase(*first++);
			}

			void clear (void)
			{
				while (!empty())
					erase(begin());
			}

			iterator find (const content_type& val) // AE look for key_type instead of content_type
			{
				node_type* ret = find_util(val);

				if (ret == ft_nullptr)
					return (_end_node);
				return (ret);
			}

			const_iterator find (const content_type& val) const // AE look for key_type instead of content_type
			{
				node_type* ret = find_util(val);

				if (ret == ft_nullptr)
					return (_end_node);
				return (ret);
			}

			size_type count (const content_type& val) const // AE look for key_type instead of content_type
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

			iterator upper_bound (const content_type& val)
			{
				node_type* ret = upper_bound_util(val, _root, ft_nullptr);
				if (ret == ft_nullptr)
					return (_end_node);
				return (ret);
			}

			const_iterator upper_bound (const content_type& val) const
			{
				node_type* ret = upper_bound_util(val, _root, ft_nullptr);
				if (ret == ft_nullptr)
					return (_end_node);
				return (ret);
			}


			iterator lower_bound (const content_type& val)
			{
				node_type* ret = lower_bound_util(val, _root, ft_nullptr);
				if (ret == ft_nullptr)
					return (_end_node);
				return (ret);
			}

			const_iterator lower_bound (const content_type& val) const
			{
				node_type* ret = lower_bound_util(val, _root, ft_nullptr);
				if (ret == ft_nullptr)
					return (_end_node);
				return (ret);
			}

			bool empty () const
			{
				if (size() == 0)
					return (true);
				return (false);
			}

			void swap (Tree& other)
			{
				node_type* tmp_root = other._root;
				node_type* tmp_end_node = other._end_node;
				node_type* tmp_rend_node = other._rend_node;
				size_type tmp_size = other._size;

				other._root = _root;
				other._end_node = _end_node;
				other._rend_node = _rend_node;
				other._size = _size;

				_root = tmp_root;
				_end_node = tmp_end_node;
				_rend_node = tmp_rend_node;
				_size = tmp_size;
			}

			size_type max_size () const
			{
				return (_allocator.max_size());
			}

			void print_preorder (void)
			{
				std::cout << "Preorder:\n";
				if (empty())
					std::cout << "(empty)";
				else
					print_preorder(_root);
				std::cout << std::endl;
			}

			void print_inorder (void)
			{
				std::cout << "Inorder:\n";
				if (empty())
					std::cout << "(empty)";
				else
					print_inorder(_root);
				std::cout << std::endl;
			}

			void print_postorder (void)
			{
				std::cout << "Postorder:\n";
				if (empty())
					std::cout << "(empty)";
				else
					print_postorder(_root);
				std::cout << std::endl;
			}

			// Wrapper over print2D_util()
			void print2D (void)
			{
				std::cout << "Tree:\n";
				if (empty())
					std::cout << "(empty)";
				else
					print2D_util(_root, 0);
				std::cout << std::endl;
			}
	};

}