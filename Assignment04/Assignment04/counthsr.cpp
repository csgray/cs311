// counthsr.cpp
// Corey S. Gray
// 08 Oct 2017
//
// For CS 311 Fall 2017
// Source for Assignment 4: countHSR recursive function

#include "counthsr.h"
#include <vector>
using std::vector;

// countHSR
// Documentation in header file.
int countHSR(int dim_x, int dim_y,			// Board dimensions
			 int hole_x, int hole_y,		// Hole coordinates
			 int start_x, int start_y,		// Start square coordinates
			 int finish_x, int finish_y)	// Finish square coordinates
{
	// Create an empty partial solution
	vector<int> boardArray(dim_x * dim_y);
	boardArray[start_x * dim_y + start_y] = 1;	// Mark start as unavailable
	boardArray[hole_x * dim_y + hole_y] = 1;	// Mark hole as unavailable
	int pos_x = start_x;						// Set current position to starting coordinates
	int pos_y = start_y;
	int squaresLeft = (dim_x * dim_y) - 2;		// Total minus start and hole

	// Start with zero solutions.
	int total = 0;

	// Call recursive workhorse with empty partial solution
	total += countHSR_recurse(boardArray,
							  dim_x, dim_y,
							  finish_x, finish_y,
							  pos_x, pos_y,
							  squaresLeft);

	// Return the number of solutions.
	return total;
}

// countHSR_recurse
// Documentation in header file.
int countHSR_recurse(vector<int> & boardArray,		// Array of visited/unavailable squares
					 int dim_x, int dim_y,			// Board dimensions
					 int finish_x, int finish_y,	// Finish square coordinates
					 int pos_x, int pos_y,			// Spider's current coordinates
					 int squaresLeft)				// Number of unvisited squares
{
	// Do we have a full solution?
	if (squaresLeft == 0 &&							// No more squares available
		pos_x == finish_x && pos_y == finish_y)		// Current position is finish square
		return 1;

	// If not a full solution, set total to 0 and check for solutions.
	int total = 0;

	// Check for solutions left to right and bottom to top.
	if (pos_x - 1 >= 0)	// Is column west of the current position on the board?
	{
		// Check for solutions to the SW.
		if (pos_y - 1 >= 0 &&									// Is row below current position on the board?
			boardArray[(pos_x - 1) * dim_y + (pos_y - 1)] == 0)	// Has this square not been visited?
		{
			// Update current position to move SW.
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

			// Revert changes except updated total.
			++squaresLeft;
			boardArray[pos_x * dim_y + pos_y] = 0;
			++pos_x;
			++pos_y;
		}

		// Check for solutions to the W.
		// Current row is on the board so no need to check that.
		if (boardArray[(pos_x - 1) * dim_y + pos_y] == 0) // Has this square not been visited?
		{
			// Update current position to move W.
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

			// Revert changes except updated total.
			++squaresLeft;
			boardArray[pos_x * dim_y + pos_y] = 0;
			++pos_x;
		}

		// Check for solutions to the NW.
		if (pos_y + 1 <= dim_y - 1 &&							// Is row above current position on the board?
			boardArray[(pos_x - 1) * dim_y + (pos_y + 1)] == 0) // Has this square not been visited?)
		{
			// Update current position to move NW.
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

			// Revert changes except updated total.
			++squaresLeft;
			boardArray[pos_x * dim_y + pos_y] = 0;
			++pos_x;
			--pos_y;
		}
	}

	// Current column is on the board so no need to check that.
	// Check for solutions to the S.
	if (pos_y - 1 >= 0 &&								// Is row below current position on the board?
		boardArray[pos_x * dim_y + (pos_y - 1)] == 0)	// Has this square not been visited?
	{
		// Update current position to move S.
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

		// Revert changes except updated total.
		++squaresLeft;
		boardArray[pos_x * dim_y + pos_y] = 0;
		++pos_y;
	}

	// Check for solutions to the N.
	if (pos_y + 1 <= dim_y - 1 &&						// Is row above current position on the board?
		boardArray[pos_x * dim_y + (pos_y + 1)] == 0)	// Has this square been visited?
	{
		// Update current position to move N.
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

	if (pos_x + 1 <= dim_x - 1)	// Is column east of current position on the board?
	{
		// Check for solutions to the SE.
		if (pos_y - 1 >= 0 &&									// Is row below current position on the board?
			boardArray[(pos_x + 1) * dim_y + (pos_y - 1)] == 0) // Has this square not been visited?
		{
			// Update current position to move SE.
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

		// Check for solutions to the E.
		// Current row is on the board by default so no need to check that.
		if (boardArray[(pos_x + 1) * dim_y + pos_y] == 0) // Has this square been visited?)
		{
			// Update current position to move E.
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

		// Check for solutions to the NE.
		if (pos_y + 1 <= dim_y - 1 &&							// Is row above current position on the board?
			boardArray[(pos_x + 1) * dim_y + (pos_y + 1)] == 0) // Has this square been visited?)
		{
			// Update current position to move NE.
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

	// Return total number of solutions found from current position.
	return total;
}
