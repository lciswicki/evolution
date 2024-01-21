#include "evolution.h"
#include "Util.h"
#include <vector>
#include <iostream>
#include <string>



int main() {
	int pop_size = 50;
	double prob = 0.2;
	int number_of_pairs = 20;
	int max_stale_iter = 500;
	int max_generations = 20000;

    std::string data_path = "./Data/icw1483.tsp";

	Evolution ev1(data_path, pop_size);
	ev1.Evolve(prob, number_of_pairs, max_stale_iter, max_generations, true);


}