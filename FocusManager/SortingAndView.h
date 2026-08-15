#pragma once

#include <algorithm>
#include <ranges>
#include <vector>

#include "Task.h"

namespace Sort {
	std::vector<const Task*> sortByStringAZ(const std::vector<Task>& tasks, const std::string& (Task::* pField)() const);
	std::vector<const Task*> sortByStringZA(const std::vector<Task>& tasks, const std::string& (Task::* pField)() const);
}

namespace View {
	inline auto viewByStatus(const std::vector<Task>& tasks, const Status status) {
		return tasks | std::views::filter([status](const Task& t)->bool {
			return t.getStatus() == status;
			});
	}
	inline auto viewByPriority(const std::vector<Task>& tasks, const Priority priority) {
		return tasks | std::views::filter([priority](const Task& t)->bool {
			return t.getPriority() == priority;
			});
	}
}