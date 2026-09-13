#include "MyTransformers.h"

std::string myTransformers::to_string(const Status status) {
	int index{ static_cast<int>(status) };

	if (index < 0 || index >= myConstants::strStatuses.size()) return myConstants::strStatuses[DEFAULT];

	return myConstants::strStatuses[index];
}
std::string myTransformers::to_string(const Priority priority) {
	int index{ static_cast<int>(priority) };

	if (index < 0 || index >= myConstants::strPriorities.size()) return myConstants::strPriorities[DEFAULT];

	return myConstants::strPriorities[index];
}

Status myTransformers::to_status(const std::string& str) {
	auto it{ myConstants::mapStatuses.find(str) };

	if (it != myConstants::mapStatuses.cend()) return it->second;

	return Status::Inactive; // DEFAULT
}
Priority myTransformers::to_priority(const std::string& str) {
	auto it{ myConstants::mapPriorities.find(str) };

	if (it != myConstants::mapPriorities.cend()) return it->second;

	return Priority::Low; // DEFAULT
}

std::string myTransformers::to_string(const State state) {
	int index{ static_cast<int>(state) };

	if (index < 0 || index >= myConstants::strStates.size()) return myConstants::strStates[DEFAULT];

	return myConstants::strStates[index];
}

ftxui::Decorator myTransformers::to_color(const Priority priority) {
	static const std::array<ftxui::Decorator, 4> stylePriorities{
		ftxui::color(ftxui::Color::GreenLight),
		ftxui::color(ftxui::Color::Yellow1),
		ftxui::color(ftxui::Color::RedLight),
		ftxui::color(ftxui::Color::Red)
	};

	int index{ static_cast<int>(priority) };

	if (index < 0 || index >= stylePriorities.size()) return stylePriorities[DEFAULT];

	return stylePriorities[index];
}
ftxui::Decorator myTransformers::to_color(const Status status) {
	static const std::array<ftxui::Decorator, 3> styleStatuses{
		ftxui::color(ftxui::Color::Orange1),
		ftxui::color(ftxui::Color::Yellow),
		ftxui::color(ftxui::Color::Green)
	};

	int index{ static_cast<int>(status) };

	if (index < 0 || index >= styleStatuses.size()) return styleStatuses[DEFAULT];

	return styleStatuses[index];
}

unsigned int myTransformers::safeConvertSTOUI(const std::string& str) {
	unsigned long result{};
	try {
		result = std::stoul(str);
	}
	catch (const std::invalid_argument& e) {
		result = 0;
	}
	catch (const std::out_of_range& e) {
		result = maxNumberOfMinutesUserInputsForValue;
	}
	return static_cast<unsigned int>(result);
}