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
#include <utility>		// For std::pair

#include "llnode2.h"	// Provided Linked List node

// reverseList
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
	LLMap()
		:_node(nullptr)
	{}

	// Copy constructor
	LLMap(const LLMap & other) = delete;

	// Move constructor
	LLMap(LLMap && other) = delete;

	// Destructor
	~LLMap()
	{}

	// Copy assignment operator
	LLMap & operator=(const LLMap & rhs) = delete;

	// Move assignment operator
	LLMap & operator=(const LLMap && rhs) = delete;

// ***** LLMap: General Public Functions *****
public:
	// size
	// Returns an integer of an appropriate type giving the number of key-value pairs in the dataset.
	std::size_t size() const
	{
		return 0;
	}

	// empty
	// Returns a bool indicating whether there are no key-value pairs in the dataset.
	bool empty() const
	{
		return false;
	}

	// find
	// Returns const data_type * for a const LLMap and data_type * for a non-const LLMap.
	// If the key lies in the dataset, the returned pointer points to the associated value.
	// Otherwise, the returned pointer is nullptr.
	const data_type * find(key_type key) const
	{
		std::shared_ptr<LLNode2<std::pair<key_type, data_type>>> search(_head);

		while (search != nullptr)
		{
			if (search->_data.first == key)
			{
				const data_type * result = search->_data.second;
				return result;
			}
			search = search->_next;
		}

		return nullptr;
	}

	data_type * find(key_type key)
	{
		std::shared_ptr<LLNode2<std::pair<key_type, data_type>>> search(_head);

		while (search != nullptr)
		{
			if (search->_data.first == key)
			{
				data_type * result = search->_data.second;
				return result;
			}

			search = search->_next;
		}

		return nullptr;
	}

	// insert
	// Inserts the key-value pair if the key is not already in the dataset.
	// Replaces an existing key-value pair with that given.
	void insert(key_type key, data_type value)
	{
		std::pair<key_type, data_type> item = std::make_pair(key, value);
		LLNode2<std::pair<key_type, data_type>> node(item);
		node._next = _head;
		_head = std::make_shared<LLNode2<std::pair<key_type, data_type>>> item;

		return;
	}

	// erase
	// Removes a key-value pair if the key lies in the dataset.
	// Otherwise it does nothing.
	void erase(key_type key)
	{
		return;
	}

	// traverse
	// Takes another function with the following requirements:
	//		Two parameters: key and value
	//		Returns nothing.
	// Calls the passed function on each key-value pair in the dataset.
	template <typename F>
	void traverse(F func)
	{
		return;
	}

// ***** LLMap: Data Members *****
private:
	std::shared_ptr<LLNode2<std::pair<key_type, data_type>>> _head;
};

#endif // #ifndef FILE_DA6_H_INCLUDED
