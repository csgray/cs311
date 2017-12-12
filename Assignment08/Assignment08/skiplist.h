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

#include <memory>	// for std::shared_ptr, std::make_shared
#include <limits>	// for std::numeric_limits
#include <random>	// for std::minstd_rand
#include <iostream>		// for std::cout

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
	explicit SkipListNode(int value,
		std::shared_ptr<SkipListNode> up = nullptr,
		std::shared_ptr<SkipListNode> down = nullptr,
		std::shared_ptr<SkipListNode> left = nullptr,
		std::shared_ptr<SkipListNode> right = nullptr)
		: _value(value)
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
//		_height >= 2;
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
	}

	// Destructor
	~SkipList() = default;

// ***** Public Member Functions ****
public:
	// insert
	// Adds the value to the skip list
	void insert(int value)
	{
		if (value == _head->_value || value == _tail->_value)
			return;
		std::shared_ptr<SkipListNode> leftnode = _head;
		std::shared_ptr<SkipListNode> rightnode = _head->_right;
		while (value > rightnode->_value || leftnode->_down)
		{
			while (value > rightnode->_value)	// Move right until value < rightnode->_value
			{
				leftnode = rightnode;
				rightnode = leftnode->_right;
			}

			if (leftnode->_down)				// Move down if possible then try again
				leftnode = leftnode->_down;
		}
		std::shared_ptr<SkipListNode> node = std::make_shared<SkipListNode>(value, nullptr, nullptr, leftnode, leftnode->_right);
		leftnode->_right = node;
		rightnode->_left = node;
		
		// Randomly add another level to the newly inserted value
		//int coin = coinFlip();
		//while (coin == 1)
		//{
		//	addUpNode(node);
		//	node = node->_up;
		//	coin = coinFlip();
		//}
	}

	// print
	// Prints each element in the list
	void print()
	{
		std::shared_ptr<SkipListNode> node = _head;
		while (node->_down)		// Reach bottom of the list
			node=node->_down;
		while (node)
		{
			std::cout << "Address: " << node << std::endl
					  << "Value:   " << node->_value << std::endl
					  << "Up:      " << node->_up << std::endl
					  << "Down:    " << node->_down << std::endl
					  << "Left:    " << node->_left << std::endl
					  << "Right:   " << node->_right << std::endl << std::endl;
			node = node->_right;
		}
	}

// ***** Private Member Functions *****
private:
	// coinFlip
	// Generates a random number between 0 and 1 to determine if we add a level
	int coinFlip()
	{
		std::random_device seed;
		std::minstd_rand generator(seed());
		std::uniform_int_distribution<int> coin(0, 1);
		int coinflip = coin(generator);
		return coinflip;
	}

	// increaseHeight
	// Adds a node above _
	void increaseHeight()
	{
		_head->_up = std::make_shared<SkipListNode>(_head->_value, nullptr, _head, nullptr, nullptr);
		_tail->_up = std::make_shared<SkipListNode>(_tail->_value, nullptr, _tail, _head->_up, nullptr);
		_head = _head->_up;
		_tail = _tail->_up;
		_head->_right = _tail;
		_height++;
	}

	// addUpNode
	// Adds a node above the passed node and links it to its neighbors at that level
	//void addUpNode(std::shared_ptr<SkipListNode> node)
	//{
		// Find the closest node to the left at the new height
	//	std::shared_ptr<SkipListNode> leftnode = node->_left;
	//	while ((leftnode->_up) && leftnode->_left)	// move further left until leftnode has an upnode
	//		leftnode = leftnode->_left; 
	//	leftnode = leftnode->_up;					// the new node's leftnode needs to be up a level
	//	if (leftnode == _head)
	//		increaseHeight();			
		// Find the closest node to the right at the new height
	//	std::shared_ptr<SkipListNode> rightnode = node->_right;
	//	while (!(rightnode->_up) && rightnode->_right)
	//		rightnode = rightnode->_right;
	//	rightnode = rightnode->_up;

	//	node->_up = std::make_shared<SkipListNode>(node->_value, nullptr, node, leftnode, rightnode);		
	//}
};

#endif // #ifndef FILE_SKIPLIST_H_INCLUDED