// tsarray.h
// Corey S. Gray
// 02 Nov 2017
//
// For CS 311 Fall 2017
// Header for Assignment 5: Templated Stunningly Smart Array Class
// Building from ssarray.h by Dr. Glenn G. Chappell

#ifndef FILE_TSSARRAY_H_INCLUDED
#define FILE_TSSARRAY_H_INCLUDED

#include <cstddef> // For std::size_t
#include <algorithm> // For std::max

// ****************************************************************************
// class TSSArray - Class Definition
// ****************************************************************************

// class TSSArray
// Templated Stunningly Smart Array of ValType.
// Resizable, copyable, movable, and exception-safe.
// Invariants:
template <typename ValType>
class TSSArray {

// ***** TSSArray: Types *****
public:
	// value_type: type of data tiems
	using value_type = ValType;
	
	// size_type: type of sizes and indices
	using size_type = std::size_t;

	// iterator, const-iterator: random-access iterator types
	using iterator = value_type *;
	using const_iterator = const value_type *;

// ***** TSSArray: Internal-use constants *****
private:
	// Capacity of default-constructed object
	static const size_type DEFAULT_CAP;

// ***** TSSArray: Constructors, Destructors, and Assignment Operators *****
public:

	// Default constructor and constructor from size
	// Strong Guarantee
	explicit TSSArray(size_type size = size_type(0))
		:_capacity(std::max(size, DEFAULT_CAP)), // _capacity must be declared before _data
		 _size(size),
		 _data(new value_type[_capacity])
	{}

	// Copy constructor
	// Strong Guarantee
	TSSArray(const TSSArray & other);

	// Move constructor
	// No-Throw Guarantee
	TSSArray(TSSArray && other) noexcept;

	// Destructor
	// No-Throw Guarantee
	~TSSArray()
	{
		delete[] _data;
	}

	// Copy assignment operator
	TSSArray & operator=(const TSSArray & rhs);

	// Move assignment operator
	// No-Throw Guarantee
	TSSArray & operator=(TSSArray && rhs) noexcept;

// ***** TSSArray: General Public Operators *****
public:

	// Operator[] - non-const and const
	// No-Throw Guarantee
	value_type & operator[](size_type index)
	{
		return _data[index];
	}
	const value_type & operator[](size_type index) const
	{
		return _data[index];
	}

// ***** TSSArray: General Public Functions *****
public:

	// size
	// No-Throw Guarantee
	size_type size() const
	{
		return _size;
	}

	// empty
	// No-Throe Guarantee
	bool empty() const
	{
		return size() == size_type(0);
	}

	// resize
	void resize(size_type newsize);

	// insert
	iterator insert(iterator pos,
					const value_type & item);

	// erase
	iterator erase(iterator pos);

	// begin - non-const & const
	// No-Throw Guarantee
	iterator begin()
	{
		return _data;
	}
	const_iterator begin() const
	{
		return _data;
	}

	// end - non-const & const
	// No-Throw Guarantee
	iterator end()
	{
		return begin() + size();
	}
	const_iterator end() const
	{
		return begin() + size();
	}

	// push_back
	// InsertEnd operation.
	void push_back(const value_type & item)
	{
		insert(end(), item);
	}

	// pop_back
	// RemoveEnd operation.
	// Precondition:
	//		_size > 0.
	void pop_back()
	{
		erase(end() - 1);
	}

	// swap
	// No-Throw Guarantee
	void swap(TSSArray & other) noexcept;

// ***** TSSArray: Data Members *****
private:

	size_type	 _capacity; // Size of the allocated array
	size_type	 _size;		// Size of client's data
	value_type * _data;		// Pointer to the array

}; // End templated class TSSArray

#endif // #ifndef FILE_TSSARRAY_H_INCLUDED
