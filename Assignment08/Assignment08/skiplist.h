// skiplist.h 
// Corey S. Gray
// 07 Dec 2017
//
// For CS 311 Fall 2017
// Header for class SkipList
// There is no associated source file.

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
	// find
	// Returns a const pointer to the bottom element containing the item
	const std::shared_ptr<SkipListNode> find(int value)
	{
		std::shared_ptr<SkipListNode> node = _head;
		while (true)
		{
			if (node->_value == value && !(node->_down))	// Bottom element with value
				return node;
			
			if (node->_right->_value > value && !(node->_down))
				break;

			while (value >= node->_right->_value)			// Move right so long as value is larger than right value
				node = node->_right;

			if (node->_down)
				node = node->_down;
		}
				
		return nullptr;
	}

	// insert
	// Adds the value to the skip list
	void insert(int value)
	{
		if (value == _head->_value || value == _tail->_value)
			return;
		std::shared_ptr<SkipListNode> leftnode = _head;
		std::shared_ptr<SkipListNode> rightnode = _head->_right;
		while (value >= rightnode->_value || leftnode->_down)
		{
			while (value >= rightnode->_value)	// Move right until value < rightnode->_value
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
	//	int coin = coinFlip();
	//	while (coin == 1)
	//	{
	//		addUpNode(node);
	//		node = node->_up;
	//		coin = coinFlip();
	//	}
	}

	// print
	// Prints each element in the list
	void print()
	{
		std::shared_ptr<SkipListNode> node = _head;
		while (node->_down)		// Reach bottom of the list
			node=node->_down;
		node = node->_right;	// Don't print _head;
		while (node->_value != _tail->_value)
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

	// addUpNode
	// Adds a node above the passed node and links it to its neighbors at that level
	void addUpNode(std::shared_ptr<SkipListNode> node)
	{
		// Find the closest node to the left at the new height
		std::shared_ptr<SkipListNode> leftnode = node->_left;
		while (!(leftnode->_up) && leftnode->_left)	// move further left until leftnode has an upnode
			leftnode = leftnode->_left; 
		if (leftnode == _head)						// Increase the height of the entire list
		{
			_head->_up = std::make_shared<SkipListNode>(_head->_value, nullptr, _head, nullptr, nullptr);
			_tail->_up = std::make_shared<SkipListNode>(_tail->_value, nullptr, _tail, nullptr, nullptr);
			_head = _head->_up;
			_tail = _tail->_up;
			node->_up = std::make_shared<SkipListNode>(node->_value, nullptr, node, _head, _tail);
			_head->_right = node->_up;
			_tail->_left = node->_up;
			_height++;
			return;
		}
		leftnode = leftnode->_up;					// the new node's leftnode needs to be up a level
		// Find the closest node to the right at the new height
		std::shared_ptr<SkipListNode> rightnode = node->_right;
		while (!(rightnode->_up) && rightnode->_right)
			rightnode = rightnode->_right;
		rightnode = rightnode->_up;

		node->_up = std::make_shared<SkipListNode>(node->_value, nullptr, node, leftnode, rightnode);
		leftnode->_right = node->_up;
		rightnode->_left = node->_up;
		return;
	}
};

#endif // #ifndef FILE_SKIPLIST_H_INCLUDED