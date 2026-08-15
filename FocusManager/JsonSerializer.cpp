#include "JsonSerializer.h"

// JsonSerializer
JsonSerializer::JsonSerializer(const std::string& path) { this->loadData(path); }
JsonSerializer::~JsonSerializer() { this->saveData(); }

void JsonSerializer::loadData(const std::string& path) {
	this->path = std::filesystem::path{ path };
	if (!std::filesystem::exists(this->path.parent_path())) {
		std::filesystem::create_directories(this->path.parent_path());
	}

	std::ifstream inFile{ this->path };

	if (!inFile) {
		std::ofstream outFile{ this->path };
		this->data = json{};
		outFile << this->data;
		return;
	}

	try {
		inFile >> this->data;
	}
	catch (const json::exception& e) {
		this->data = json{};
		Error error{
			getCurrentTime(),
			"class: JsonSerializer, func: loadData",
			e.what()
		};
		writeErrorReport(error);
		return;
	}
}
void JsonSerializer::saveData() {
	std::ofstream outFile{ this->path };

	if (!outFile) {
		return;
	}

	outFile << this->data.dump(4);
}
void JsonSerializer::clearData() { this->data.clear(); }
const json& JsonSerializer::getData() const { return this->data; }
void JsonSerializer::setData(const json& data) { this->data = data; }