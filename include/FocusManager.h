#pragma once

#include <string>
#include <thread>

#include <ftxui/component/loop.hpp>
#include <ftxui/component/screen_interactive.hpp>

#include "ToDoList.h"
#include "JsonSerializer.h"
#include "Timer.h"
#include "Blocker.h"
#include "Paths.hpp"

constexpr int fps{ 20 };
constexpr int frameTimeMilliseconds{ 1000 / fps };

class FocusManagerUI;

class FocusManager {
public:
	FocusManager();
	~FocusManager();

	void run();

	bool isRun();
	void stopRun();

	ToDoList& getToDoList();
	Timer& getTimer();
	Blocker& getBlocker();

private:
	bool mRun{};

	JsonSerializer mJsonSerializer{};
	ToDoList mToDoList{};
	Timer mTimer{};
	Blocker mBlocker{};
};