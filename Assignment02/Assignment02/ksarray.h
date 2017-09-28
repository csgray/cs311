// ksarray.h
// Corey S. Gray
// 18 Sep 2017

// For CS 311 Fall 2017
// Header for template KSArray
// A "kinda smart" array

#ifndef FILE_KSARRAY_H_INCLUDED
#define FILE_KSARRAY_H_INCLUDED

#include <algorithm> // For std::lexicographical_compare and std::swap

// template KSArray
// Array of ValType with size, Big Five, comparison operators, bracket operator, begin, end
// Invariants: _size >= 0
// Requirements on Types: ValType must have operator!= and operator<
template <typename ValType>
class KSArray {

// ***** KSArray: Constructors, destructor *****
public:

	// Default constructor
	// Pre: None
	// Post: KSArray with 10 items of type ValType
	KSArray() : _size(10), _array(new value_type[_size]) {}

	// 1-parameter constructor
	// Pre: A non-negative integer giving the number of items in the array
	// Post: KSArray with specificed number of items of type ValType
	KSArray(int number) : _size(number), _array(new value_type[_size]) {}

	// Destructor
	~KSArray()
	{
		delete[] _array;
	}

	// Copy constructor
	// Pre: Valid KSArray object
	// Post: Another KSArray object with same _size and _array as the first
	KSArray(const KSArray & other) : _size(other.size()), _array(new value_type[size()])
	{
		for (auto i = 0; i != size(); ++i)
			_array[i] = other._array[i];
	}

	// Move constructor
	// Pre: Valid KSArray object
	// Post:
	//		New KSArray object with same _size and _array as the first
	//		Old KSArray object's size set to 0 and _array set to NULL
	KSArray(KSArray && other) noexcept : _size(other._size), _array(other._array)
	{
		other._size = 0;
		other._array = NULL;
	}

	// Copy assignment operator
	// Pre: Valid KSArray object
	// Post:
	//		Return is a KSArray with the same _size and _array same as the other KSArray
	//		Other KSArray is unchanged
	KSArray & operator=(const KSArray & other)
	{
		KSArray copy(other);
		mswap(copy);
		return *this;
	}

	// Move assignment operator
	// Pre: Valid KSArray object
	// Post:
	//		Return is a KSArray with the _size and _array of the other KSArray
	//		Other KSArray now has this KSArray's old values
	KSArray & operator=(KSArray && other) noexcept
	{
		mswap(other);
		return *this;
	}

// ***** KSArray: Member types *****
public:
	using value_type = ValType;
	using size_type = size_t;

// ***** KSArray: Data members *****
private:
	size_type _size; // Number of items in the array
	value_type * _array; // Pointer to first item in the array

// ***** KSArray: Private functions ****
private:
	// mswap
	// Pre: Two valid KSArray objects
	// Post:
	//		The _size and _array of the first KSArray are those of the second
	//		The _size and _array of the second KSArray are those of the first
	void mswap(KSArray & other) noexcept
	{
		std::swap(_size, other._size);
		std::swap(_array, other._array);
	}

// ***** KSArray: General public operators *****
public:

	// operator[]
	// Pre: An integer from 0 to size-1 where size is the number of items in the array
	// Post: Returns a modifiable reference to the proper item
	value_type & operator[](const size_type i)
	{
		return _array[i];
	}

	// operator[] const
	// Pre: An integer from 0 to size-1 where size is the number of items in the array
	// Post: Returns a not-modifiable reference to the proper item
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

	// begin const
	// Pre: None
	// Post:
	//		Returns the address of item 0 in the array
	//		Does not allow modification of the item
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

	// end const
	// Pre: None
	// Post:
	//		Returns the address of the item one-past the end of the array
	//		Does not allow modification of the item
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
// Requirements on Types: ValType must have operator !=
template <typename ValType>
bool operator==(const KSArray<ValType> & lhs, const KSArray<ValType> & rhs)
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
// Checks whether two KSArrays with the same value_type do not have the same
// size and/or not all corresponding items are equal
// Pre: Two objects of class KSArray with the same value_type
// Post:
//		Returns a boolean.
//		True if either size or corresponding items are different
//		False otherwise
// Requirements on Types: ValType must have operator!=
template <typename ValType>
bool operator!=(const KSArray<ValType> & lhs, const KSArray<ValType> & rhs)
{
	return !(lhs == rhs);
}

// less than (<)
// Checks if the first KSArray has a lower lexicographical value than the second
// Pre: Two objects of class KSArray with the same value_type
// Post:
//		Returns a boolean
//		True if the first KSArray has a lower lexicographical value than the second
//		False otherwise
// Requirements on Types: ValType must have operator<
template <typename ValType>
bool operator<(const KSArray<ValType> & lhs, const KSArray<ValType> & rhs)
{
	return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

// less than or equal (<=)
// Checks if the first KSArray has a lower or equal lexicographical value as compared to the second
// Pre: Two objects of class KSArray with the same value_type
// Post:
//		Returns a boolean
//		True if the first KSArray has a lower lexicographical value than the second
//		True if the two KSArrays are equal
//		False otherwise
// Requirements on Types: ValType must have operator<
template <typename ValType>
bool operator<=(const KSArray<ValType> & lhs, const KSArray<ValType> & rhs)
{
	return (lhs < rhs || lhs == rhs);
}

// greater than (>)
// Checks if the first KSArray has a higher lexicographical value than the second
// Pre: Two objects of class KSArray with the same value_type
// Post:
//		Returns a boolean
//		True if the first KSArray has a higher lexicographical value than the second
//		False otherwise
// Requirements on Types: ValType must have operator<
template <typename ValType>
bool operator>(const KSArray<ValType> & lhs, const KSArray<ValType> & rhs)
{
	return !(lhs < rhs || lhs == rhs);
}

// greater than or equal (>=)
// Checks if the first KSArray has a higher or equal lexicographical value as compared to the second
// Pre: Two objects of class KSArray with the same value_type
// Post:
//		Returns a boolean
//		True if the first KSArray has a higher lexicographical value than the second
//		True if the two KSArrays are equal
//		False otherwise
// Requirements on Types: ValType must have operator<
template <typename ValType>
bool operator>=(const KSArray<ValType> & lhs, const KSArray<ValType> & rhs)
{
	return !(lhs < rhs);
}

#endif //#ifndef FILE_KSARRAY_H_INCLUDED