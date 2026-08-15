#include "SortingAndView.h"

std::vector<const Task*> Sort::sortByStringAZ(const std::vector<Task>& tasks, const std::string& (Task::* pField)() const) {
	std::vector<const Task*> pTasks{};
	pTasks.reserve(tasks.size());

	for (const Task& t : tasks) {
		pTasks.emplace_back(&t);
	}

	std::sort(pTasks.begin(), pTasks.end(), [pField](const Task* t1, const Task* t2)->bool {
		return (t1->*pField)() < (t2->*pField)();
		});

	return pTasks;
}
std::vector<const Task*> Sort::sortByStringZA(const std::vector<Task>& tasks, const std::string& (Task::* pField)() const) {
	std::vector<const Task*> pTasks{};
	pTasks.reserve(tasks.size());

	for (const Task& t : tasks) {
		pTasks.emplace_back(&t);
	}

	std::sort(pTasks.begin(), pTasks.end(), [pField](const Task* t1, const Task* t2)->bool {
		return (t1->*pField)() > (t2->*pField)();
		});

	return pTasks;
}