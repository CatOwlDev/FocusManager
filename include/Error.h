#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "Paths.hpp"

class Error
{
public:
	friend std::ostream& operator<<(std::ostream& out, const Error& error);
	Error() = default;
	~Error() = default;
	Error(
		const std::string& when,
		const std::string& where,
		const std::string& why
	);
private:
	std::string mWhen{};
	std::string mWhere{};
	std::string mWhy{};
};

std::ostream& operator<<(std::ostream& out, const Error& error);
void writeErrorReport(const Error& error);