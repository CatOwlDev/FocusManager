#pragma once

#define NOMINMAX

#include <windows.h>
#include <shlobj.h>
#include <filesystem>

namespace paths {
	std::filesystem::path getRoamingPath();
	const std::filesystem::path& getFolderFocusManager();
}