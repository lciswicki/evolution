#include "evolution.h"
#include "Util.h"
#include <string>
#include <vector>
#include <iostream>


int Objective_Function(std::vector<int> perm, std::vector<std::vector<int>> weights) {
	int p_length = perm.size(); // permutation length
	int c_weight = 0;   // cycle weight
	for (int i = 0; i < p_length - 1; i++) {
		c_weight += weights[perm[i]][perm[i + 1]];
	}
	// adding an edge from last to first to close the cycle
	c_weight += weights[perm[p_length - 1]][perm[0]];
	return c_weight;
}

/// <summary>
/// Inverts part of a permutation from index i to j
/// </summary>
/// <param name="perm"> permuatation</param>
/// <param name="i"> start of inversion</param>
/// <param name="j"> end of inversion</param>
/// <returns> inverted permutation </returns>
std::vector<int> invert(std::vector<int> perm, int i, int j) {
    int p_size = perm.size();
    if (i < 0 || i >= p_size) {
        std::cout << "Error: " << i << " out of bound" << std::endl;
        return perm;
    }
    if (j < 0 || j >= p_size) {
        std::cout << "Error: " << j << " out of bound" << std::endl;
        return perm;
    }
    if (j < i) {
        std::cout << "Error: " << j << " smaller than " << i << std::endl;
        return perm;
    }
    int temp = 0;
    // division with an upper ceiling
    int half_range = ((j - i) + 2 - 1) / 2;
    for (int x = 0; x < half_range; x++) {
        temp = perm[i + x];
        perm[i + x] = perm[j - x];
        perm[j - x] = temp;
    }
    return perm;
}

/// <summary>
/// Effectively calculates cycle length of the new permutation
/// </summary>
/// <param name="perm_old"> old permutation </param>
/// <param name="length_old"> old path length </param>
/// <param name="i"> start of inversion</param>
/// <param name="j"> end of inversion</param>
/// <param name="weights"></param>
/// <returns> new path length</returns>
double NewLength(std::vector<int> perm_old, double length_old, int i, int j, std::vector<std::vector<int>> weights) {
    int p_size = perm_old.size();
    double length_new = length_old;
    if (i == 0 && j == p_size - 1) {
        // cycle length doesnt change
    }
    else if (i == 0) {
        length_new -= weights[perm_old[p_size - 1]][perm_old[i]];
        length_new -= weights[perm_old[j]][perm_old[j + 1]];
        length_new += weights[perm_old[p_size - 1]][perm_old[j]];
        length_new += weights[perm_old[i]][perm_old[j + 1]];
    }
    else if (j == p_size - 1) {
        length_new -= weights[perm_old[i - 1]][perm_old[i]];
        length_new -= weights[perm_old[j]][perm_old[0]];
        length_new += weights[perm_old[i - 1]][perm_old[j]];
        length_new += weights[perm_old[i]][perm_old[0]];
    }
    else {
        length_new -= weights[perm_old[i - 1]][perm_old[i]];
        length_new -= weights[perm_old[j]][perm_old[j + 1]];
        length_new += weights[perm_old[i - 1]][perm_old[j]];
        length_new += weights[perm_old[i]][perm_old[j + 1]];
    }
    return length_new;
}

Chromosome::Chromosome(std::vector<int> perm, int value) {
	this->value = value;
	this->perm = perm;
}

int Chromosome::EvalChrom(){
	return 0;
};

Chromosome::~Chromosome(){};

Chromosome Evolution::MutateChrom(Chromosome chrom){

};

void Evolution::CrossChrom(){};


Evolution::Evolution(std::string data_path, int population_size, int prob) {
	this->group_size = population_size;
	std::vector<std::vector<int>> coords = Parser(data_path);
	std::vector<std::vector<int>> weights = Weights(coords);
	this->weights = weights;
	this->prob = prob;
	this->size = coords.size();

	for (int i = 0; i < population_size; i++) {
		std::vector<int> r_perm = Perm_Gen(size);
		population.push_back(Chromosome(r_perm, Objective_Function(r_perm, weights)));
	}
};

void Evolution::Evolve(bool verbose){
	
};

Evolution::~Evolution() {};
