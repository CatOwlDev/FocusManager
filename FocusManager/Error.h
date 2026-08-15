#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>


class Error
{
public:
	friend std::ostream& operator<<(std::ostream& out, const Error& e);
	Error() = default;
	~Error() = default;
	Error(
		const std::string& when,
		const std::string& where,
		const std::string& why
	);
private:
	std::string when{};
	std::string where{};
	std::string why{};
};

std::ostream& operator<<(std::ostream& out, const Error& e);
void writeErrorReport(const Error& error);