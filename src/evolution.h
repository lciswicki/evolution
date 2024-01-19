#pragma once
#include <vector>
#include <string>
#include <tuple>
#include "Util.h"

/**
 * @brief Calculates objective function for a permutation
 * O(n)
 * @param perm starting permutation
 * @return Objective value of the permutation
 */
int Objective_Function(std::vector<int> perm, std::vector<std::vector<int>> weights);

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

class Chromosome {
public:
	int value;
	std::vector<int> perm;

	Chromosome(std::vector<int> perm, int value);
	int EvalChrom();
	~Chromosome();
};

// przy tworzeniu wybrac sposob mutacji jako enum
// potem switch case po enumach?
class Evolution{
public:
	Chromosome MutateChrom(Chromosome chrom);
	Chromosome CrossChrom(Chromosome ch1, Chromosome ch2);
	int FindPosition(std::vector<int> perm, int value);
	void SortPopulation();

public:
	std::string data_path;
	int group_size;
	int size;
	int prob;
	std::vector<Chromosome> population;
	std::vector<std::vector<int>> weights;

	Evolution(std::string data_path, int population_size, int prob);

	void Evolve(bool verbose = false);
	~Evolution();
};