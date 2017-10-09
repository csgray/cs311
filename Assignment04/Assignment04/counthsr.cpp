// counthsr.cpp
// Corey S. Gray
// 08 Oct 2017
//
// For CS 311 Fall 2017
// Source for Assignment 4

#include "counthsr.h"
#include <vector>
using std::vector;

// Nonrecursive wrapper function
int countHSR(int dim_x, int dim_y,			// board dimensions
			 int hole_x, int hole_y,		// hole coordinates
			 int start_x, int start_y,		// start square coordinates
			 int finish_x, int finish_y)	// finish square coordinates
{
	// Create an empty partial solution
	vector<int> boardArray(dim_x * dim_y);
	boardArray[start_x * dim_y + start_y] = 1; // Mark start as unavailable
	boardArray[hole_x * dim_y + hole_y] = 1; // Mark hole as unavailable
	int pos_x = start_x;
	int pos_y = start_y;
	int squaresLeft = (dim_x * dim_y) - 2; // Total minus start and hole

	int total = 0;

	// Call recursive workhorse with partial solution
	total += countHSR_recurse(boardArray,
		dim_x, dim_y,
		finish_x, finish_y,
		pos_x, pos_y,
		squaresLeft);

	// Return the return value of the workhorse function
	return total;
}

// Recursive workhorse function
int countHSR_recurse(vector<int> & boardArray,
					 int dim_x, int dim_y,
					 int finish_x, int finish_y,
					 int pos_x, int pos_y,
					 int squaresLeft)
{
	// Do we have a full solution?
	if (squaresLeft == 0 && pos_x == finish_x && pos_y == finish_y)
		return 1;

	int total = 0;

	// Is column to left of current position on the board?
	if (pos_x - 1 >= 0)
	{
		// Is row below current position on the board?
		if (pos_y - 1 >= 0 &&
			boardArray[(pos_x - 1) * dim_y + (pos_y - 1)] == 0) // Has this square been visited?
		{
			// Update current position.
			--pos_x;
			--pos_y;

			// Mark new square as visited.
			boardArray[pos_x * dim_y + pos_y] = 1;

			// Decrement number of squares left.
			--squaresLeft;

			// Make recursive call and add return value to total.
			total += countHSR_recurse(boardArray,
									  dim_x, dim_y,
									  finish_x, finish_y,
									  pos_x, pos_y,
									  squaresLeft);

			// Revert changes except updated total
			++squaresLeft;
			boardArray[pos_x * dim_y + pos_y] = 0;
			++pos_x;
			++pos_y;
		}

		// Current row is on the board by default
		if (boardArray[(pos_x - 1) * dim_y + pos_y] == 0) // Has this square been visited?)
		{
			// Update current position.
			--pos_x;

			// Mark new square as visited.
			boardArray[pos_x * dim_y + pos_y] = 1;

			// Decrement number of squares left.
			--squaresLeft;

			// Make recursive call and add return value to total.
			total += countHSR_recurse(boardArray,
									  dim_x, dim_y,
									  finish_x, finish_y,
									  pos_x, pos_y,
									  squaresLeft);

			// Revert changes except updated total
			++squaresLeft;
			boardArray[pos_x * dim_y + pos_y] = 0;
			++pos_x;
		}

		// Is row above current position on the board?
		if (pos_y + 1 <= dim_y - 1 &&
			boardArray[(pos_x - 1) * dim_y + (pos_y + 1)] == 0) // Has this square been visited?)
		{
			// Update current position.
			--pos_x;
			++pos_y;

			// Mark new square as visited.
			boardArray[pos_x * dim_y + pos_y] = 1;

			// Decrement number of squares left.
			--squaresLeft;

			// Make recursive call and add return value to total.
			total += countHSR_recurse(boardArray,
									  dim_x, dim_y,
									  finish_x, finish_y,
									  pos_x, pos_y,
									  squaresLeft);

			// Revert changes except updated total
			++squaresLeft;
			boardArray[pos_x * dim_y + pos_y] = 0;
			++pos_x;
			--pos_y;
		}
	}

	// Current column is on the board by default
	// Is row below current position on the board?
	if (pos_y - 1 >= 0 &&
		boardArray[pos_x * dim_y + (pos_y - 1)] == 0) // Has this square been visited?
	{
		// Update current position.
		--pos_y;

		// Mark new square as visited.
		boardArray[pos_x * dim_y + pos_y] = 1;

		// Decrement number of squares left.
		--squaresLeft;

		// Make recursive call and add return value to total.
		total += countHSR_recurse(boardArray,
			dim_x, dim_y,
			finish_x, finish_y,
			pos_x, pos_y,
			squaresLeft);

		// Revert changes except updated total
		++squaresLeft;
		boardArray[pos_x * dim_y + pos_y] = 0;
		++pos_y;
	}

	// Is row above current position on the board?
	if (pos_y + 1 <= dim_y - 1 &&
		boardArray[pos_x * dim_y + (pos_y + 1)] == 0) // Has this square been visited?
	{
		// Update current position.
		++pos_y;

		// Mark new square as visited.
		boardArray[pos_x * dim_y + pos_y] = 1;

		// Decrement number of squares left.
		--squaresLeft;

		// Make recursive call and add return value to total.
		total += countHSR_recurse(boardArray,
			dim_x, dim_y,
			finish_x, finish_y,
			pos_x, pos_y,
			squaresLeft);

		// Revert changes except updated total
		++squaresLeft;
		boardArray[pos_x * dim_y + pos_y] = 0;
		--pos_y;
	}

	// Is column to right of current position on the board?
	if (pos_x + 1 <= dim_x - 1)
	{
		// Is row below current position on the board?
		if (pos_y - 1 >= 0 &&
			boardArray[(pos_x + 1) * dim_y + (pos_y - 1)] == 0) // Has this square been visited?
		{
			// Update current position.
			++pos_x;
			--pos_y;

			// Mark new square as visited.
			boardArray[pos_x * dim_y + pos_y] = 1;

			// Decrement number of squares left.
			--squaresLeft;

			// Make recursive call and add return value to total.
			total += countHSR_recurse(boardArray,
									  dim_x, dim_y,
									  finish_x, finish_y,
									  pos_x, pos_y,
									  squaresLeft);

			// Revert changes except updated total
			++squaresLeft;
			boardArray[pos_x * dim_y + pos_y] = 0;
			--pos_x;
			++pos_y;
		}

		// Current row is on the board by default
		if (boardArray[(pos_x + 1) * dim_y + pos_y] == 0) // Has this square been visited?)
		{
			// Update current position.
			++pos_x;

			// Mark new square as visited.
			boardArray[pos_x * dim_y + pos_y] = 1;

			// Decrement number of squares left.
			--squaresLeft;

			// Make recursive call and add return value to total.
			total += countHSR_recurse(boardArray,
				dim_x, dim_y,
				finish_x, finish_y,
				pos_x, pos_y,
				squaresLeft);

			// Revert changes except updated total
			++squaresLeft;
			boardArray[pos_x * dim_y + pos_y] = 0;
			--pos_x;
		}

		// Is row above current position on the board?
		if (pos_y + 1 <= dim_y - 1 &&
			boardArray[(pos_x + 1) * dim_y + (pos_y + 1)] == 0) // Has this square been visited?)
		{
			// Update current position.
			++pos_x;
			++pos_y;

			// Mark new square as visited.
			boardArray[pos_x * dim_y + pos_y] = 1;

			// Decrement number of squares left.
			--squaresLeft;

			// Make recursive call and add return value to total.
			total += countHSR_recurse(boardArray,
				dim_x, dim_y,
				finish_x, finish_y,
				pos_x, pos_y,
				squaresLeft);

			// Revert changes except updated total
			++squaresLeft;
			boardArray[pos_x * dim_y + pos_y] = 0;
			--pos_x;
			--pos_y;
		}
	}

	return total;
}
