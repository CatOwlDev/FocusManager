#pragma once
#include <string>

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
	Task() = default;
	Task(
		const std::wstring& name,
		const std::wstring& pathToDescription,
		const std::wstring& completionDate,
		const std::wstring& category,
		const Status status,
		const Priority priority
	);
	~Task() = default;

	void setName(const std::wstring& name);
	void setPathToDescription(const std::wstring& pathToDescription);
	void setCompletionDate(const std::wstring& completionDate);
	void setCategory(const std::wstring& category);
	void setStatus(const Status status);
	void setPriority(const Priority priority);

	std::wstring getName() const;
	std::wstring getPathToDescription() const;
	std::wstring getCompletionDate() const;
	std::wstring getCategory() const;
	Status getStatus() const;
	Priority getPriority() const;
	unsigned int getId() const;

	static void setIdCounter(unsigned int idCounter);
	static unsigned int getIdCounter();

private:
	std::wstring name{};
	std::wstring pathToDescription{};
	std::wstring completionDate{};
	std::wstring category{};
	Status status{};
	Priority priority{};
	unsigned int id{};
	static unsigned int idCounter;
};