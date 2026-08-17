#pragma once

#include <vector>
#include <nlohmann/json.hpp>

#include "Task.h"
#include "JsonSerializer.h"

using json = nlohmann::json;

class ToDoList
{
public:
	friend void to_json(json& j, const ToDoList& t);
	friend void from_json(const json& j, ToDoList& t);

	ToDoList() = default;
	~ToDoList() = default;
	//ToDoList(const ToDoList& toDoList);

	void emplaceBack(Task& task);
	void erase(unsigned int id);

	size_t getSize() const;
	std::vector<Task>::const_iterator cbegin() const;
	std::vector<Task>::const_iterator cend() const;

private:
	std::vector<Task> mTasks{};
};

ToDoList initToDoList(const JsonSerializer& data);
void saveToDoList(JsonSerializer& jsonSerializer, const ToDoList& toDoList);