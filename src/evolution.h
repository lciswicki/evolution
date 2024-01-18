#pragma once
#include <vector>
#include <string>
#include <tuple>
#include "Util.h"

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
private:


	void MutateChrom();
	/// <summary>
	/// 1. takes first half of the first permutation
	/// 2. 
	/// </summary>
	void CrossChrom();

public:
	std::string data_path;
	int group_size;
	std::vector<Chromosome> chroms;
	std::vector<std::vector<int>> weights;

	Evolution(std::string data_path, int group_size);
	void Evolve(bool verbose = false);
	~Evolution();
};