#include "Paths.hpp"

// AI
std::filesystem::path paths::getRoamingPath() {
	PWSTR path{ nullptr };

	if (FAILED(SHGetKnownFolderPath(
		FOLDERID_RoamingAppData,
		0,
		nullptr,
		&path
	))) return std::filesystem::path{};

	std::filesystem::path result{ path };
	CoTaskMemFree(path);

	return result;
}
// AI
const std::filesystem::path& paths::getFolderFocusManager() {
	static const std::filesystem::path result{
		[]()->std::filesystem::path {
			std::filesystem::path path{ getRoamingPath() / "FocusManager" };
			return path;
		}()
	};

	return result;
}