#include "Task.h"

Task::Task(
	const std::string& name,
	const std::string& shortDescription,
	const std::string& completionDateAndTime,
	const std::string& category,
	Status status,
	Priority priority
) :
	mName{ name },
	mShortDescription{ shortDescription },
	mCompletionDateAndTime{ completionDateAndTime },
	mCategory{ category },
	mStatus{ status },
	mPriority{ priority } {}

void Task::setName(const std::string& name) { mName = name; }
void Task::setShortDescription(const std::string& shortDescription) { mShortDescription = shortDescription; }
void Task::setCompletionDateAndTime(const std::string& completionDateAndTime) { mCompletionDateAndTime = completionDateAndTime; }
void Task::setCategory(const std::string& category) { mCategory = category; }
void Task::setStatus(Status status) { mStatus = status; }
void Task::setPriority(Priority priority) { mPriority = priority; }

const std::string& Task::getName() const { return mName; }
const std::string& Task::getShortDescription() const { return mShortDescription; }
const std::string& Task::getCompletionDateAndTime() const { return mCompletionDateAndTime; }
const std::string& Task::getCategory() const { return mCategory; }
Status Task::getStatus() const { return mStatus; }
Priority Task::getPriority() const { return mPriority; }

void to_json(json& j, const Task& t) {
	j = json{
		{ "Name", t.mName },
		{ "ShortDescription", t.mShortDescription },
		{ "Category", t.mCategory },
		{ "CompletionDateAndTime", t.mCompletionDateAndTime },
		{ "Priority", myTransformers::to_string(t.mPriority) },
		{ "Status", myTransformers::to_string(t.mStatus) },
	};
}
void from_json(const json& j, Task& t) {
	try {
		Task temp{};

		j.at("Name").get_to(temp.mName);
		j.at("ShortDescription").get_to(temp.mShortDescription);
		j.at("Category").get_to(temp.mCategory);
		j.at("CompletionDateAndTime").get_to(temp.mCompletionDateAndTime);
		std::string strPriority{};
		j.at("Priority").get_to(strPriority);
		temp.mPriority = myTransformers::to_priority(strPriority);
		std::string strStatus{};
		j.at("Status").get_to(strStatus);
		temp.mStatus = myTransformers::to_status(strStatus);

		t = temp;
	}
	catch (const json::exception& e) {
		Error error{
			getCurrentDateAndTimeToString(),
			"file: Task.cpp, func: from_json",
			e.what()
		};
		writeErrorReport(error);
	}
}