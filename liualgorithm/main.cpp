#include <iostream>
#include "liualg.h"

int main() {

	int numberOfTasks;
	std::cout << "Poddaj ilosc zadan:";
	std::cin >> numberOfTasks;

	LiuAlg alg(numberOfTasks);

	alg.createAndAddTasks();
	
	alg.solve();

	alg.showTasks();
	alg.showLatencyOfTasks();
	
	std::cout << std::endl;
	std::cout << "Max latency:"<< alg.countMaxLatency();

	return 0;
}