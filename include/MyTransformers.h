#pragma once

#include <string>
#include <array>
#include <unordered_map>
#include <ftxui/component/component.hpp>

constexpr int DEFAULT = 0;

constexpr long long maxNumberOfMinutesUserInputsForValue{ 5999 };

enum class Status : int {
	Active,
	Inactive,
	Completed,
};
enum class Priority : int {
	Low,
	Medium,
	High,
	Critical
};

enum class State : unsigned int {
	Work,
	minRelax,
	maxRelax
};

namespace myConstants {
	static const std::array<std::string, 3> strStatuses{
		"Active",
		"Inactive",
		"Completed"
	};
	static const std::array<std::string, 4> strPriorities{
		"Low",
		"Medium",
		"High",
		"Critical"
	};

	static const std::unordered_map<std::string, Status> mapStatuses{
		{ "Active", Status::Active },
		{ "Inactive", Status::Inactive },
		{ "Completed", Status::Completed }
	};
	static const std::unordered_map<std::string, Priority> mapPriorities{
		{ "Low", Priority::Low },
		{ "Medium", Priority::Medium },
		{ "High", Priority::High },
		{ "Critical", Priority::Critical }
	};

	static const std::array<std::string, 3> strStates{
		"Work",
		"MinRelax",
		"MaxRelax"
	};
}

namespace myTransformers {
	std::string to_string(const Status status);
	std::string to_string(const Priority status);
	std::string to_string(const State state);

	Status to_status(const std::string& str);
	Priority to_priority(const std::string& str);
	
	ftxui::Decorator to_color(const Priority priority);
	ftxui::Decorator to_color(const Status status);

	unsigned int safeConvertSTOUI(const std::string& str);
}