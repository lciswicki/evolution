#include "evolution.h"
#include "Util.h"
#include <string>
#include <vector>

Chromosome::Chromosome(std::vector<int> perm, int value) {
	this->value = value;
	this->perm = perm;
}

int Chromosome::EvalChrom(){
	return 0;
};

Chromosome::~Chromosome(){};

void Evolution::MutateChrom(){};

void Evolution::CrossChrom(){};


Evolution::Evolution(std::string data_path, int group_size) {
	this->group_size = group_size;
	//std::vector<std::vector<int>> coords = Parser(data_path);
	//std::vector<std::vector<int>> weights = Weights(coords);
	//this->weights = weights;
};

void Evolution::Evolve(bool verbose){};

Evolution::~Evolution() {};
