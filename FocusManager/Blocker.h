#pragma once

#include <vector>
#include <string>

#define NOMINMAX
#include <windows.h>
#include <tlhelp32.h>

#include "JsonSerializer.h"
#include "Error.h"
#include "Timer.h"

using json = nlohmann::json;

// AI
struct TargetWindowData {
	DWORD processId{};
	HWND windowHandle{};
};

class Blocker
{
public:
	friend void to_json(json& j, const Blocker& blocker);
	friend void from_json(const json& j, Blocker& blocker);

	Blocker() = default;
	~Blocker() = default;

	void blockAllUnimportantProcesses();
	
	void emplaceBack(const std::string& processName);
	void erase(int selected);

	void editProcessName(int selected, const std::string& processName);

	std::vector<std::string>* getList();
	std::string getProcess(int selected) const;
private:
	static BOOL CALLBACK enumWindowsProc(HWND hwndm, LPARAM lParam);
	HWND findMainWindow(DWORD processId);
	DWORD findProcessId(const std::string& processName);
	void killProcess(HWND hwnd);
private:
	std::vector<std::string> mList{};
};

void to_json(json& j, const Blocker& blocker);
void from_json(const json& j, Blocker& blocker);

Blocker initBlocker(const JsonSerializer& jsonSerializer);
void saveBlocker(JsonSerializer& jsonSerializer, const Blocker& blocker);
