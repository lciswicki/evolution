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
	int pop_size = 50;
	double prob = 0.2;
	int number_of_pairs = 10;
	int max_stale_iter = 100;
	int max_generations = 10000;

    std::string data_path = "./Data/bcl380.tsp";
	//std::string data_path = "./Data/xqf131.tsp";

	Evolution ev1(data_path, pop_size);
	ev1.Evolve(prob, number_of_pairs, max_stale_iter, max_generations, true);


}