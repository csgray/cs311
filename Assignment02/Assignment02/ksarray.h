// ksarray.h
// Corey S. Gray
// 18 Sep 2017

// For CS 311 Fall 2017
// Header for template KSArray
// A "kinda smart" array that knows its size and has copy operations

#ifndef FILE_KSARRAY_H_INCLUDED
#define FILE_KSARRAY_H_INCLUDED

#include <algorithm> // For std::lexicographical_compare

// template KSArray
// Desc
// Invariants
template <typename ValType>
class KSArray {

// ***** KSArray: Constructors, destructor *****
public:

	// Default constructor
	// Pre: None
	// Post
	KSArray() : _size(10), _array(new ValType[_size]) {}

	// 1-parameter constructor
	// Pre: A non-negative integer giving the number of items in the array
	KSArray(int number) : _size(number), _array(new ValType[_size]) {}

	// Destructor
	~KSArray()
	{
		delete[] _array;
	}

	// Copy constructor
	KSArray(const KSArray & other) : _size(other._size), _array(new ValType[_size])
	{
		for (auto i = 0; i != _size; ++i)
			_array[i] = other._array[i];
	}

	// Move constructor
	KSArray(KSArray && other) noexcept : _size(other._size)
	{
		_array = other._array;
		other._size = 0;
		other._array = NULL;
	}

	// Copy assignment operator
	KSArray & operator=(const KSArray & other)
	{
		if (&other != this)
		{
			if (_size != other._size)
			{
				_size = other._size;
				delete[] _array;
				_array = new ValType[_size];
			}
			for (auto i = 0; i != _size; ++i)
				_array[i] = other._array[i];
		}
		return *this;
	}

	// Move assignment operator
	KSArray & operator=(KSArray && other) noexcept
	{
		if (this != &other)
		{
			delete[] _array;
			_size = other._size;
			_array = other._array;
			other._size = 0;
			other._array = NULL;
		}
		return *this;
	}

// ***** KSArray: Member types *****
public:
	using value_type = ValType;
	using size_type = size_t;

// ***** KSArray: Data members *****
private:
	size_type _size;
	value_type * _array;

	// ***** KSArray: General public operators *****
public:

	// operator[]
	// Pre: An integer from 0 to size-1 where size is the number of items in the array
	// Post: Returns a reference to the proper item
	value_type & operator[](const size_type i)
	{
		return _array[i];
	}

	const value_type & operator[](const size_type i) const
	{
		return _array[i];
	}

	// ***** KSArray: General public member functions *****
public:

	// size
	// Pre: None
	// Post: Returns the number of items in the array
	size_type size() const
	{
		return _size;
	}

	// begin
	// Pre: None
	// Post: Returns the address of item 0 in the array
	value_type * begin()
	{
		return _array;
	}

	const value_type * begin() const
	{
		return _array;
	}

	// end
	// Pre: None
	// Post: Returns the address of the item one-past the end of the array
	value_type * end()
	{
		return _array + _size;
	}

	const value_type * end() const
	{
		return _array + _size;
	}

};

// ***** class KSArray - Declaration of associated global operators *****

// equality (==)
// Checks whether two KSArrays with the same value_type have the same size and
// if all corresponding items are equal
// Pre: Two objects of class KSArray with same value_type
// Post:
//		Returns a boolean.
//		True if both size and corresponding items are equal. False otherwise.
template <typename value_type>
bool operator==(const KSArray<value_type> & lhs, const KSArray<value_type> & rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	for (auto i = 0; i != lhs.size(); ++i)
	{
		if (lhs[i] != rhs[i])
			return false;
	}
	return true;
}

// inequality (!=)
// Checks whether two KSarrays with the same value_type do not have the same
// size and/or not all corresponding items are equal
// Pre: Two objects of class KSArray with the same value_type
// Post:
//		Returns a boolean.
//		True if either size or corresponding items are different. False otherwise.
template <typename value_type>
bool operator!=(const KSArray<value_type> & lhs, const KSArray<value_type> & rhs)
{
	return !(lhs == rhs);
}

// less than (<)
template <typename ValType>
bool operator<(const KSArray<ValType> & lhs, const KSArray<ValType> & rhs)
{
	return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

// less than or equal (<=)
template <typename ValType>
bool operator<=(const KSArray<ValType> & lhs, const KSArray<ValType> & rhs)
{
	return (lhs < rhs || lhs == rhs);
}

// greater than (>)
template <typename ValType>
bool operator>(const KSArray<ValType> & lhs, const KSArray<ValType> & rhs)
{
	return !(lhs < rhs || lhs == rhs);
}

// greater than or equal (>=)
template <typename ValType>
bool operator>=(const KSArray<ValType> & lhs, const KSArray<ValType> & rhs)
{
	return !(lhs < rhs);
}

#endif //#ifndef FILE_KSARRAY_H_INCLUDED