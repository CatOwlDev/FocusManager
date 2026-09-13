#include "ToDoList.h"

void ToDoList::emplaceBack(const Task& task) { mTasks.emplace_back(task); }
void ToDoList::erase(int selected) {
	if (selected < 0 || selected >= static_cast<int>(mTasks.size())) return;

	mTasks.erase(mTasks.begin() + selected);
} 

size_t ToDoList::getSize() const { return mTasks.size(); }
const std::vector<Task>& ToDoList::getTasks() const { return mTasks; }
Task& ToDoList::getTask(int selected) { return mTasks[selected];  }

void to_json(json& j, const ToDoList& toDoList) {
	j = json{
		{ "ToDoList", { {"Tasks", toDoList.mTasks} } }
	};
}
void from_json(const json& j, ToDoList& toDoList) {
	try {
		ToDoList temp{};

		j.at("Tasks").get_to(temp.mTasks);

		toDoList = temp;
	}
	catch (const json::exception& e) {
		Error error{
			getCurrentDateAndTimeToString(),
			"file: ToDoList.cpp, func: from_json",
			e.what()
		};
		writeErrorReport(error);
	}
}

ToDoList initToDoList(const JsonSerializer& jsonSerializer) {
	ToDoList toDoList{};
	const json& data{ jsonSerializer.getData() };

	if (!data.empty()) {
		try {
			data.at("ToDoList").get_to(toDoList);
		}
		catch (const json::exception& e) {
			Error error{
				getCurrentDateAndTimeToString(),
				"file: ToDoList.cpp, func: initToDoList",
				e.what()
			};
			writeErrorReport(error);
			return ToDoList{};
		}
	}

	return toDoList;
}
void saveToDoList(JsonSerializer& jsonSerializer, const ToDoList& toDoList) {
	json j{};
	to_json(j, toDoList);
	jsonSerializer.setData(j);
}