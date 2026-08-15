#include "Task.h"

Task::Task(
	const std::string& name,
	const std::string& pathToDescription,
	const std::string& completionDate,
	const std::string& category,
	Status status,
	Priority priority
) :
	name{ name },
	pathToDescription{ pathToDescription },
	completionDate{ completionDate },
	category{ category },
	status{ status },
	priority{ priority } {}

void Task::setName(const std::string& name) { this->name = name; }
void Task::setPathToDescription(const std::string& pathToDescription) { this->pathToDescription = pathToDescription; }
void Task::setCompletionDate(const std::string& completionDate) { this->completionDate = completionDate; }
void Task::setCategory(const std::string& category) { this->category = category; }
void Task::setStatus(Status status) { this->status = status; }
void Task::setPriority(Priority priority) { this->priority = priority; }
void Task::setId(unsigned int id) { this->id = id; }

const std::string& Task::getName() const { return this->name; }
const std::string& Task::getPathToDescription() const { return this->pathToDescription; }
const std::string& Task::getCompletionDate() const { return this->completionDate; }
const std::string& Task::getCategory() const { return this->category; }
Status Task::getStatus() const { return this->status; }
Priority Task::getPriority() const { return this->priority; }
unsigned int Task::getId() const { return this->id; }

void to_json(json& j, const Task& t) {
	j = json{
		{ "Name", t.name },
		{ "PathToDescription", t.pathToDescription },
		{ "Category", t.category },
		{ "CompletionDate", t.completionDate },
		{ "Priority", t.priority },
		{ "Status", t.status },
		{ "Id", t.id }
	};
}
void from_json(const json& j, Task& t) {
	try {
		j.at("Name").get_to(t.name);
		j.at("PathToDescription").get_to(t.pathToDescription);
		j.at("Category").get_to(t.category);
		j.at("CompletionDate").get_to(t.completionDate);
		j.at("Priority").get_to(t.priority);
		j.at("Status").get_to(t.status);
		j.at("Id").get_to(t.id);
	}
	catch (const json::exception& e) {
		Error error{
			getCurrentTime(),
			"file: Task.cpp, func: from_json",
			e.what()
		};
		writeErrorReport(error);
	}
}

std::string myTransform::to_string(const Status status) {
	static const std::array<std::string, 3> str{
	"Active",
	"Inactive",
	"Completed"
	};
	
	return str[static_cast<size_t>(status)];
}
std::string myTransform::to_string(const Priority priority) {
	static const std::array<std::string, 4> str{
		"Low",
		"Medium",
		"High",
		"Critical"
	};

	return str[static_cast<size_t>(priority)];
}
