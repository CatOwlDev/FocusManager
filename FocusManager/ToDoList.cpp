#include "ToDoList.h"

void ToDoList::emplaceBack(Task& task) { 
	task.setId(static_cast<unsigned int>(mTasks.size()));
	mTasks.emplace_back(task); 
}
void ToDoList::erase(unsigned int id) {
	if (id >= mTasks.size()) return;

	mTasks.erase(mTasks.begin() + id);
	
	for (size_t i{ static_cast<size_t>(id) }; i < mTasks.size(); ++i)
		mTasks[i].setId(static_cast<unsigned int>(i));
} 

size_t ToDoList::getSize() const { return mTasks.size(); }
std::vector<Task>::const_iterator ToDoList::cbegin() const { return mTasks.cbegin(); }
std::vector<Task>::const_iterator ToDoList::cend() const { return mTasks.cend(); }

void to_json(json& j, const ToDoList& toDoList) {
	j = json{
		{ "ToDoList", { {"Tasks", toDoList.mTasks} } }
	};
}
void from_json(const json& j, ToDoList& toDoList) {
	try {
		j.at("Tasks").get_to(toDoList.mTasks);
	}
	catch (const json::exception& e) {
		Error error{
			getCurrentTimeToString(),
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
			getCurrentTimeToString(),
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
