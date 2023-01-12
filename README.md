# WORK IN PROGRESS
This project is about reimplementing some container types of the C++ standard template library to practice generic programming with templates. Inspired by the "42 Coding School" exercise "ft_containers" (November 2022).
</br>

## Table of contents
* [Introduction](#introduction)
  * [Requirements](#requirements)
* [Approach](#approach)
* [Prerequisites](#prerequisites)
* [How to use](#how-to-use)
* [Resources](#resources)
* [Notes](#notes)

## Introduction
###### <p align="right">Next: [Approach](#approach)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
Reimplement the following:
* vector (with iterator)
* map (with iterator)
* iterator_traits
* reverse_iterator
* enable_if
* is_integral
* equal
* lexicographical_compare
* pair
* make_pair
</br></br></br>

### Requirements
* reimplement all member functions, non-member functions and overloads
* follow the original naming
* comply with C++98 standard
* use std::allocator
</br></br></br>

## Approach
###### <p align="right">Next: [Prerequisites](#prerequisites)&emsp;Previous: [Introduction](#introduction)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
"Text for Approach"
</br></br></br>

## Prerequisites
###### <p align="right">Next: [How to use](#how-to-use)&emsp;Previous: [Approach](#approach)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
"Text for Prerequisites"
</br></br></br>

## How to use
###### <p align="right">Next: [Resources](#resources)&emsp;Previous: [Prerequisites](#prerequisites)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
"Text for How to use"
</br></br></br>

## Resources
###### <p align="right">Next: [Notes](#notes)&emsp;Previous: [How to use](#how-to-use)&emsp;&emsp;[[Contents](#table-of-contents)]</p>

[The Cherno](https://www.youtube.com/c/TheChernoProject)'s YouTube videos of reimplementing [vector](https://www.youtube.com/watch?v=ryRf4Jh_YC0) with [iterator](https://www.youtube.com/watch?v=F9eDv-YIOQ0).</br>
</br>

[RobEdward](https://www.youtube.com/@RobEdwardsVideos)'s YouTube videos about trees:</br>
[AVL Tree 5 checking balance in an AVL tree](https://www.youtube.com/watch?v=iNy6c4Q9Umw)</br>
[AVL Tree 6 Rebalancing AVL trees](https://www.youtube.com/watch?v=wn1tc5SAGZk)</br>
[Trees 9 Introduction to rotations](https://www.youtube.com/watch?v=M0Y3kDuyUCU)</br>
[Trees 10 Rotations](https://www.youtube.com/watch?v=NczBLeco6XA)</br>
[Trees 11 Coding Rotations](https://www.youtube.com/watch?v=Y-nmgO8ALjM)</br>
</br>

[AVL Tree Visualizer](https://www.cs.usfca.edu/~galles/visualization/AVLtree.html) to play around and to understand how an AVL tree works step by step.</br>
</br>

https://www.geeksforgeeks.org/deletion-in-binary-search-tree/</br>
https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/</br>
https://www.geeksforgeeks.org/insertion-in-an-avl-tree/</br>
https://www.geeksforgeeks.org/deletion-in-an-avl-tree/</br>
https://www.geeksforgeeks.org/binary-tree-iterator-for-inorder-traversal/</br>
https://www.geeksforgeeks.org/remove-bst-keys-in-a-given-range/</br>
https://www.educative.io/answers/how-to-balance-an-avl-tree</br>
</br></br></br>

## Notes
###### <p align="right">Previous: [Resources](#resources)&emsp;&emsp;[[Contents](#table-of-contents)]</p>
The STL map uses a red-black tree as it's underlying data structure. For my implementation I am using an AVL tree.
</br></br></br>
