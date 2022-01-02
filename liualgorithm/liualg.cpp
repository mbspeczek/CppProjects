#include "liualg.h"
#include <iostream>
#include <algorithm>

LiuAlg::LiuAlg(size_t _numberOfTasks) 
	:
	numberOfTasks(_numberOfTasks) 
{

	tasks = new Task[numberOfTasks];
	tasksEndTimes = new int[numberOfTasks];
}

LiuAlg::~LiuAlg() {
	delete[] tasks;
	delete[] tasksEndTimes;

}


void LiuAlg::createAndAddTasks() {
	size_t a, b, c;
	for (size_t i = 0; i < numberOfTasks; i++) {
		std::cout << "Podaj parametry p, r, d (po spacjach, zatwierdz enterem) dla zadania nr: " << i + 1 << std::endl;
		std::cin >> a >> b >> c;
		tasks[i].setParamsToTask(a, b, c);
	}
	
}

void LiuAlg::replaceTaskOnID(size_t id, Task newTask) {
	if (id >= 0 && id < numberOfTasks) {
		tasks[id].d = newTask.d;
		tasks[id].p = newTask.p;
		tasks[id].r = newTask.r;
	}
}

size_t LiuAlg::countMaxDurationTime() {
	size_t maxDurationTime = 0;
	for (int i = 0; i < numberOfTasks; i++) {
		maxDurationTime += tasks[i].p;
	}
	return maxDurationTime;
}

void LiuAlg::solve() {
	maxDurationTime = countMaxDurationTime();
	std::vector<int> avaJobs;
	int minID = 0;
	//avaJobs.reserve(numberOfTasks);
	for (int timeUnit = 0; timeUnit < maxDurationTime; timeUnit++) {
		avaJobs.clear();
		avaJobs = getAvailableTasksInCurrentTimeUnit(timeUnit);
		
		minID = getIdOfMinimalEndTask(avaJobs);

		makeTaskByID(minID, timeUnit);

	}

}

std::vector<int> LiuAlg::getAvailableTasksInCurrentTimeUnit(int timeUnit) {
	std::vector<int> tmpVector;
	for (int j = 0; j < numberOfTasks; j++) {
		if (tasks[j].r <= timeUnit && tasks[j].p > 0) {
			tmpVector.push_back(j);
		}
	}
	return tmpVector;
}

int LiuAlg::getIdOfMinimalEndTask(std::vector<int> avaliableTasks) {
	int minID = avaliableTasks.at(0);
	for (int k = 0; k < avaliableTasks.size(); k++) {
		(tasks[minID].d <= tasks[avaliableTasks.at(k)].d) ? minID : minID = avaliableTasks.at(k);
	}
	
	return minID;
}

void LiuAlg::makeTaskByID(size_t idOfTask, size_t timeUnit) {
	if (idOfTask >= 0 && idOfTask <= numberOfTasks) {
		tasks[idOfTask].p -= 1;
		if (tasks[idOfTask].p <= 0) {
			tasksEndTimes[idOfTask] = timeUnit;
		}
		taskNumberInTimeUnit.push_back(idOfTask);
	}
		
}

void LiuAlg::showTasks() {
	std::cout << "Indeks wykonywanego zadania w kolejnych jednostkach czasowych:" << std::endl;
	std::cout << "| ";
	for (int k = 0; k < maxDurationTime; k++) {
		std::cout << taskNumberInTimeUnit[k]+1<<" | ";
	}
	std::cout << std::endl;
}

void LiuAlg::showLatencyOfTasks() {
	for (int i = 0; i < numberOfTasks; i++) {
		std::cout << " zadanie " << i + 1 << " koniec w " << tasksEndTimes[i] + 1 << " jednostce. Planowany koniec w " << tasks[i].d << " - opoznienie: " << (tasksEndTimes[i] - tasks[i].d) + 1 << std::endl;
	}
}

int LiuAlg::countMaxLatency() {
	int late = tasksEndTimes[0] - tasks[0].d;
	int maxTime = late;
	for (int i = 0; i < numberOfTasks; i++) {
		late = tasksEndTimes[i] - tasks[i].d;
		late >= maxTime ? maxTime = late : maxTime;
	}
	return maxTime+1; 
}