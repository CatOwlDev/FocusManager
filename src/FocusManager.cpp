#include "FocusManager.h"
#include "UI.h"

FocusManager::FocusManager() :
	mJsonSerializer{ paths::getFolderFocusManager() / "data.json" },
	mToDoList{ initToDoList(mJsonSerializer) },
	mTimer{ initTimer(mJsonSerializer) },
	mBlocker{ initBlocker(mJsonSerializer) } {}

FocusManager::~FocusManager() {
	saveToDoList(mJsonSerializer, mToDoList);
	saveTimer(mJsonSerializer, mTimer);
	saveBlocker(mJsonSerializer, mBlocker);
	mJsonSerializer.saveData();
}

void FocusManager::run() {
	FocusManagerUI focusManagerUI{ FocusManagerUI(this) };
	ftxui::Component component{ focusManagerUI.component() };
	
	ftxui::App screen{ ftxui::ScreenInteractive::TerminalOutput() };
	ftxui::Loop loop{ &screen, component };
	
	mRun = true;
	while (!loop.HasQuitted()) {
		mTimer.update();
		mBlocker.blockAllUnimportantProcesses();

		if (!isRun()) screen.Exit();

		loop.RunOnce();

		std::this_thread::sleep_for(std::chrono::milliseconds(frameTimeMilliseconds));
	}
}

bool FocusManager::isRun() { return mRun; }
void FocusManager::stopRun() { mRun = false; }

ToDoList& FocusManager::getToDoList() { return mToDoList; }
Timer& FocusManager::getTimer() { return mTimer; }
Blocker& FocusManager::getBlocker() { return mBlocker; }
