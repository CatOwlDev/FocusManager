#include "JsonSerializer.h"

JsonSerializer::JsonSerializer(const std::filesystem::path& path) { loadData(path); }
JsonSerializer::~JsonSerializer() { saveData(); }

void JsonSerializer::loadData(const std::filesystem::path& path) {
	mPath = std::filesystem::path{ path };

	std::ifstream inFile{ mPath };

	if (!inFile) {
		std::ofstream outFile{ mPath };
		mData = json{};
		outFile << mData;
		return;
	}

	try {
		if (std::filesystem::file_size(path) != 0)
			inFile >> mData;
	}
	catch (const json::exception& e) {
		mData = json{};
		Error error{
			getCurrentDateAndTimeToString(),
			"file: JsonSerializer.cpp, func: loadData",
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
const json& JsonSerializer::getData() const { return mData; }
void JsonSerializer::setData(const json& data) { mData.update(data); }