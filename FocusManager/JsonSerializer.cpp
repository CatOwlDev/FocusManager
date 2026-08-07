#include "JsonSerializer.h"

JsonSerializer::JsonSerializer(const std::wstring& path) { this->loadData(path); }
JsonSerializer::~JsonSerializer() { this->saveData(); }

void JsonSerializer::loadData(const std::wstring& path) {
	this->path = path;
	if (!std::filesystem::exists(this->path.parent_path())) {
		std::filesystem::create_directories(this->path.parent_path());
	}

	std::ifstream file{ this->path };

	if (!file) {
		std::ofstream{ this->path };
		this->data = json{};
		return;
	}

	if(file.peek() == std::ifstream::traits_type::eof()) {
		this->data = json{};
		return;
	}

	file >> this->data;
}
void JsonSerializer::saveData() {
	std::ofstream file{ this->path };

	if (!file) {
		return;
	}

	file << this->data.dump(4);
}
void JsonSerializer::clearData() { this->data.clear(); }
const json& JsonSerializer::getData() const { return this->data; }
