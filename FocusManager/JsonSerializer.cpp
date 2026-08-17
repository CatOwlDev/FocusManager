#include "JsonSerializer.h"

// JsonSerializer
JsonSerializer::JsonSerializer(const std::string& path) { loadData(path); }
JsonSerializer::~JsonSerializer() { saveData(); }

void JsonSerializer::loadData(const std::string& path) {
	mPath = std::filesystem::path{ path };
	if (!std::filesystem::exists(mPath.parent_path())) {
		std::filesystem::create_directories(mPath.parent_path());
	}

	std::ifstream inFile{ mPath };

	if (!inFile) {
		std::ofstream outFile{ mPath };
		mData = json{};
		outFile << mData;
		return;
	}

	try {
		inFile >> mData;
	}
	catch (const json::exception& e) {
		mData = json{};
		Error error{
			getCurrentTimeToString(),
			"class: JsonSerializer, func: loadData",
			e.what()
		};
		writeErrorReport(error);
	}
}
void JsonSerializer::saveData() {
	std::ofstream outFile{ mPath };

	if (!outFile) {
		return;
	}

	outFile << mData.dump(4);
}
void JsonSerializer::clearData() { mData.clear(); }
const json& JsonSerializer::getData() const { return mData; }
void JsonSerializer::setData(const json& data) { mData = data; }