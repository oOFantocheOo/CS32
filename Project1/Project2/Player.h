#include <string>
using namespace std;
#ifndef _PLAYER_H_
#define _PLAYER_H_
class Arena;
class Player
{
public:
	// Constructor
	Player(Arena *ap, int r, int c);

	// Accessors
	int  row() const;
	int  col() const;
	int  age() const;
	bool isDead() const;

	// Mutators
	string takeComputerChosenTurn();
	void   stand();
	void   move(int dir);
	bool   shoot(int dir);
	void   setDead();

private:
	Arena* m_arena;
	int    m_row;
	int    m_col;
	int    m_age;
	bool   m_dead;

	int    computeDanger(int r, int c) const;
};
#endif
