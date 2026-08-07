#include "Task.h"

Task::Task(
	const std::wstring& name,
	const std::wstring& pathToDescription,
	const std::wstring& completionDate,
	const std::wstring& category,
	const Status status,
	const Priority priority
) :
	name{ name },
	pathToDescription{ pathToDescription },
	completionDate{ completionDate },
	category{ category },
	status{ status },
	priority{ priority },
	id{ idCounter } { ++idCounter; }

void Task::setName(const std::wstring& name) { this->name = name; }
void Task::setPathToDescription(const std::wstring& pathToDescription) { this->pathToDescription = pathToDescription; }
void Task::setCompletionDate(const std::wstring& completionDate) { this->completionDate = completionDate; }
void Task::setCategory(const std::wstring& category) { this->category = category; }
void Task::setStatus(const Status status) { this->status = status; }
void Task::setPriority(const Priority priority) { this->priority = priority; }

std::wstring Task::getName() const { return this->name; }
std::wstring Task::getPathToDescription() const { return this->pathToDescription; }
std::wstring Task::getCompletionDate() const { return this->completionDate; }
std::wstring Task::getCategory() const { return this->category; }
Status Task::getStatus() const { return this->status; }
Priority Task::getPriority() const { return this->priority; }
unsigned int Task::getId() const { return this->id; }

void Task::setIdCounter(unsigned int idCounter) {
	Task::idCounter = idCounter;
}
unsigned int Task::getIdCounter() {
	return Task::idCounter;
}

unsigned int Task::idCounter{ 0 };