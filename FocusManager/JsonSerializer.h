#pragma once
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <string>

using json = nlohmann::json;

class JsonSerializer
{
public:
	JsonSerializer() = default;
	JsonSerializer(const std::wstring& path);
	~JsonSerializer();
	JsonSerializer(const JsonSerializer& jsonSerializer) = delete;

	void loadData(const std::wstring& path);
	void saveData();
	void clearData();
	const json& getData() const;

private:
	json data{};
	std::filesystem::path path{};
};

class JsonSerializerException : public std::runtime_error {

};
