#include "evolution.h"
#include "Util.h"
#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <random>


std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

double Objective_Function(std::vector<int> perm, std::vector<std::vector<int>> weights) {
	int p_length = perm.size(); // permutation length
	double c_weight = 0;   // cycle weight
	for (int i = 0; i < p_length - 1; i++) {
		c_weight += weights[perm[i]][perm[i + 1]];
	}
	// adding an edge from last to first to close the cycle
	c_weight += weights[perm[p_length - 1]][perm[0]];
	return c_weight;
}


// O(n)
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


int FindPosition(std::vector<int> perm, double value) {
    auto it = std::find(perm.begin(), perm.end(), value);

    if (it != perm.end()){
        int index = it - perm.begin();
        return index;
    }
    else {
        //std::cout << "Error: " << value << " not found in permutation." << std::endl;
        return -1;
    }
}


Chromosome::Chromosome(std::vector<int> perm, double value) {
	this->value = value;
	this->perm = perm;
}


bool operator<(const Chromosome& s1, const Chromosome& s2) {
    // maybe have to use getValue()
    return s1.value < s2.value;
};


int Chromosome::EvalChrom(){
	return 0;
};


Chromosome::~Chromosome(){};


// O(n)
Chromosome Evolution::MutateChrom(Chromosome chrom){
    std::uniform_int_distribution<std::mt19937::result_type> distrib_i(0, size - 2);
    int i = distrib_i(rng);
    std::uniform_int_distribution<std::mt19937::result_type> distrib_j(i, size - 1);
    int j = distrib_j(rng);

    std::vector<int> new_perm = invert(chrom.perm, i, j);
    double new_length = NewLength(chrom.perm, chrom.value, i, j, weights);
    chrom.perm = new_perm;
    chrom.value = new_length;
    return chrom;
};


Evolution::Evolution(std::string data_path, int population_size){
    this->population_size = population_size;
    std::vector<std::vector<int>> coords = Parser(data_path);
    std::vector<std::vector<int>> weights = Weights(coords);
    this->weights = weights;
    this->size = coords.size();

    // adding starting chromosomes to the population
    for (int i = 0; i < population_size; i++) {
        std::vector<int> r_perm = Perm_Gen(size);
        population.push_back(Chromosome(r_perm, Objective_Function(r_perm, weights)));
    }
};


// Crossover method PMX from this paper by Gokturk Ucoluk
// can improve time of setting value to constant from linear
// https://user.ceng.metu.edu.tr/~ucoluk/research/publications/tspnew.pdf
// O(n^2)
Chromosome Evolution::CrossChrom(Chromosome ch1, Chromosome ch2){
    int ch1_size = ch1.perm.size();
    std::uniform_int_distribution<std::mt19937::result_type> distrib(0, ch1_size - 1);
    int crossover = distrib(rng); // values between zero and crossover are swapped

    // swapping 
    for (int i = 0; i < crossover; i++) {
        int ch1_value = ch1.perm[i];
        int ch2_value = ch2.perm[i];
        int ch2_index = FindPosition(ch1.perm, ch2_value); // index of ch2_value in ch1's permutation
        ch1.perm[i] = ch2_value;
        ch1.perm[ch2_index] = ch1_value;
    }
    // possible to improve this to constant time
    ch1.value = Objective_Function(ch1.perm, weights);

    return ch1;
};


int Evolution::Evolve(double mutation_prob, int no_of_pairs, int max_stale_iter, int max_generations, bool verbose){
    std::sort(population.begin(), population.end());
    int stale_iter_counter = 0;
    int best_length = population[0].value;
    int generation = 0;

    std::uniform_real_distribution<float> distrib(0, 1);

    while (generation < max_generations && stale_iter_counter < max_stale_iter) {
        if (verbose && generation % 10 == 0) {
            std::cout << "gen: " << generation << "\tbest: " << best_length << std::endl;
        }

        // mutating chromosomes
        for (int i = 0; i < population_size; i++) { // O(p)
            if (distrib(rng) < mutation_prob) {
                population[i] = MutateChrom(population[i]);
            }

        }
        std::sort(population.begin(), population.end());

        // breeding best chromosomes, generating 2 * no_of_pairs too much so will have te remove some later
        // O(n^3)
        for (int i = 0; i < no_of_pairs; i += 2) {
            population.push_back(CrossChrom(population[i], population[i + 1]));
            population.push_back(CrossChrom(population[i + 1], population[i]));
        }

        std::sort(population.begin(), population.end());
        // removing additional chromosomes
        for (int i = 0; i < no_of_pairs; i++) {
            population.pop_back();
        }

        int new_length = population[0].value;

        if (new_length == best_length) {
            stale_iter_counter++;
        }
        else {
            stale_iter_counter = 0;
        }

        best_length = new_length;



        generation++;
    }

    if (verbose) {
        std::cout << "best length = " << best_length << " real length = " << Objective_Function(population[0].perm, weights) << std::endl;
        PrintVectorInt(population[0].perm);
    }

    return best_length;
    
};


Evolution::~Evolution() {};
