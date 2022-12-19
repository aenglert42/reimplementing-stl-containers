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
	class Compare = ft::less<content_type> >
	// class Alloc = typename std::allocator<content_type> > // AE build this in later
	class Tree
	{
		public:
			typedef Node<content_type>							node_type;
			// typedef typename node_type::key_type				key_type; // AE uncommenting this will make node<int> invalid
			// typedef typename node_type::value_type			value_type; // AE uncommenting this will make node<int> invalid
			typedef Compare										value_compare;
			typedef typename node_type::allocator_type			allocator_type;
			typedef TreeIterator<content_type>					iterator;
			typedef TreeIterator<const content_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		
		private:
			node_type* _root;
			node_type* _end_node;
			allocator_type _allocator;
			value_compare _compare;

			// bool first_is_less_than_second(const node_type* new_node, node_type* node)
			// {
			// 	if (node == _end_node)
			// 		return (true);
			// 	return (new_node->_content < node->_content);
			// }

			bool first_is_less_than_second(const content_type& val, node_type* node)
			{
				if (node == _end_node)
					return (true);
				return (_compare(val, node->_content));
			}

			bool first_is_greater_than_second(const content_type& val, node_type* node)
			{
				if (node == _end_node)
					return (false);
				return (_compare(node->_content, val));
			}

			// bool first_is_less_than_second(const content_type& val, node_type* node)
			// {
			// 	if (node == _end_node)
			// 		return (true);
			// 	return (val < node->_content);
			// }

			// bool first_is_greater_than_second(const content_type& val, node_type* node)
			// {
			// 	if (node == _end_node)
			// 		return (false);
			// 	return (val > node->_content);
			// }

			// node_type* insert(const node_type* new_node, node_type* node, node_type* parent)
			// {
			// 	if (node == ft_nullptr)
			// 		node = new node_type(val, parent); // AE change to alloc
			// 	else if (first_is_less_than_second(val, node))
			// 	{
			// 		node->_left_child = insert(val, node->_left_child, node);
			// 		node->_parent = parent;
			// 	}
			// 	else if (val > node->_content)
			// 	{
			// 		node->_right_child = insert(val, node->_right_child, node);
			// 		node->_parent = parent;
			// 	}
			// 	return (node);
			// }

			node_type* insert(const content_type& val, node_type* node, node_type* parent)
			{
				if (node == ft_nullptr)
					node = new node_type(val, parent); // AE change to alloc
				else if (first_is_less_than_second(val, node))
				{
					node->_left_child = insert(val, node->_left_child, node);
					node->_parent = parent;
				}
				else if (val > node->_content)
				{
					node->_right_child = insert(val, node->_right_child, node);
					node->_parent = parent;
				}
				return (node);
			}

			// node_type* insert(const content_type& val, iterator node, node_type* parent)
			// {
			// 	return (insert(val, node, parent));
			// }

			node_type* remove_node_with_one_child(node_type* node, node_type* child)
			{
				child->_parent = node->_parent;
				delete node; // AE change to dealloc
				return (child);
			}

			node_type* remove_node_with_two_children(node_type* node)
			{
				node_type* tmp = get_leftmost_node(node->_right_child);
				node->_content = tmp->_content;
				node->_right_child = erase(tmp->_content, node->_right_child);
				return (node);
			}

			node_type* remove_node(node_type* node)
			{
				if (node->_left_child == ft_nullptr && node->_right_child == ft_nullptr)
					return(ft_nullptr);
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
				else if (val < node->_content)
					node->_left_child = erase(val, node->_left_child);
				else if (val > node->_content)
					node->_right_child = erase(val, node->_right_child);
				else
					node = remove_node(node);
				return (node);
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
		
		public:
			Tree(void) : _root(ft_nullptr), _end_node(ft_nullptr), _allocator()
			{
				_end_node = _allocator.allocate(1);
				_allocator.construct(_end_node, node_type());
				_root = _end_node;
			}

			Tree(const content_type& val) : _root(ft_nullptr), _end_node(ft_nullptr), _allocator()
			{
				_end_node = _allocator.allocate(1);
				_allocator.construct(_end_node, node_type());
				_root = _end_node;
				_root = insert(val, _root, _root);
			}

			~Tree(void)
			{
				// delete _root;
				if (_end_node != ft_nullptr)
				{
					_allocator.destroy(_end_node);
					_allocator.deallocate(_end_node, 1);
				}
				_root = ft_nullptr;
				_end_node = ft_nullptr;
			}

			iterator begin()
			{
				return(iterator(get_leftmost_node(_root)));
			}

			iterator end()
			{
				return(iterator(get_rightmost_node(_root)));
			}

			// void insert(const content_type& val)
			// {
			// 	_root = insert(val, _root, ft_nullptr);
			// }

			ft::pair<iterator,bool> insert(const content_type& val)
			{
				bool key_is_new = true;
				node_type* tmp = find(val); // AE have insert function that returns node* on success or ft_nullptr
				_root = insert(val, _root, ft_nullptr);
				if (tmp != ft_nullptr)
					key_is_new = false;
				else
					tmp = find(val);
				return (ft::make_pair(tmp , key_is_new));
			}

			iterator insert(iterator position, const content_type& val)
			{
				(void)position;
				if (first_is_greater_than_second(val, position.base()))
					insert(val, position.base(), position.base()->_parent); // AE what if this would be first node? What happens with root / parent?
				else
					_root = insert(val, _root, ft_nullptr);
				return (find(val));
			}

			void erase(const content_type& val)
			{
				_root = erase(val, _root);
			}

			node_type* find(const content_type& val)
			{
				node_type* tmp = _root->_left_child; // AE this is a workaround while _end_node is _root
				while (tmp != ft_nullptr && (!first_is_less_than_second(val, tmp) && !first_is_greater_than_second(val, tmp)))
				{
					if (first_is_less_than_second(val, tmp))
						tmp = tmp->_left_child;
					else
						tmp = tmp->_right_child;
				}
				return (tmp);
			}

			void pre(const content_type& val)
			{
				std::cout << get_predecessor_node(find2(val))->_content << std::endl;
			}

			void post(const content_type& val)
			{
				std::cout << get_successor_node(find2(val))->_content << std::endl;
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