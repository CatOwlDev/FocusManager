#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <filesystem>

#include "Timer.h"
#include "Error.h"
#include "Paths.hpp"

using json = nlohmann::json;

class JsonSerializer
{
public:
	JsonSerializer() = default;
	JsonSerializer(const std::filesystem::path& path);
	~JsonSerializer();

	void loadData(const std::filesystem::path& path);
	void saveData();

	const json& getData() const;
	
	void setData(const json& data);

private:
	json mData{};
	std::filesystem::path mPath{};
};
