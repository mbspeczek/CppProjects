#pragma once
#ifndef LIUALG_H
#define LIUALG_H

#include <vector>

struct Task
{
	size_t p; // task duration
	size_t r; // task appear time 
	size_t d; // task end
	void setParamsToTask(size_t p, size_t r, size_t d) {
		this->p = p;
		this->r = r;
		this->d = d;
	}
};

class LiuAlg {
public:
	LiuAlg();
	LiuAlg(size_t _numberOfTasks);

	~LiuAlg();

	
	void					createAndAddTasks();

	size_t					countMaxDurationTime();
	void					replaceTaskOnID(size_t id, Task newTask);
	std::vector<int>		getAvailableTasksInCurrentTimeUnit(int timeUnit);
	int						getIdOfMinimalEndTask(std::vector<int> tasks);
	void					makeTaskByID(size_t idOfTask, size_t timeUnit);

	void					showLatencyOfTasks();
	int						countMaxLatency();
	void					showTasks();

	void					solve();
protected:
private:
	size_t numberOfTasks;
	size_t maxDurationTime;
	
	std::vector<int> taskNumberInTimeUnit;

	Task* tasks;
	int* tasksEndTimes; 

	
};


#endif // !LIUALG_H
