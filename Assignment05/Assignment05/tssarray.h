// tsarray.h
// Corey S. Gray
// 02 Nov 2017
//
// For CS 311 Fall 2017
// Header for Assignment 5: Templated Stunningly Smart Array Class
// Building from ssarray.h by Dr. Glenn G. Chappell

#ifndef FILE_TSSARRAY_H_INCLUDED
#define FILE_TSSARRAY_H_INCLUDED

#include <cstddef>	 // For std::size_t
#include <algorithm> // For std::copy, std::max, std::rotate, std::swap

// ****************************************************************************
// class TSSArray - Class Definition
// ****************************************************************************

// class TSSArray
// Templated Stunningly Smart Array of ValType.
// Resizable, copyable, movable, and exception-safe.
// Invariants:
//		0 <= size <= _capacity
//		_data points to an array of ValType, owned by *this, holding _capacity ValType
//		Exception: _data may be NULL if _capacity == 0 
// Requirements on Types: None
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
	static const size_type DEFAULT_CAP = 8;

// ***** TSSArray: Constructors, Destructors, and Assignment Operators *****
public:

	// Default constructor and constructor from size
	// Pre: size >= 0
	// Exception neutral, does not throw any additional exceptions
	// Strong Guarantee
	explicit TSSArray(size_type size = size_type(0))
		:_capacity(std::max(size, DEFAULT_CAP)), // _capacity must be declared before _data
		 _size(size),
		 _data(new value_type[_capacity])
	{}

	// Copy constructor
	// Pre: A valid TSSArray object
	// Exception neutral, does not throw any additional exceptions
	// Strong Guarantee
	TSSArray(const TSSArray & other)
		:_capacity(other._capacity),
		 _size(other._size),
		 _data(new value_type[_capacity])
	{
		try
		{
			std::copy(other.begin(), other.end(), begin());
		}
		catch (...)
		{
			this->~TSSArray();
			throw;
		}
	}

	// Move constructor
	// Pre: A valid TSSArray object
	// No-Throw Guarantee
	TSSArray(TSSArray && other) noexcept
		:_capacity(other._capacity),
		 _size(other._size),
		 _data(other._data)
	{
		other._size = 0;
		other._data = NULL;
	}

	// Destructor
	// No-Throw Guarantee
	~TSSArray()
	{
		delete[] _data;
	}

	// Copy assignment operator
	// Pre: A valid TSSArray objects
	// Exception neutral, does not throw any additional exceptions
	// Strong Guarantee
	TSSArray & operator=(const TSSArray & rhs)
	{
		TSSArray copyobject(rhs);
		swap(copyobject);
		return *this;
	}

	// Move assignment operator
	// Pre: Valid TSSAray object
	// No-Throw Guarantee
	TSSArray & operator=(TSSArray && rhs) noexcept
	{
		swap(rhs);
		return *this;
	}

// ***** TSSArray: General Public Operators *****
public:

	// operator[] - non-const and const
	// Pre: 0 <= index <= _size - 1
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
	// No-Throw Guarantee
	bool empty() const
	{
		return size() == size_type(0);
	}

	// resize
	// Pre:  newsize >= 0
	// Exception neutral, does not throw any additional exceptions
	// Strong Guarantee
	void resize(size_type newsize)
	{
		if (newsize > _capacity)
		{
			_capacity = std::max(2 * _capacity, newsize);
			value_type * temp = new value_type[_capacity];
			try
			{
				std::copy(begin(), end(), temp);
			}
			catch (...)
			{
				delete[] temp;
				throw;
			}
			delete[] _data;
			_data = temp;
		}
		_size = newsize;
	}

	// insert
	// Pre: begin() <= pos <= end()
	// Exception neutral, does not throw any additional exceptions
	// Strong Guarantee
	iterator insert(iterator pos,
					const value_type & item)
	{
		size_type index = pos - begin();
		resize(_size + 1);
		_data[_size - 1] = item;
		iterator newpos = begin() + index;
		try
		{
			std::rotate(newpos, begin() + _size - 1, end());
		}
		catch (...)
		{
			resize(_size - 1);
			throw;
		}
		return newpos;
	}

	// erase
	// Pre: begin() <= pos <= end()
	// Exception neutral, does not throw any additional exceptions
	// Strong Guarantee
	iterator erase(iterator pos)
	{
		std::rotate(pos, pos + 1, end());
		resize(_size - 1);
		return pos;
	}

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
	// Exception neutral, does not throw any additional exceptions
	// Strong Guarantee
	void push_back(const value_type & item)
	{
		insert(end(), item);
	}

	// pop_back
	// RemoveEnd operation.
	// Pre: _size > 0.
	// Exception neutral, does not throw any additional exceptions
	// Strong Guarantee
	void pop_back()
	{
		erase(end() - 1);
	}

	// swap
	// Pre: Two valid TSSArray objects
	// No-Throw Guarantee
	void swap(TSSArray & other) noexcept
	{
		std::swap(_capacity, other._capacity);
		std::swap(_size, other._size);
		std::swap(_data, other._data);
	}

// ***** TSSArray: Data Members *****
private:

	size_type	 _capacity; // Size of the allocated array
	size_type	 _size;		// Size of client's data
	value_type * _data;		// Pointer to the array

}; // End templated class TSSArray

#endif // #ifndef FILE_TSSARRAY_H_INCLUDED
