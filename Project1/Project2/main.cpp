

// zion_solution.cpp

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Arena.h"
#include "globals.h"
#include "Robot.h"
#include "Player.h"
#include "Game.h"
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#include  "History.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
	// Initialize the random number generator.  (You don't need to
	// understand how this works.)
	srand(static_cast<unsigned int>(time(0)));

	// Create a game
	// Use this instead to create a mini-game:   Game g(3, 3, 2);
	Game g(15, 18, 1);

	// Play the game
	g.play();
}
