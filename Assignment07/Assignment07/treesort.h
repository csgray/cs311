// treesort.h 
// Corey S. Gray, based on Glenn G. Chappell's skeleton file
// 20 Nov 2017
//
// For CS 311 Fall 2017
// Header for function template treesort
// There is no associated source file.

#ifndef FILE_TREESORT_H_INCLUDED
#define FILE_TREESORT_H_INCLUDED

#include <type_traits>	// for std::remove_reference
#include <memory>		// for std::shared_ptr, std::make_shared

// struct BSTreeNode
// Binary Search Tree node with client-specified value type. BSTreeNode objects
// should be created with std::make_shared and owned by a std::shared_ptr. An
// empty tree consists of an empty std::shared_ptr.
// 
// Invariants:
//		_data == data
//		_left == left or nullptr
//		_right == right or nullptr
// Requirements on Types:
//		ValType must have a copy constructor and a destructor.
//		ValType's destructor must not throw.
//		ValType must have operator< for treeInsert to function.
template<typename ValType>
struct BSTreeNode {
	ValType _data;
	std::shared_ptr<BSTreeNode<ValType>> _left;
	std::shared_ptr<BSTreeNode<ValType>> _right;

	// Parameterized Constructor
	// Creates a BSTreeNode holding data with no children,
	// unless children are passed as additional parameters.
	//
	// Preconditions:
	//		data is not empty
	//		data satisfies the ValType requirements
	// Postconditions:
	//		_data == data
	//		_left == left if passed, otherwise nullptr
	//		_right == right if passed, otherwise nullptr
	// Exceptions:
	//		Throws when and what a ValType operation throws.
	// Strong Guarantee, Exception Neutral
	explicit BSTreeNode(const ValType & data,
			   std::shared_ptr<BSTreeNode<ValType>> left = nullptr,
			   std::shared_ptr<BSTreeNode<ValType>> right = nullptr)
			   : _data(data)
			   , _left(left)
			   , _right(right)
	{}

	// Destructor
	~BSTreeNode() = default;
};

// treeInsert
// Inserts a BSTreeNode in the correct position in the Binary Search Tree by
// comparing data to the _data in a node's children then making recursive
// calls on left or right children until finding a nullptr and replacing that.
//
// Preconditions:
//		node must be a shared_ptr to a BSTreeNode or a nullptr
// Requirements on Types:
//		ValType must have a copy constructor and a destructor.
//		ValType's destructor must not throw.
//		ValType must have operator<.
// Exceptions:
//		Throws when and what a ValType operation throws.
//		std::make_shared may throw std::bad_alloc
// Recursive, Stable, Strong Guarantee, Exception Neutral
template<typename ValType>
void treeInsert(std::shared_ptr<BSTreeNode<ValType>> & node,
				const ValType & data)
{
	// Base Case
	if (node == nullptr)
	{
		node = std::make_shared<BSTreeNode<ValType>>(data);
		return;
	}
	
	// Data less than node's _data goes to the left of the node
	if (data < node->_data)	
		treeInsert(node->_left, data);

	// Data greater than or equal to node's data goes to the right of the node
	else					
		treeInsert(node->_right, data);
}

// treeTraverse
// Conducts an inorder (root between children) traversal of a Binary Search Tree
//
// Preconditions:
//		node must be a shared_ptr to a BSTreeNode or a nullptr
// Postconditions:
//		Binary Search Tree
// Requirements on Types:
//		ValType must have a copy constructor and a destructor.
//		ValType's destructor must not throw.
//		ValType must have operator<.
//		FDIter must be a forward iterator.
// Exceptions:
//		Throws when and what a ValType operation throws.
//		std::make_shared may throw std::bad_alloc
// Recursive, No-Throw Guarantee, Exception Neutral
template<typename ValType, typename FDIter>
void treeTraverse(std::shared_ptr<BSTreeNode<ValType>> & node,
				  FDIter & iter)
{
	// Base Case
	// nullptr marks the end of a branch of a Binary Search Tree
	if (node == nullptr)
		return;

	treeTraverse(node->_left, iter);	// Traverse left branch
	*iter++ = node->_data;				// Update iterator with root's value
	treeTraverse(node->_right, iter);	// Traverse right branch
}

// treesort
// Sort a given range using Treesort.
//
// Preconditions:
//		first and last must be iterators in the same range
//		last must be equal to or greater than first
// Postconditions:
//		Range of values indicated by first and last are sorted.
// Requirements on Types:
//		ValType must have a copy constructor and a destructor.
//		ValType's destructor must not throw.
//		ValType must have operator<.
//		FDIter must be a forward iterator.
// Exceptions:
//		Throws when and what a ValType operation throws.
//		std::make_shared may throw std::bad_alloc
// Stable, Strong Guarantee, Exception Neutral
template<typename FDIter>
void treesort(FDIter first, FDIter last)
{
    // Get the type that FDIter points to
    using ValType = typename std::remove_reference<decltype(*first)>::type;

	// Create a Binary Search Tree by starting with an empty BSTreeNode then
	// calling treeInsert for each value within the range of iterators
	std::shared_ptr<BSTreeNode<ValType>> head = nullptr;
	for (FDIter item = first; item != last; ++item)
		treeInsert(head, *item);

	// Update original range by calling treeTraverse on the Binary Search Tree's
	// head (root) and the first iterator in the original range
	treeTraverse(head, first);
}

#endif //#ifndef FILE_TREESORT_H_INCLUDED
