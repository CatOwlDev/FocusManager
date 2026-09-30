#include "Blocker.h"

// AI
void Blocker::blockAllUnimportantProcesses() {
	for (const std::string& target : mList) {
		DWORD processId{ findProcessId(target) };
		if (processId != 0) {
			HWND hwnd{ findMainWindow(processId) };
			killProcess(hwnd);
		}
	}
}

void Blocker::emplaceBack(const std::string& processName) { mList.emplace_back(processName); }
void Blocker::erase(int selected) {
	if (selected < 0 || selected >= static_cast<int>(mList.size())) return;

	mList.erase(mList.begin() + selected);
}

void Blocker::editProcessName(int selected, const std::string& processName) { mList[selected] = processName; }

std::vector<std::string>* Blocker::getList() { return &mList; }
std::string Blocker::getProcess(int selected) const { return mList[selected]; }

// AI
BOOL CALLBACK Blocker::enumWindowsProc(HWND hwnd, LPARAM lParam) {
	TargetWindowData* data{ reinterpret_cast<TargetWindowData*>(lParam) };
	DWORD windowProcessId{ 0 };

	GetWindowThreadProcessId(hwnd, &windowProcessId);

	if (windowProcessId == data->processId && GetWindow(hwnd, GW_OWNER) == NULL && IsWindowVisible(hwnd)) {
		data->windowHandle = hwnd;
		return FALSE;
	}

	return TRUE;
}
// AI
HWND Blocker::findMainWindow(DWORD processId) {
	TargetWindowData data{ processId, NULL };

	EnumWindows(enumWindowsProc, reinterpret_cast<LPARAM>(&data));
	return data.windowHandle;
}
// AI
DWORD Blocker::findProcessId(const std::string& processName) {
	std::wstring targetProcessName{ processName.begin(), processName.end() };
	PROCESSENTRY32W processInfo{};
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot{ CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };
	if (processesSnapshot == INVALID_HANDLE_VALUE) return 0;

	if (Process32FirstW(processesSnapshot, &processInfo)) {
		do {

			if (targetProcessName == processInfo.szExeFile) {
				CloseHandle(processesSnapshot);
				return processInfo.th32ProcessID;
			}
		} while (Process32NextW(processesSnapshot, &processInfo));
	}

	CloseHandle(processesSnapshot);
	return 0;
}
// AI
void Blocker::killProcess(HWND hwnd) { 
	if (hwnd != NULL) {
		PostMessage(hwnd, WM_CLOSE, 0, 0);
	}
}

void to_json(json& j, const Blocker& blocker) {
	j = json{
		{ "Blocker", { { "List", blocker.mList } } }
	};
}
void from_json(const json& j, Blocker& blocker) {
	try {
		j.at("List").get_to(blocker.mList);
	}
	catch (const json::exception& e) {
		Error error{
			getCurrentDateAndTimeToString(),
			"file: Blocker.cpp, func: from_json",
			e.what()
		};
		writeErrorReport(error);
	}
}

Blocker initBlocker(const JsonSerializer& jsonSerializer) {
	Blocker blocker{};
	const json& data{ jsonSerializer.getData() };

	if (!data.empty()) {
		try {
			data.at("Blocker").get_to(blocker);
		}
		catch (const json::exception& e) {
			Error error{
				getCurrentDateAndTimeToString(),
				"file: Blocker.cpp, func: initBlocker",
				e.what()
			};
			writeErrorReport(error);
			return Blocker{};
		}
	}

	return blocker;
}
void saveBlocker(JsonSerializer& jsonSerializer, const Blocker& blocker) {
	json j{};
	to_json(j, blocker);
	jsonSerializer.setData(j);
}
