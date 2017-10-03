// da3.h 
// Corey S. Gray
// 03 Oct 2017
//
// For CS 311 Fall 2017
// Header for Assignment 3 Functions

#ifndef FILE_DA3_H_INCLUDED
#define FILE_DA3_H_INCLUDED

#include <cstddef>
using std::size_t;
#include <functional>
using std::function;
#include <stdexcept> // std::out_of_range
#include <algorithm> // std::find
#include <iterator>  // std::next and std::advance


// **************************************************************** // *
// Begin DO-NOT-CHANGE section                                      // *
// Do not alter the lines below                                     // *
// **************************************************************** // *
                                                                    // *
                                                                    // *
// struct LLNode                                                    // *
// Linked List node, with client-specified value type               // *
// Intended Invariants (breakable, as data members are public):     // *
//     Either _next is nullptr, or _next points to an LLNode,       // *
//      allocated with new, owned by *this.                         // *
// Requirements on Types:                                           // *
//     ValueType must have a copy ctor and a dctor.                 // *
template <typename ValueType>                                       // *
struct LLNode {                                                     // *
    ValueType _data;  // Data for this node                         // *
    LLNode *  _next;   // Ptr to next node, or nullptr if none      // *
                                                                    // *
    // The following simplify creation & destruction                // *
                                                                    // *
    // 1- & 2-param ctor                                            // *
    // Pre:                                                         // *
    //     theNext, if passed, is either nullptr, or else it        // *
    //      points to an LLNode, allocated with new, with           // *
    //      ownership transferred to *this.                         // *
    // Post:                                                        // *
    //     _data == data.                                           // *
    //     If _next passed, then _next == next. Otherwise, _next    // *
    //      is nullptr.                                             // *
    explicit LLNode(const ValueType & data,                         // *
                    LLNode * next = nullptr)                        // *
        :_data(data),                                               // *
         _next(next)                                                // *
    {}                                                              // *
                                                                    // *
    // dctor                                                        // *
    // Pre: None.                                                   // *
    // Post: None. (_next delete'd)                                 // *
    ~LLNode()                                                       // *
    { delete _next; }                                               // *
};  // End struct LLNode                                            // *
                                                                    // *
                                                                    // *
// **************************************************************** // *
// End DO-NOT-CHANGE section                                        // *
// Do not alter the lines above                                     // *
// **************************************************************** // *

// lookUp
// Searches a linked list for node corresponding to index and returns its _data.
// Preconditions:
//		A valid LLNode object with _next and _data members.
//		index is a nonnegative number.
// Postconditions:
//		Returns _data for the LLNode corresponding to index.
// Requirements on Types:
//		ValueType must have a copy ctor and a dctor.
// Exceptions:
//		lookUp throws std::out_of_range if index is larger than the list's size.
template <typename ValueType>
ValueType lookUp(const LLNode<ValueType> * head,
                 size_t index)
{
	while (true)
	{
		if (head == nullptr)
			throw std::out_of_range("Index out of range.");

		if (index == 0)
			return head->_data;

		head = head->_next;
		--index;
	}

}

// callBetween
// Calls three function objects in order.
// Preconditions:
//		Valid function objects to be called as start(), middle(), and finish().
//		finish() may not throw.
// Postconditions:
//		Functions are called in order.
// Exceptions:
//		callBetween catches and rethrows any errors that start() or middle() throws.
//		if start() throws then middle() and finish() will not be called.
// Implementation in source file.
void callBetween(const function<void()> & start,
                 const function<void()> & middle,
                 const function<void()> & finish);

// uniqueCount
// Searches a specified range and counts the total number of unique values. 
// Preconditions:
//		Two iterators specifying a range of values.
//		first cannot be after last in the range.
// Postconditions:
//		Returns the number of unique values in the given range.
// Restrictions on Types:
//		RAIter must have operator==
template <typename RAIter>
size_t uniqueCount(RAIter first,
                   RAIter last)
{
	size_t uniques = 0;

	while (first != last)
	{
		if (std::find(std::next(first), last, *first) == last)
			++uniques;
		std::advance(first, 1);
	}

	return uniques;
}

// gcd
// Recurses.
// Finds the Greater Common Denominator of two integers.
// Preconditions:
//		Two nonnegative integers.
//		Only one of the integers may be zero.
// Postconditions:
//		Returns the Greatest Common Denominator as an integer.
// Implementation in source file.
int gcd(int a,
        int b);


#endif  //#ifndef FILE_DA3_H_INCLUDED

