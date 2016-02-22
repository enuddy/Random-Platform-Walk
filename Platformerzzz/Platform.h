#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>

#define BLOCK_LENGTH 10
#define BLOCK_HEIGHT 10
#define JUMP_HEIGHT 3
#define EMPTY_SPACE 0
#define FLOOR_SPACE 1
#define MAX_KEY_SIZE 7

enum Action{
	NIL,
	MOVE_UP,
	MOVE_RIGHT,
	MOVE_LEFT,
	NUM_ACTIONS
};


class Platform{
private:
	int currentMap[BLOCK_LENGTH * MAX_KEY_SIZE][BLOCK_HEIGHT],
		playerLocationX,
		playerLocationY;
	std::string key;
	bool isDead;
	bool done;
	int numMoves;
public:
	Platform();
	

	inline int getNumMoves(){ return numMoves; };

	float getFitness();
	bool act();
	bool checkDeath();
	void gameOver();
	void movePlayer(Action action);
	void movePlayer_NO_OUTPUT(Action action);
	void outputPlatform();

};