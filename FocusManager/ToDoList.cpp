#include "ToDoList.h"

ToDoList::ToDoList(const ToDoList& toDoList) { this->tasks = toDoList.tasks; }

void ToDoList::emplaceBack(Task& task) { 
	task.setId(static_cast<unsigned int>(this->tasks.size()));
	this->tasks.emplace_back(task); 
}
void ToDoList::erase(unsigned int id) {
	if (id >= this->tasks.size()) return;

	this->tasks.erase(this->tasks.begin() + id);
	
	for (size_t i{ static_cast<size_t>(id) }; i < this->tasks.size(); ++i)
		this->tasks[i].setId(static_cast<unsigned int>(i));
} 

size_t ToDoList::getSize() const { return this->tasks.size(); }
std::vector<Task>::const_iterator ToDoList::cbegin() const { return this->tasks.cbegin(); }
std::vector<Task>::const_iterator ToDoList::cend() const { return this->tasks.cend(); }

void to_json(json& j, const ToDoList& toDoList) {
	j = json{
		{ "ToDoList", { {"Tasks", toDoList.tasks} } }
	};
}
void from_json(const json& j, ToDoList& toDoList) {
	try {
		j.at("Tasks").get_to(toDoList.tasks);
	}
	catch (const json::exception& e) {
		Error error{
			getCurrentTime(),
			"file: ToDoList.cpp, func: from_json",
			e.what()
		};
		writeErrorReport(error);
	}
}

ToDoList initToDoList(const JsonSerializer& jsonSerializer) {
	ToDoList toDoList{};
	const json& data{ jsonSerializer.getData() };

	try {
		data.at("ToDoList").get_to(toDoList);
	}
	catch (const json::exception& e) {
		Error error{
			getCurrentTime(),
			"class: ToDoList, func: initToDoList",
			e.what()
		};
		writeErrorReport(error);
		return ToDoList{};
	}

	return toDoList;
}
void saveToDoList(JsonSerializer& jsonSerializer, const ToDoList& toDoList) {
	json j{};
	to_json(j, toDoList);
	jsonSerializer.setData(j);
}

// TODO: class Blocker, Timer. Func Sort