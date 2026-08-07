#include "ToDoList.h"

ToDoList::ToDoList(const ToDoList& toDoList) { this->tasks = toDoList.tasks; }

void ToDoList::emplaceBack(const Task& task) { this->tasks.emplace_back(task); }
void ToDoList::erase(unsigned int id) {
	if (id >= this->tasks.size()) return;
	this->tasks.erase(this->tasks.begin() + id);
}

size_t ToDoList::getSize() const { return this->tasks.size(); }
std::vector<Task>::const_iterator ToDoList::cbegin() const { return this->tasks.cbegin(); }
std::vector<Task>::const_iterator ToDoList::cend() const { return this->tasks.cend(); }

ToDoList initToDoList(const json& data) {
	ToDoList toDoList{};
	// Открыть файл Json
	// Записать данные с файла
	// Вернуть обьект

	json::const_iterator it{ data.find("ToDoList") };

	if (it == data.cend()) {
		return toDoList; // Потом добавить Исключение(throw)
	}
	
	Task::setIdCounter(it->at("Number of tasks"));

	return toDoList;
}