// counthsr.h 
// Corey S. Gray
// 08 Oct 2017
//
// For CS 311 Fall 2017
// Header for Assignment 4

#ifndef FILE_COUNTHSR_H_INCLUDED
#define FILE_COUNTHSR_H_INCLUDED

#include <vector>

int countHSR(int dim_x, int dim_y,			// board dimensions
			 int hole_x, int hole_y,		// hole coordinates
			 int start_x, int start_y,		// start square coordinates
			 int finish_x, int finish_y);	// finish square coordinates

int countHSR_recurse(std::vector<int> & boardArray,
					 int dim_x, int dim_y,
					 int finish_x, int finish_y,
					 int pos_x, int pos_y,
					 int squaresLeft);

#endif  //#ifndef FILE_COUNTHSR_H_INCLUDED
