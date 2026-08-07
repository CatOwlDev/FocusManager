#pragma once
#include "Task.h"
#include "JsonSerializer.h"

#include <vector>

class ToDoList
{
public:
	ToDoList() = default;
	~ToDoList() = default;
	ToDoList(const ToDoList& toDoList);

	void emplaceBack(const Task& task);
	void erase(unsigned int id);

	size_t getSize() const;
	std::vector<Task>::const_iterator cbegin() const;
	std::vector<Task>::const_iterator cend() const;

	void sort();

private:
	std::vector<Task> tasks{};
};

ToDoList initToDoList(const json& data);

class ToDoListException : public std::runtime_error {};