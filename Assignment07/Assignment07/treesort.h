// treesort.h  INCOMPLETE
// Glenn G. Chappell
// 15 Nov 2017
//
// For CS 311 Fall 2017
// Header for function template treesort
// There is no associated source file.

#ifndef FILE_TREESORT_H_INCLUDED
#define FILE_TREESORT_H_INCLUDED

#include <type_traits>	// for std::remove_reference
#include <iterator>
#include <memory>		// for std::shared_ptr, std::make_shared


// struct BSTreeNode
// Binary Search Tree node with client-specified value type. BSTreeNode objects
// should be created with std::make_shared and owned by a std::shared_ptr. An
// empty list consists of an empty std::shared_ptr.
// 
// Invariants:
//
// Requirements on Types:
//		ValType must have a copy constructor and a destructor.
//		ValType's destructor must not throw.
template<typename ValType>
struct BSTreeNode {
	ValType _data;
	std::shared_ptr<BSTreeNode<ValType>> _left;
	std::shared_ptr<BSTreeNode<ValType>> _right;

	// Parameterized Constructor
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
template<typename ValType>
void treeInsert(std::shared_ptr<BSTreeNode<ValType>> & node,
				ValType data)
{
	if (node == nullptr)				// Empty Binary Search Tree
	{
		node = std::make_shared<BSTreeNode<ValType>>(data);
		return;
	}
	
	if (data < node->_data)				// Data less than node's _data
	{
		treeInsert(node->_left, data);
		return;
	}

	else								// Data greater than or equal to node's data
		treeInsert(node->_right, data);
}

// treeTraverse
template<typename ValType, typename FDIter>
void treeTraverse(std::shared_ptr<BSTreeNode<ValType>> & node,
				  FDIter & iter)
{
	if (node == nullptr)
		return;

	treeTraverse(node->_left, iter);
	*iter = node->_data;
	iter++;
	treeTraverse(node->_right, iter);
}

// treesort
// Sort a given range using Treesort.
// Pre:
//     ???
// Requirements on Types:
//     ???
// Exception safety guarantee:
//     ???
template<typename FDIter>
void treesort(FDIter first, FDIter last)
{
    // Get the type that FDIter points to
    using ValType = typename std::remove_reference<decltype(*first)>::type;

	// Create Binary Search Tree
	std::shared_ptr<BSTreeNode<ValType>> head = nullptr;
	for (FDIter item = first; item != last; ++item)
		treeInsert(head, *item);

	// Update range
	treeTraverse(head, first);
}


#endif //#ifndef FILE_TREESORT_H_INCLUDED
