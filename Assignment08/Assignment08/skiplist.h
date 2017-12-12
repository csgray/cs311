// skiplist.h 
// Corey S. Gray
// 07 Dec 2017
//
// For CS 311 Fall 2017
// Header for function template treesort
// There is no associated source file.
//
// I found this blog post especially helpful while writing this:
// https://partiallattice.wordpress.com/2013/04/16/testing-c-skip-lists/

#ifndef FILE_SKIPLIST_H_INCLUDED
#define FILE_SKIPLIST_H_INCLUDED

#include <memory> // for std::shared_ptr, std::make_shared
#include <limits> // for std::numeric_limits

// struct SkipListNode
// Skip List int node. SkipListNode objects should be created with std::make_shared and owned by a std::shared_ptr.
// An empty list consists of the head and tail nodes with nothing between them.
//
// Invariants:
//		_data == data
//		_up == up or nullptr (if top of column)
//		_down == down or nullptr (if bottom of column)
//		_left == left or nullptr (if in head column)
//		_right == right or nullptr (if in tail column)
struct SkipListNode {
	int _value;
	std::shared_ptr<SkipListNode> _up;
	std::shared_ptr<SkipListNode> _down;
	std::shared_ptr<SkipListNode> _left;
	std::shared_ptr<SkipListNode> _right;

	// Parameterized Constructor
	// Creates an unlinked SkipListNode (which isn't that useful),
	// unless neighboring nodes are passed as additional parameters.
	//
	// Preconditions:
	//		data is not empty
	// Postconditions:
	//		_data == data
	//		_up == up if passed, otherwise nullptr
	//		_down == down if passed, otherwise nullptr
	//		_left == left if passed, otherwise nullptr
	//		_right == right if passed, otherwise nullptr
	// Exceptions:
	//		
	// Strong Guarantee, Exception Neutral
	explicit SkipListNode(int data,
		std::shared_ptr<SkipListNode> up = nullptr,
		std::shared_ptr<SkipListNode> down = nullptr,
		std::shared_ptr<SkipListNode> left = nullptr,
		std::shared_ptr<SkipListNode> right = nullptr)
		: _value(data)
		, _up(up)
		, _down(down)
		, _left(left)
		, _right(right)
	{}

	// Destructor
	~SkipListNode() = default;
};

// class SkipList
// Uses a SkipList to hold a sorted dataset.
// Invariants:
//		_height >= 1;
//		_head is a shared_ptr to a SkipListNode of "negative infinity"
//		_tail is a shared_ptr to a SkipListNode of "positive infinity"
class SkipList {
// ***** SkipList: Data Members *****
public:
	int _height = 1;
	std::shared_ptr<SkipListNode> _head;
	std::shared_ptr<SkipListNode> _tail;

	// ***** SkipList: Constructors and Destructors *****
public:
	// Default Constructor
	// Creates an empty list bracketed by the _head and _tail nodes
	// _head is the int equivalent of negativity infinity
	// _tail is the int equivalent of infinity
	// Pre: None
	SkipList()
	{
		// _head and _tail are as close to negative infinity and infinity as possible
		_head = std::make_shared<SkipListNode>(std::numeric_limits<int>::min()); 
		_tail = std::make_shared<SkipListNode>(std::numeric_limits<int>::max(), nullptr, nullptr, _head, nullptr);
		_head->_right = _tail;	// _head and _tail are linked

		// increase _head and _tail by one level
		_head = std::make_shared<SkipListNode>(_head->_value, nullptr, _head, nullptr, nullptr);
		_tail = std::make_shared<SkipListNode>(_tail->_value, nullptr, _tail, _head, nullptr);
		_head->_right = _tail;	// new _head and _tail are linked
		_height++;
	}

	// Destructor
	~SkipList() = default;

// ***** Node Functions *****
private:
	// raiseLevel
	// Adds a node above the passed node and links it to its neighbors at that level
	void raiseLevel(std::shared_ptr<SkipListNode> node)
	{
		// Find the closest node to the left at the new height
		std::shared_ptr<SkipListNode> leftnode = node->_left;
		while (!(leftnode->_up) && leftnode->_left)
			leftnode = leftnode->_left;
		if (leftnode->_up)
			leftnode = leftnode->_up;
		// Find the closest node to the right at the new height
		std::shared_ptr<SkipListNode> rightnode = node->_right;
		while (!(rightnode->_up) && rightnode->_left) 
			rightnode = rightnode->_left;
		if (rightnode->_up)
			rightnode = rightnode->_up;

		node->_up = std::make_shared<SkipListNode>(node->_value, nullptr, node, leftnode, rightnode);		
	}
};

#endif // #ifndef FILE_SKIPLIST_H_INCLUDED