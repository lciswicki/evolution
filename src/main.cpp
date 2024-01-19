#include "evolution.h"
#include "Util.h"
#include <vector>
#include <iostream>
#include "Util.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <chrono>

int main() {
	int pop_size = 20;
	int prob = 0.1;
	std::vector<int> perm1 = Perm_Gen(20);

    std::string data_path = "./Data/xqf131.tsp";

	Evolution ev1(data_path, pop_size, prob);

	PrintVectorInt(ev1.population[0].perm);
}