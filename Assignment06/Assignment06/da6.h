// da6.h
// Corey S. Gray
// 10 Nov 2017
//
// For CS 311 Fall 2017
// Header for Assignment 6: Linked List Exercises

#ifndef FILE_DA6_H_INCLUDED
#define FILE_DA6_H_INCLUDED

#include <memory>		// For std::shared_ptr
#include <cstddef>		// For std::size_t
#include <utility>		// For std::pair, std::make_pair
#include <functional>	// For std::function

#include "llnode2.h"	// Provided Linked List node

// reverseList
// Reverses the order of a given Linked List.
// Pre: A shared pointer to a Linked List.
// No-Throw Guarantee
template <typename ValType>
void reverseList(std::shared_ptr<LLNode2<ValType>> & head)
{
	std::shared_ptr<LLNode2<ValType>> newHead(nullptr);
	std::shared_ptr<LLNode2<ValType>> oldHead(nullptr);

	while (head != nullptr)
	{
		oldHead = head->_next;
		
		head->_next = newHead;
		newHead = head;
		head = oldHead;
	}

	head = newHead;
};

// class LLMap
// Uses a Linked List to hold an associated dataset.
// Invariants:
//		_head is a shared_ptr to the start of a Linked List or is nullptr
// Requirements on Types:
//		KeyType must have a copy constructor (for std::make_pair) and a destructor
//		DataType must have a copy constructor (for std::make_pair) and a destructor 
template <typename KeyType, typename DataType>
class LLMap {

// ***** LLMap: Types *****
public:
	// key_type: type of key items (first half of pair)
	using key_type = KeyType;

	// data_type: type of data items (second half of pair)
	using data_type = DataType;

// ***** LLMap: Constructors, Destructors, and Assignment Operators *****
public:

	// Default constructor
	// Creates an empty dataset
	// Pre: None
	// Exception neutral, does not throw any additional exceptions
	// Strong Guarantee
	LLMap()
		:_head(nullptr)
	{}

	// Copy constructor
	// Not allowed
	LLMap(const LLMap & other) = delete;

	// Move constructor
	// Not allowed
	LLMap(LLMap && other) = delete;

	// Destructor
	// Loops through the Linked List calling reset() on each node.
	// Otherwise long lists may overflow the stack with recursive destructor calls.
	// No Throw Guarantee
	~LLMap()
	{
		while (_head)
		{
			auto temp = _head->_next;	// Preserves address of next node
			_head.reset();
			_head = temp;
		}
	}

	// Copy assignment operator
	// Not allowed
	LLMap & operator=(const LLMap & rhs) = delete;

	// Move assignment operator
	// Not allowed
	LLMap & operator=(const LLMap && rhs) = delete;

// ***** LLMap: General Public Functions *****
public:
	// size
	// Returns an unsigned integer of an appropriate type giving the number of key-value pairs in the dataset.
	// Pre: A nullptr-terminaed LLMap object
	// No Throw Guarantee
	std::size_t size() const
	{
		size_t size = 0;
		
		auto temp = _head;
		while (search)
		{
			++size;
			temp = temp->_next;
		}

		return size;
	}

	// empty
	// Returns a bool indicating whether there are no key-value pairs in the dataset.
	// Pre: A LLMap object
	// No Throw Guarantee
	bool empty() const
	{
		return isEmpty(_head);
	}

	// find
	// Returns const data_type * for a const LLMap and data_type * for a non-const LLMap.
	// If the key lies in the dataset, the returned pointer points to the associated value.
	// Otherwise, the returned pointer is nullptr.
	// Pre: A nullptr-terminated LLMap object
	// No Throw Guarantee
	const data_type * find(key_type key) const
	{
		auto search = _head;

		while (search)
		{
			if (search->_data.first == key)
				return &(search->_data.second);

			search = search->_next;
		}

		return nullptr;
	}

	data_type * find(key_type key)
	{
		auto search = _head;
		while (search)
		{
			if (search->_data.first == key)
				return &(search->_data.second);

			search = search->_next;
		}

		return nullptr;
	}

	// insert
	// Inserts the key-value pair if the key is not already in the dataset.
	// Replaces an existing key-value pair with that given.
	// Pre:	A nullptr-terminated LLMap object
	// Exception neutral.
	//		Throws what and when key_type or data_type constructors throw.
	// Strong Guarantee
	void insert(key_type key, data_type value)
	{
		auto result = find(key);
		if (result)
		{
			*result = value;
			return;
		}
		
		push_front(_head, std::make_pair(key, value));
	}

	// erase
	// Removes a key-value pair if the key lies in the dataset.
	// Otherwise it does nothing.
	// Pre: A nullptr-terminated LLMap
	// No Throw Guarantee
	void erase(key_type key)
	{
		if (_head->_data.first == key)
		{
			_head = _head->_next;
			return;
		}
		
		auto prevItem = _head;
		auto search = _head->_next;
		while (search)
		{
			if (search->_data.first == key)
			{
				prevItem->_next = search->_next;
				return;
			}
			
			prevItem = search;
			search = search->_next;
		}
	}

	// traverse
	// Calls the passed function on each key-value pair in the dataset.
	// Pre: func takes two parameters and returns nothing.
	// Exception neutral.
	//		Throws what and when func throws.
	// Basic guarantee.
	//		Modified values remain changed if traverse throws on latter values.
	void traverse(std::function<void (key_type, data_type)> func)
	{
		auto search = _head;
		while (search)
		{
			func(search->_data.first, search->_data.second);
			search = search->_next;
		}
	}

// ***** LLMap: Data Members *****
private:
	std::shared_ptr<LLNode2<std::pair<key_type, data_type>>> _head;
};

#endif // #ifndef FILE_DA6_H_INCLUDED
