#include "Platform.h"
#include "Genetic.h"

#define GENERATIONS_BEFORE_OUTPUT 20
#define MAX_FAILS 3

int main(){
	std::string	geneToBuildOn = "";
	int numberOfGenerations = 0,
		numFails = 0,
		numGensBeforeSuccess = 0;
	bot bestBot;
	float bestFitness = 0.0f;

	srand(time(NULL));
	bestBot.fitness = -1;

	while (true){
		numberOfGenerations++;
		//Attempts to complete the game 50 or so times.  Keeps track of the 'best' solution
		for (int i = 0; i < GENERATION_SIZE; i++){
			//creates a new bot with a psuedo-random 'path'
			bot someAttempt(generateRandomString(), geneToBuildOn, numFails);
			Platform game;
			std::string currentPath = "";
			int j = 0;

			//passes the gene in, char by char, until dead or out of characters
			//it's essentially 'playing' the game here
			while (!game.checkDeath() && j < someAttempt.gene.length()){
				currentPath += someAttempt.gene[j];
				game.movePlayer_NO_OUTPUT((Action)currentPath[j]);
				j++;
			}

			//checks to see how well the bot did, then compares it to previous best
			someAttempt.fitness = game.getFitness();
			if (someAttempt.fitness > bestBot.fitness){
				bestBot = someAttempt;
				geneToBuildOn = currentPath;
				numFails = 0;
			}
		}

		//This is really just an output loop.
		//!!!!one section is important to the code, and should be kept even if output isn't needed!!!!!
		if (numberOfGenerations % GENERATIONS_BEFORE_OUTPUT == 0){
			//THIS IS IMPORTANT KEEP
			if (numFails < MAX_FAILS)
				numFails++;

			//Outputs what is currently the best bot
			Platform game;
			int i = 0;
			while (!game.checkDeath() && i < bestBot.gene.length()){
				game.movePlayer((Action)bestBot.gene[i]);
				i++;
			}
			if (bestBot.fitness > 1 && numGensBeforeSuccess == 0)
				numGensBeforeSuccess = numberOfGenerations;
			std::cout << "On generation: " << numberOfGenerations << "...\n"
				<< "Best fitness this round was: " << bestBot.fitness << "...\n"
				<< "Previous best was: " << bestFitness << "...\n"
				<< "Attempts before success: ~" << numGensBeforeSuccess * GENERATION_SIZE << "...\n";
		}
	}
	return 0;
}