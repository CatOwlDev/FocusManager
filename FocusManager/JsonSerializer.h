#pragma once

#include <nlohmann/json.hpp>
#include <string>

#include "Timer.h"
#include "Error.h"

using json = nlohmann::json;

class JsonSerializer
{
public:
	JsonSerializer() = default;
	JsonSerializer(const std::string& path);
	~JsonSerializer();
	JsonSerializer(const JsonSerializer& jsonSerializer) = delete;

	void loadData(const std::string& path);
	void saveData();
	void clearData();
	const json& getData() const;
	void setData(const json& data);

private:
	json mData{};
	std::filesystem::path mPath{};
};