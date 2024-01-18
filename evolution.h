#pragma once
#include <vector>
#include <string>
#include <tuple>

class Chromosome {
public:
	int value;
	std::vector<int> perm;

	Chromosome();
	int EvalChrom();
	~Chromosome();
};

// przy tworzeniu wybrac sposob mutacji jako enum
// potem switch case po enumach?
class Evolution{
private:
	void MutateChrom();
	void CrossChrom();

public:
	Evolution();
	void Initialize();
	void Evolve();
	~Evolution();
};