#include <string>
#include <ctime>
#include <random>
#include <iostream>

#define GENERATION_SIZE 50
#define MAX_GENE_SIZE 10

//This structure holds the path that the bot will take and how well it did during it's run
struct bot{
	std::string gene;
	float fitness;
	bot(std::string gene, std::string build, int numFails){
		std::string startingGene = build; //resizing build causes problems
		
		//taks the previous best, resizes to account for mistakes
		if (startingGene.length() > numFails)
			startingGene.resize(startingGene.length() - numFails);
		
		//adds on a random string for the new attempt
		this->gene = startingGene + gene;
		fitness = 0.0f;
	}
	bot(){
		gene = "";
		fitness = 0.0f;
	}
};

std::string generateRandomString();