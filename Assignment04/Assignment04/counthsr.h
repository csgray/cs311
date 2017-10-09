// counthsr.h 
// Corey S. Gray
// 08 Oct 2017
//
// For CS 311 Fall 2017
// Header for Assignment 4: countHSR recursive function

#ifndef FILE_COUNTHSR_H_INCLUDED
#define FILE_COUNTHSR_H_INCLUDED

#include <vector>

// countHSR
// Counts the solutions to a "holey spider run" board.
// Nonrecursive wrapper function that calls countHSR_recurse.
// Preconditions:
//		dim_x and dim_y > 0
//		hole_x, start_x, and finish_x <= dim_x
//		holy_y, start_y, and finish_y <= dim_y
// Postconditions:
//		Returns the total number of solutions as an integer.
// Exceptions:
//		Does not throw.
// Implementation in source file.
int countHSR(int dim_x, int dim_y,			// board dimensions
			 int hole_x, int hole_y,		// hole coordinates
			 int start_x, int start_y,		// start square coordinates
			 int finish_x, int finish_y);	// finish square coordinates

// countHSR_recurse
// Recursive workhorse for countHSR.
// Preconditions:
//		dim_x and dim_y > 0
//		hole_x, start_x, and finish_x <= dim_x
//		holy_y, start_y, and finish_y <= dim_y
//		squaresLeft  0;
// Postconditions: 
//		Returns the total number of solutions as an integer.
// Exceptions:
//		Does not throw.
// Implementation in source file.
int countHSR_recurse(std::vector<int> & boardArray,
					 int dim_x, int dim_y,
					 int finish_x, int finish_y,
					 int pos_x, int pos_y,
					 int squaresLeft);

#endif  //#ifndef FILE_COUNTHSR_H_INCLUDED
