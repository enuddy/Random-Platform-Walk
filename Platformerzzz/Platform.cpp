#include "Platform.h"

/*
Reads in textfiles that contain 10x10 maps.  These are put together to form the platforming game.

key is filled with integers from 1-5.
Text files are filled with 1's and 0's that represent empty space and floor panels.
All of the text files are named (someint).txt
*/
Platform::Platform(){
	key = "1234543123123123";
	if (key.length() > MAX_KEY_SIZE)
		key.resize(MAX_KEY_SIZE);
	playerLocationX = 0;
	playerLocationY = 0;
	numMoves = 0;
	done = false;

	std::ifstream inFile;
	for (int i = 0; i < key.length(); i++){
		//subtract '0' to change character values to their integer equivalents. 
		std::string fileName = std::to_string(key[i] - '0') + ".txt";
		inFile.open(fileName);
		if (!inFile.is_open()){
			std::cout << "ERR CANNOT OPEN FILE";
			return;
		}
		for (int j = 0; j < BLOCK_HEIGHT; j++){
			for (int k = 0; k < BLOCK_LENGTH; k++)
				currentMap[k + (i * 10)][j] = inFile.get() - '0';
			//ignores newline
			inFile.get();
		}
		inFile.close();
	}
}

//moves the player downwards cool.
//I forget if this being a bool is relevant.  I don't think so.  Change this probably
bool Platform::act(){
	if (currentMap[playerLocationX][playerLocationY + 1] != 1){
		playerLocationY++;
		return true;
	}
	if (playerLocationY >= BLOCK_HEIGHT - 1){
		//gameOver();
	}
	return false;
}

//don't fall nerd.
//Change this at some point so that way the game registers death sooner.
//It shouldn't be able to fall and think it's doing a good job
bool Platform::checkDeath(){
	if (playerLocationY >= BLOCK_HEIGHT - 1)
			return true;
	return false;
}

//fitness is a judge of how well each bot does in a round
float Platform::getFitness(){
	float fitness = playerLocationX / (float)numMoves;
	//Prevents bots that efficently die from being considered 'good'
	//possibly not a good thing to account for
	if (checkDeath())
		fitness--;
	
	//Bots that finish the map should be considered the best
	if (done)
		fitness++;
	return fitness;
}

//this updates the players location on the platformer, then calls output
void Platform::movePlayer(Action action){
	//stop moving at the end
	if (playerLocationX == BLOCK_LENGTH * key.length() - 1){
		//prevents the program from continuing senseless output
		if (!done){
			act();
			outputPlatform();
		}
		done = true;
		return;
	}

	numMoves++;
	//each if just double checks that it's a valid move.  Can't double jump, can't move off the map, etc
	switch (action)
	{
	case MOVE_LEFT:
		if (playerLocationX > 0 && playerLocationX != BLOCK_LENGTH * key.length() - 1)
			playerLocationX--;
		break;
	case MOVE_RIGHT:
		if (playerLocationX != BLOCK_LENGTH * key.length())
			playerLocationX++;
		break;
	case MOVE_UP:
		if (currentMap[playerLocationX][playerLocationY + 1] == 1)
			playerLocationY -= JUMP_HEIGHT;
		break;
	default:
		break;
	}
	//updates the map to move the player when it should be falling
	//also updates actors on the map if I ever add them
	act();
	outputPlatform();
}

//Merge this with the other move function at some point and add a bool that decides output
void Platform::movePlayer_NO_OUTPUT(Action action){
	if (playerLocationX == BLOCK_LENGTH * key.length() - 1){
		if (!done)
			act();
		done = true;
		return;
	}
	numMoves++;
	switch (action)
	{
	case MOVE_LEFT:
		if (playerLocationX > 0)
			playerLocationX--;
		break;
	case MOVE_RIGHT:
		playerLocationX++;
		break;
	case MOVE_UP:
		if (currentMap[playerLocationX][playerLocationY + 1] == 1)
			playerLocationY -= JUMP_HEIGHT;
		break;
	default:
		break;
	}
	act();
	//outputPlatform();
}

//update this so it doesn't print senseless whitespace
void Platform::outputPlatform(){
	system("cls");
	for (int i = 0; i < BLOCK_HEIGHT; i++){
		for (int j = 0; j < BLOCK_LENGTH * key.length(); j++){
			if (i == playerLocationY && j == playerLocationX)
				std::cout << "o";
			else if (currentMap[j][i] == EMPTY_SPACE)
				std::cout << " ";
			else if (currentMap[j][i] == FLOOR_SPACE)
				std::cout << "_";
			else
				std::cout << "NIL";
		}
		std::cout << "\n";
	}
	std::cout.flush();
	Sleep(50);
}