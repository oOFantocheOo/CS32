#include "History.h"
#include "Arena.h"
#include "globals.h"
#include <string>
#include <iostream>
using namespace std;


History::History(int nRows, int nCols)
{
	// Position (row,col) in the arena coordinate system is represented in
	// the array element grid[row-1][col-1]
	int r, c;

	// Fill the grid with dots
	for (r = 0; r < nRows; r++)
		for (c = 0; c < nCols; c++)
			grid[r][c] = 'A';
	for (r = 0; r < nRows; r++)
		for (c = 0; c < nCols; c++)
			position[r][c] = 0;
	nr = nRows;
	nc = nCols;
}

bool History::record(int r, int c)
{
	if (r>nr || c>nc)
		return false;
	else
	{
		position[r - 1][c - 1]++;
		return true;
	}
}

void History::display() const
{
	clearScreen();
	int r, c;
	for (r = 0; r < nr; r++)
		for (c = 0; c < nc; c++)
		{
			if (position[r][c] == 0)
				cout << '.';
			else if (position[r][c] <= 26)
				cout << (char)(grid[r][c] - 1 + position[r][c]);
			else
				cout << 'Z';
			if (c == nc - 1)
				cout << endl;
		}

	cout << endl;
}