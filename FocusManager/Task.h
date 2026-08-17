#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <array>

#include "Error.h"
#include "Timer.h"

using json = nlohmann::json;

enum class Status : unsigned int {
	Active,
	Inactive,
	Completed,
};
enum class Priority : unsigned int {
	Low,
	Medium,
	High,
	Critical
};

class Task
{
public:
	friend void to_json(json& j, const Task& t);
	friend void from_json(const json& j, Task& t);
	Task() = default;
	Task(
		const std::string& name,
		const std::string& pathToDescription,
		const std::string& completionDate,
		const std::string& category,
		Status status,
		Priority priority
	);
	~Task() = default;

	void setName(const std::string& name);
	void setPathToDescription(const std::string& pathToDescription);
	void setCompletionDate(const std::string& completionDate);
	void setCategory(const std::string& category);
	void setStatus(Status status);
	void setPriority(Priority priority);
	void setId(unsigned int id);

	const std::string& getName() const;
	const std::string& getPathToDescription() const;
	const std::string& getCompletionDate() const;
	const std::string& getCategory() const;
	Status getStatus() const;
	Priority getPriority() const;
	unsigned int getId() const;

private:
	std::string mName{};
	std::string mPathToDescription{};
	std::string mCompletionDate{};
	std::string mCategory{};
	Status mStatus{};
	Priority mPriority{};
	unsigned int mId{};
};

void to_json(json& j, const Task& t);
void from_json(const json& j, Task& t);

namespace myTransform {
	std::string to_string(const Status status);
	std::string to_string(const Priority status);
}
