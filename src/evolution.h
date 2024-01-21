#pragma once
#include <vector>
#include <string>
#include <tuple>
#include "Util.h"
#include <stdexcept>
#include <chrono>
#include <random>
#include <iostream>

/**
 * @brief Calculates objective function for a permutation
 * O(n)
 * @param perm starting permutation
 * @return Objective value of the permutation
 */
double Objective_Function(std::vector<int> perm, std::vector<std::vector<int>> weights);

/**
 * @brief Inverts a part of a vector
 * O(n)
 * @param perm starting permutation
 * @param i start of inversion
 * @param j end of inversion
 * @return std::vector<int> inverted vector
 */
std::vector<int> invert(std::vector<int> perm, int i, int j);

/// <summary>
/// Effectively calculates cycle length of the new permutation
/// </summary>
/// <param name="perm_old"> old permutation </param>
/// <param name="length_old"> old path length </param>
/// <param name="i"> start of inversion</param>
/// <param name="j"> end of inversion</param>
/// <param name="weights"></param>
/// <returns> new path length</returns>
double NewLength(std::vector<int> perm_old, double length_old, int i, int j, std::vector<std::vector<int>> weights);

int FindPosition(std::vector<int> perm, double value);

class Chromosome {
public:
	double value;
	std::vector<int> perm;
	//double getValue() const { return value; } // maybe have to use this later

	Chromosome(std::vector<int> perm, double value);
	int EvalChrom();
	~Chromosome();
};


/// <summary>
/// To sort chromosomes by value
/// </summary>
/// <param name="s1"></param>
/// <param name="s2"></param>
/// <returns></returns>
bool operator<(const Chromosome& s1, const Chromosome& s2);

/// <summary>
/// 
/// </summary>
class Evolution{
public:
	Chromosome MutateChrom(Chromosome chrom);
	Chromosome CrossChrom(Chromosome ch1, Chromosome ch2);
	

public:
	std::string data_path;
	int population_size;
	int size;
	std::vector<Chromosome> population;
	std::vector<std::vector<int>> weights;

	Evolution(std::string data_path, int population_size);

	int Evolve(double mutation_prob, int no_of_pairs, int max_stale_iter, int max_generations, bool verbose = false);
	~Evolution();
};





