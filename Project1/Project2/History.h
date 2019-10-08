#include "globals.h"
#ifndef _HISTORY_H_
#define _HISTORY_H
using namespace std;


class History
{
private:
	int position[MAXROWS][MAXCOLS];
	char grid[MAXROWS][MAXCOLS];
	int nr, nc;
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;
};

#endif
