#include "Genetic.h"

//random string of char vals between 0-3
//HARDCODED VALUES CHANGE ME
std::string generateRandomString(){
	std::string gene = "";
	for (int i = 0; i < MAX_GENE_SIZE; i++){
		gene += (char)(rand() % 3 + 1);
	}
	return gene;
}