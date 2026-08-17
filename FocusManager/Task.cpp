#include "Task.h"

Task::Task(
	const std::string& name,
	const std::string& pathToDescription,
	const std::string& completionDate,
	const std::string& category,
	Status status,
	Priority priority
) :
	mName{ name },
	mPathToDescription{ pathToDescription },
	mCompletionDate{ completionDate },
	mCategory{ category },
	mStatus{ status },
	mPriority{ priority } {}

void Task::setName(const std::string& name) { mName = name; }
void Task::setPathToDescription(const std::string& pathToDescription) { mPathToDescription = pathToDescription; }
void Task::setCompletionDate(const std::string& completionDate) { mCompletionDate = completionDate; }
void Task::setCategory(const std::string& category) { mCategory = category; }
void Task::setStatus(Status status) { mStatus = status; }
void Task::setPriority(Priority priority) { mPriority = priority; }
void Task::setId(unsigned int id) { mId = id; }

const std::string& Task::getName() const { return mName; }
const std::string& Task::getPathToDescription() const { return mPathToDescription; }
const std::string& Task::getCompletionDate() const { return mCompletionDate; }
const std::string& Task::getCategory() const { return mCategory; }
Status Task::getStatus() const { return mStatus; }
Priority Task::getPriority() const { return mPriority; }
unsigned int Task::getId() const { return mId; }

void to_json(json& j, const Task& t) {
	j = json{
		{ "Name", t.mName },
		{ "PathToDescription", t.mPathToDescription },
		{ "Category", t.mCategory },
		{ "CompletionDate", t.mCompletionDate },
		{ "Priority", t.mPriority },
		{ "Status", t.mStatus },
		{ "Id", t.mId }
	};
}
void from_json(const json& j, Task& t) {
	try {
		j.at("Name").get_to(t.mName);
		j.at("PathToDescription").get_to(t.mPathToDescription);
		j.at("Category").get_to(t.mCategory);
		j.at("CompletionDate").get_to(t.mCompletionDate);
		j.at("Priority").get_to(t.mPriority);
		j.at("Status").get_to(t.mStatus);
		j.at("Id").get_to(t.mId);
	}
	catch (const json::exception& e) {
		Error error{
			getCurrentTimeToString(),
			"file: Task.cpp, func: from_json",
			e.what()
		};
		writeErrorReport(error);
	}
}

std::string myTransform::to_string(const Status status) {
	static const std::array<std::string, 3> strStatuses{
	"Active",
	"Inactive",
	"Completed"
	};
	
	return strStatuses[static_cast<unsigned int>(status)];
}
std::string myTransform::to_string(const Priority priority) {
	static const std::array<std::string, 4> strStatuses{
		"Low",
		"Medium",
		"High",
		"Critical"
	};

	return strStatuses[static_cast<unsigned int>(priority)];
}
