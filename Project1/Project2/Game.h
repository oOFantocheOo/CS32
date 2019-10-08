#ifndef _GAME_H_
#define _GAME_H_
class Arena;
class History;
class Game
{
public:
	// Constructor/destructor
	Game(int rows, int cols, int nRobots);
	~Game();

	// Mutators
	void play();

private:
	Arena* m_arena;
	History* m_history;
};
#endif