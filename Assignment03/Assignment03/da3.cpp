// da3.cpp
// Corey S. Gray
// 03 Oct 2017
//
// For CS 311 Fall 2017
// Source for Assignment 3 Functions

#include "da3.h"       // For Assignment 3 prototypes & templates
#include <functional>
using std::function;

// callBetween
// Documentation in header file
void callBetween(const function<void()> & start,
                 const function<void()> & middle,
                 const function<void()> & finish)
{
	try {
		start();
	}
	catch (...) {
		throw; // middle() and finish() are not called if start() throws
	};

	try {
		middle();
	}
	catch (...) {
		finish(); // finish() MUST be called after middle() no matter what
		throw;
	};

	finish();
}

// gcd
// Documentation in header file
int gcd(int a,
        int b)
{
	if (a == 0)
		return b;

	if (a > b)
		gcd(b, a);

	gcd(b % a, a);
}

