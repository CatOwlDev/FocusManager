#pragma once

#include <string>
#include <array>
#include <unordered_map>
#include <nlohmann/json.hpp>

#include "Error.h"
#include "Timer.h"
#include "MyTransformers.h"

using json = nlohmann::json;

class Task
{
public:
	friend void to_json(json& j, const Task& t);
	friend void from_json(const json& j, Task& t);

	Task() = default;
	Task(
		const std::string& name,
		const std::string& shortDescription,
		const std::string& completionDate,
		const std::string& category,
		Status status,
		Priority priority
	);
	~Task() = default;

	void setName(const std::string& name);
	void setShortDescription(const std::string& shortDescription);
	void setCompletionDateAndTime(const std::string& completionDateAndTime);
	void setCategory(const std::string& category);
	void setStatus(Status status);
	void setPriority(Priority priority);

	const std::string& getName() const;
	const std::string& getShortDescription() const;
	const std::string& getCompletionDateAndTime() const;
	const std::string& getCategory() const;
	Status getStatus() const;
	Priority getPriority() const;

private:
	std::string mName{};
	std::string mShortDescription{};
	std::string mCompletionDateAndTime{};
	std::string mCategory{};
	Status mStatus{};
	Priority mPriority{};
};

void to_json(json& j, const Task& t);
void from_json(const json& j, Task& t);