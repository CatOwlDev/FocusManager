#pragma once

#include <vector>
#include <algorithm>
#include <nlohmann/json.hpp>

#include "Task.h"
#include "JsonSerializer.h"
#include "Error.h"
#include "Timer.h"

using json = nlohmann::json;

class ToDoList
{
public:
	friend void to_json(json& j, const ToDoList& t);
	friend void from_json(const json& j, ToDoList& t);

	ToDoList() = default;
	~ToDoList() = default;

	void emplaceBack(const Task& task);
	void erase(int selected);

	size_t getSize() const;
	const std::vector<Task>& getTasks() const;
	Task& getTask(int selected);

private:
	std::vector<Task> mTasks{};
};

void to_json(json& j, const ToDoList& t);
void from_json(const json& j, ToDoList& t);

ToDoList initToDoList(const JsonSerializer& data);
void saveToDoList(JsonSerializer& jsonSerializer, const ToDoList& toDoList);